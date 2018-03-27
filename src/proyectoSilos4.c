/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/
#include "proyectoSilos4.h"
#include "sapi.h"        // <= sAPI header
#include "os.h"       // <= freeOSEK
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


/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/
uint8_t key;
uint8_t slaves[MAXSLAVES][COLUMN_DATA];
uint8_t activeSlaves;
uint8_t inactiveSlaves; //en principio se hace general. lo ideal es informar cual está inactivo
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
static uint8_t ACT_ID;


/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/
/**
Por cada esclavo:
	si está activo toma su temperatura y humedad para realizar el promedio del interior del silo
	si estuvo inactivo 30 veces seguidas, indica que hay esclavos inactivos
**/
void processData (void);
void processActives (void);
void info (void);

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();
   PMM_init();
   // ---------- INICIAR SISTEMA OPERATIVO --------------------
	// Starts the operating system in the Application Mode 1
	// This example has only one Application Mode
	StartOS(AppMode1);

	// StartOs shall never returns, but to avoid compiler warnings or errors
	// 0 is returned

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontrolador y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}


void ErrorHook(void)
{
	ShutdownOS(0);
}
 /** Se ejecuta sólo 1 vez.
 ---acá van los init de cada librería--
 Activa las alarmas que temporizan todo el sistema.**/
TASK (InitTask){

	key='s';
	inactiveSlaves=0;
	VENTILACION_Init();
	KEYPAD_init();
	LCD_init(DISPLAY_8X5 | _2_LINES , DISPLAY_ON | CURSOR_OFF);
	MEF_Init();
	CONFIG_init();
	SetRelAlarm(ActivateKeypadTask, 1000, 100);
	SetRelAlarm(ActivateRefreshDisplayTask, 1000, 500);
	SetRelAlarm(ActivateDetectActiveSlavesTask, 1000, 2000);
	TerminateTask();
}

TASK(KeypadTask){
	KEYPAD_ScanAutorepeat(&key);
	TerminateTask();
}

TASK(RefreshDisplayTask){	
	if(!KEYPAD_getkey(&key)){
		key='s';
	}

	MEF_updateState(0);
	MEF_updateOutput(temperatureI,temperatureE,humidityI,humidityE,activeSlaves,inactiveSlaves,fan);
	TerminateTask();

}
TASK(DetectActiveSlavesTask){
	ACT_ID=4;
	EventMaskType Events;	
	uint8_t package[3];
	uint8_t id;
	
	for(id=1; id<MAXSLAVES+1; id++){
		PMM_setPaq(id,0x0A, package);
		uartWriteString(UART_RS485, package);
		SetRelAlarm(SetWatchDogDetectEvent, 12,0);
		WaitEvent(receiveInterruptEvent | WatchDogEvent);
		GetEvent(DetectActiveSlavesTask, &Events);
		if(Events & receiveInterruptEvent){ //se recibió interrupción
			CancelAlarm(SetWatchDogDetectEvent);	
			if(PMM_verify(buffer, id)==1){
				slaves[id][C_STATE]=ACTIVE;
				if(slaves[id][C_INACTIVE]>=MAX_INACTIVE)
					slaves[id][C_INACTIVE]=0;
			}
			else{
				//ESTO
				slaves[id][C_STATE]=INACTIVE;
				slaves[id][C_INACTIVE]++;
			}
		}
		else{
			slaves[id][C_STATE]=INACTIVE;
			slaves[id][C_INACTIVE]++;
		}
		ClearEvent(Events);
	}
	

	ActivateTask(TakeDataSlavesTask);
	TerminateTask();


}
TASK(TakeDataSlavesTask){
	ACT_ID=5;
	EventMaskType Events;
	uint8_t package[3];
	uint8_t id;
	processActives();
	for(id=1; id<MAXSLAVES+1; id++){
		if(slaves[id][C_STATE]==ACTIVE){
			PMM_setPaq(id,0x1E, package);
			uartWriteString(UART_RS485, package);
			SetRelAlarm(SetWatchDogTakeDataEvent, 12,0);
			WaitEvent(receiveInterruptEvent | WatchDogEvent);
			GetEvent(TakeDataSlavesTask, &Events);
			if(Events & receiveInterruptEvent){ //se recibió interrupción
				CancelAlarm(SetWatchDogTakeDataEvent);
				PMM_getData(buffer,id, &slaves[id][C_TEMP], &slaves[id][C_HUM]);
			}
			ClearEvent(Events);
		}	
	}
	//ingresarDatos();
	ActivateTask(ActionTask);
	TerminateTask();

}
TASK(ActionTask){
	gpioToggle(LED3);
	processData();
		if(VENTILACION_actuar(temperatureI, temperatureE, humidityI, humidityE, CONFIG_get_desired_temp()))
		fan=1;
	else
		fan=0;
		

	
	if(temperatureI>=TEMP_ALERTA){
		gpioToggle(LED1);
		//GPRS_critico();
	}
	if(inactiveSlaves){
		gpioToggle(LED2);
		//GPRS_alerta();
	}
	
	TerminateTask();

}
//rutina de interrupción utilizada para la primer prueba de recepción de byte
ISR (UART_RS485_IRQHandler){
	if(ACT_ID==4)
		SetEvent(DetectActiveSlavesTask, receiveInterruptEvent);
	else
		if(ACT_ID==5)
			SetEvent(TakeDataSlavesTask, receiveInterruptEvent);
	info();
}
/*==================[definiciones de funciones internas]=====================*/

