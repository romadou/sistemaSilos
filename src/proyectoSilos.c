/**
 * @brief Sistema operativo general
 * 
 * @file proyectoSilos.c
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#include "proyectoSilos4.h"
#include "sapi.h"        // sAPI header
#include "os.h"       // freeOSEK
#include "MEF.h"
#include "VENTILACION.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "lcd_mensajes.h"
#include "testTabla.h"
#include "math.h"
#include "general_config.h"
#include "PMM_sensores.h"
#include "gprs.h"

/* Variables privadas */
uint8_t key;
uint8_t slaves[MAXSLAVES][COLUMN_DATA];
uint8_t activeSlavesTotal;
uint8_t activeSlavesInterior;
uint8_t activeSlavesExterior;
uint8_t inactiveSlaves;
uint8_t temperatureI;
uint8_t humidityI;
uint8_t temperatureE;
uint8_t humidityE;
uint8_t desiredTemp;
uint8_t fan;
uint8_t buffer[7];
uint8_t posBuffer;
uint8_t indice;
uint8_t dato;
uint8_t retransmision;
static uint8_t ACT_ID;

/* Funciones privadas */
void processData (void);
void processActives (void);
void info (void);

/* Función principal, punto de entrada al programa al encender o reiniciar el sistema */
int main( void ){
	// CONFIGURACIONES
	// Inicializar y configurar la plataforma
	boardConfig();
	PMM_init();
	GPRS_config();

	// INICIAR SISTEMA OPERATIVO
	StartOS(AppMode1);

   // NO DEBE LLEGAR NUNCA AQUI; debido a que a este programa se ejecuta
   // directamente sobre un microcontrolador y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/* Se ejecuta ante cualquier error y apaga el Sistema Operativo */
void ErrorHook(void){
	ShutdownOS(0);
}

/**
 * @brief Tarea inicial
 * Se ejecuta sólo una vez
 * Contiene los init de cada librería
 * Activa las alarmas que temporizan todo el sistema
 */
TASK (InitTask){
	key='s';
	inactiveSlaves=0;
	retransmision=0;
	VENTILACION_Init();
	LCD_init(DISPLAY_8X5 | _2_LINES , DISPLAY_ON | CURSOR_OFF);
	MEF_Init();
	CONFIG_init();
	SetRelAlarm(ActivateKeypadTask, 1000, 100);
	SetRelAlarm(ActivateRefreshDisplayTask, 1000, 500);
	SetRelAlarm(ActivateDetectActiveSlavesTask, 1000, 2000);
	TerminateTask();
}

/**
 * @brief Tarea del teclado
 * 
 */
TASK(KeypadTask){
	KEYPAD_ScanAutorepeat(&key);
	TerminateTask();
}

/**
 * @brief Tarea de refresco del display
 * 
 */
TASK(RefreshDisplayTask){	
	if(!KEYPAD_getkey(&key)){
		key='s';
	}

	MEF_updateState(0);
	MEF_updateOutput(temperatureI,temperatureE,humidityI,humidityE,activeSlavesTotal,inactiveSlaves,fan);
	TerminateTask();

}

/**
 * @brief Tarea de detección de esclavos activos
 * 
 */
TASK(DetectActiveSlavesTask){
	ACT_ID=4;
	EventMaskType Events;	
	uint8_t package[3];
	uint8_t id;
	
	for(id=1; id<MAXSLAVES; id++){
		while(retransmision<3){
			PMM_setPaq(id,(operacion)ESTADO, package);
			uartWriteString(UART_RS485, package);
			SetRelAlarm(SetWatchDogDetectEvent, 20,0);
			WaitEvent(receiveInterruptEvent | WatchDogEvent);
			GetEvent(DetectActiveSlavesTask, &Events);
			if(Events & receiveInterruptEvent){ //se recibió interrupción
				CancelAlarm(SetWatchDogDetectEvent);	
				if(PMM_verify(buffer, id)==1){
					slaves[id][C_STATE]=ACTIVE;
					retransmision=3; //fin
					if(slaves[id][C_INACTIVE]>=MAX_INACTIVE)
						slaves[id][C_INACTIVE]=0;
				}
				else{
					retransmision++;
					slaves[id][C_STATE]=INACTIVE;
					slaves[id][C_INACTIVE]++;
				}
			}
			else{
				retransmision++;
				slaves[id][C_STATE]=INACTIVE;
				slaves[id][C_INACTIVE]++;
			}
			ClearEvent(Events);
		}
		retransmision=0;
	}
	

	ActivateTask(TakeDataSlavesTask);
	TerminateTask();


}

/**
 * @brief Tarea de recolección de datos
 * 
 */
TASK(TakeDataSlavesTask){
	ACT_ID=5;
	EventMaskType Events;
	uint8_t package[3];
	uint8_t id;
	processActives();
	for(id=1; id<MAXSLAVES; id++){
		if(slaves[id][C_STATE]==ACTIVE){
			while(retransmision<3){

				PMM_setPaq(id,(operacion)DATA, package);
				uartWriteString(UART_RS485, package);
				SetRelAlarm(SetWatchDogTakeDataEvent, 20,0);
				WaitEvent(receiveInterruptEvent | WatchDogEvent);
				GetEvent(TakeDataSlavesTask, &Events);
				if(Events & receiveInterruptEvent){ // Se detectó una interrupción
					CancelAlarm(SetWatchDogTakeDataEvent);
					if(PMM_getData(buffer,id, &slaves[id][C_TEMP], &slaves[id][C_HUM])!=1){
						retransmision++;
						slaves[id][C_STATE]=INACTIVE;
						slaves[id][C_INACTIVE]++;
					}
					else{
						retransmision=3; // Fin
					}
				}
				else{
					retransmision++;
					slaves[id][C_STATE]=INACTIVE;
					slaves[id][C_INACTIVE]++;
				}
				ClearEvent(Events);
			}
			retransmision=0;

		}	
	}
	ActivateTask(ActionTask);
	TerminateTask();

}

/**
 * @brief Tarea de actuación
 * 
 */
TASK(ActionTask){
	gpioToggle(LED3);
	processData();
		if(VENTILACION_actuar(temperatureI, temperatureE, humidityI, humidityE, CONFIG_get_desired_temp()))
		fan=1;
	else
		fan=0;
	if(temperatureI>=TEMP_ALERTA){
		gpioToggle(LED1);
	}
	if(inactiveSlaves){
		gpioToggle(LED2);
		GPRS_alerta();
	}
	
	TerminateTask();

}

/**
 * @brief Rutina de interrupción
 * 
 */
ISR (UART_RS485_IRQHandler){
	if(ACT_ID==4)
		SetEvent(DetectActiveSlavesTask, receiveInterruptEvent);
	else
		if(ACT_ID==5)
			SetEvent(TakeDataSlavesTask, receiveInterruptEvent);
	info();
}

/**
 * Por cada esclavo:
 * 		- si está activo, toma su temperatura y humedad para realizar el promedio del interior del silo
 *  	- si estuvo inactivo 30 veces seguidas, indica que hay esclavos inactivos
 */
void processActives (void){
	uint8_t i;
	uint8_t cantInactiveSlaves=0;
	activeSlavesTotal=0;
	activeSlavesInterior=0;
	activeSlavesExterior=0;
	// El esclavo 1 está en el exterior, por eso no se incluye en el promedio.
	for(i=1; i<MAXSLAVES; i++){ 
		// Si está activo
		if(slaves[i][C_STATE]==ACTIVE){ 
			if(i==1)
				activeSlavesExterior++;
			else
				activeSlavesInterior++;
		}
		if(slaves[i][C_INACTIVE]>=MAX_INACTIVE)
			cantInactiveSlaves++;
	}
	if(cantInactiveSlaves>=(MAXSLAVES-CANT_SLAVES))
		inactiveSlaves=1;
	else
		inactiveSlaves=0;

}

/* Procesamiento de los datos obtenidos del sistema de sensado */
void processData (void){
	uint8_t i;
	float tempAux, humAux;
	unsigned short totalHum=0, totalTemp=0;
	// El esclavo 1 está en el exterior, por eso no se incluye en el promedio.
	for(i=2; i<MAXSLAVES; i++){
		// Si está activo
		if(slaves[i][C_STATE]==ACTIVE){
			totalTemp=totalTemp + slaves[i][C_TEMP];
			totalHum=totalHum + slaves[i][C_HUM];
		}
	}
	// Si no hay esclavos activos, no tiene sentido hacer el promedio
	if(activeSlavesInterior>0){ 
		tempAux=(float)totalTemp/activeSlavesInterior;
		// Se redondea
		if(tempAux-(uint8_t)tempAux > 0.5)
			temperatureI=ceil(tempAux);
		else
			temperatureI=ceil(tempAux);
		
		humAux=(float)totalHum/activeSlavesInterior; 
		if(humAux-(uint8_t)humAux > 0.5)
			humidityI=ceil(humAux);
		else
			humidityI=floor(humAux);
	}
	else{
		temperatureI=255;
		humidityI=255;
	}
	
	// Esclavo exterior
	if(slaves[1][C_STATE]==ACTIVE){
		temperatureE=slaves[1][C_TEMP];
		humidityE=slaves[1][C_HUM];	
	}
	else{ 
		// Si el sensor exterior no funciona el sistema no funciona
		// Se muestra en pantalla 'XX'
		temperatureE=255;
		humidityE=255;		
	}

	activeSlavesTotal=activeSlavesInterior+activeSlavesExterior;
}

void info(void){
	int32_t message_length=0;
	while (Chip_UART_ReadLineStatus(LPC_USART0) & UART_LSR_RDR) {
      buffer[message_length++] = Chip_UART_ReadByte(LPC_USART0);
   }

}
