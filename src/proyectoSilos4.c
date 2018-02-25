/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

//#include "blinky.h"   // <= own header (optional)
#include "sapi.h"        // <= sAPI header
#include "os.h"       // <= freeOSEK
#include "proyectoSilos4.h"
#include "MEF.h"
#include "VENTILACION.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "lcd_mensajes.h"
#include "packageGenerator.h"



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
uint8_t buffer[8];
uint8_t posBuffer;
uint8_t indice;
uint8_t dato;

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/
/**
Por cada esclavo:
	si está activo toma su temperatura y humedad para realizar el promedio del interior del silo
	si estuvo inactivo 30 veces seguidas, indica que hay esclavos inactivos
**/
void processData (void);

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();
   uartConfig(0,9600);
   uartEnableRxInterrupt(4);
   //uartEnableRxInterrupt(4);
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
	//HASTA OBTENER VALORES DE LOS ESCLAVOS
	temperatureI=23;
	humidityI=70;
	temperatureE=21;
	humidityE=65;
	desiredTemp=22;

	//HASTA OBTENER VALORES DE LOS ESCLAVOS
	fan=0;
	VENTILACION_Init();
	KEYPAD_init();
	LCD_init(DISPLAY_8X5 | _2_LINES , DISPLAY_ON | CURSOR_OFF);
	MEF_Init();
	SetRelAlarm(ActivateKeypadTask, 1000, 100);
	SetRelAlarm(ActivateRefreshDisplayTask, 1000, 600);
	SetRelAlarm(ActivateDetectActiveSlavesTask, 1000, 6000);
	TerminateTask();
}

TASK(KeypadTask){
	gpioToggle( LED3 );
	KEYPAD_ScanAutorepeat(&key);
	TerminateTask();
}

TASK(RefreshDisplayTask){	
	if(!KEYPAD_getkey(&key)){
		key='s';
	}
	MEF_updateState(0);
	MEF_updateOutput(temperatureI,temperatureE,humidityI,humidityE,activeSlaves,fan);
	TerminateTask();

}
TASK(DetectActiveSlavesTask){
	gpioToggle( LED1 );	
	ActivateTask(TakeDataSlavesTask);
	TerminateTask();


}
TASK(TakeDataSlavesTask){
	gpioToggle( LEDR );	
	ActivateTask(ActionTask);
	TerminateTask();

}
TASK(ActionTask){
	gpioToggle( LEDB );	
	if(VENTILACION_actuar(temperatureI, temperatureE, humidityI, humidityE, desiredTemp))
		fan=1;
	else
		fan=0;
	TerminateTask();

}
//rutina de interrupción utilizada para la primer prueba de recepción de byte
ISR (UART_RS485_IRQHandler){
	uartReceiveByte(4, &dato);
	saveInBuffer(dato);

}
/*==================[definiciones de funciones internas]=====================*/


void processData (void){
	uint8_t i, totalHum=0, totalTemp=0, cantTotal=0;
	for(i=1; i<31; i++){ //el esclavo 0 está en el exterior, por eso no se incluye en el promedio.
		if(slaves[i][C_STATE]==1){ //está activo
			totalTemp=totalTemp + slaves[i][C_TEMP];
			totalHum=totalHum + slaves[i][C_HUM];
			cantTotal++;
		}
		if(slaves[i][C_INACTIVE]>=30){
			inactiveSlaves=1; //en principio solo se notifica que hay al menos 1 inactivo, lo mejor sería indicar cual/es
		}

	humidityI=totalHum/cantTotal;
	temperatureI=totalTemp/cantTotal;	
	}

}



/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