//Las variables cantInactiveSlaves, inactiveSlaves, activeSlaves se deberían revisar.
//Como solución se planteo esto para salir del apuro. Pero podría estar mejor.
void processActives (void){
	uint8_t i;
	uint8_t cantInactiveSlaves=0;
	activeSlaves=0;
	for(i=1; i<MAXSLAVES+1; i++){ //el esclavo 1 está en el exterior, por eso no se incluye en el promedio.
		if(slaves[i][C_STATE]==ACTIVE){ //está activo
			activeSlaves++;
		}
		if(slaves[i][C_INACTIVE]>=MAX_INACTIVE)
			cantInactiveSlaves++; //en principio solo se notifica que hay al menos 1 inactivo, lo mejor sería indicar cual/es
	}
	if(cantInactiveSlaves>(MAXSLAVES-CANT_SLAVES))
		inactiveSlaves=1;
	else
		inactiveSlaves=0;

}

void processData (void){
	uint8_t i;
	float tempAux, humAux;
	unsigned short totalHum=0, totalTemp=0;
	for(i=2; i<MAXSLAVES+1; i++){ //el esclavo 1 está en el exterior, por eso no se incluye en el promedio.
		if(slaves[i][C_STATE]==ACTIVE){ //está activo
			totalTemp=totalTemp + slaves[i][C_TEMP];
			totalHum=totalHum + slaves[i][C_HUM];
		}

		
	}
	if(activeSlaves>0){ //si no hay esclavos activos no tiene sentido hacer el promedio
		tempAux=(float)totalTemp/activeSlaves;
		if(tempAux-(uint8_t)tempAux > 0.5) //se redondea
			temperatureI=ceil(tempAux);
		else
			temperatureI=floor(tempAux);
		
		humAux=(float)totalHum/activeSlaves; 
		if(humAux-(uint8_t)humAux > 0.5) //se redondea
			humidityI=ceil(humAux);
		else
			humidityI=floor(humAux);
	}
	else{ //si no hay datos
		temperatureI=255; //momentaneo. Lo ideal sería mostrar en pantalla 'XX'
		humidityI=255;
	}
	if(slaves[1][C_STATE]==ACTIVE){ //Esclavo exterior
		temperatureE=slaves[1][C_TEMP];
		humidityE=slaves[1][C_HUM];
	}
	else{ 
		/*Si el sensor exterior no funciona el sistema no funciona
		Debe agregarse a estado de alerta!!*/
		temperatureE=255; //momentaneo. Lo ideal sería mostrar en pantalla 'XX'
		humidityE=255;		
	}


}

void info(void){
	int32_t message_length=0;
	while (Chip_UART_ReadLineStatus(LPC_USART0) & UART_LSR_RDR) {
      buffer[message_length++] = Chip_UART_ReadByte(LPC_USART0);
   }


}

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
