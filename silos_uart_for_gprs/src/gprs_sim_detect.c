/*
 * Date: 2017-10-26
 */
/*==================[inclusions]=============================================*/

#include "gprs_sim_detect.h"   // <= own header (optional)
#include "sapi.h"     // <= sAPI header

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void imprimirMensajeDeBienvenida( void ){

   /* Imprimo el mensaje de bienvenida */
   uartWriteString( UART_USB,
      "Bienvenido al asistente de comunicación serie con el SIM800L\r\n" );
   uartWriteString( UART_USB,
      "A continuacion se realiza un listado de algunos de los\r\n" );
   uartWriteString( UART_USB, "comandos AT disponibles (a completar):\r\n\r\n" );
   uartWriteString( UART_USB,
      "> Saber si el modulo responde correctamente: AT\r\n" );
   uartWriteString( UART_USB,
      "> Version del Firmware: AT+GMR\r\n" );
   uartWriteString( UART_USB, "> Resetear el modulo: AT+RST\r\n" );

   delay(100);
}


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar las UART a 9600 baudios */
   uartConfig( UART_USB, BAUD_RATE );
   uartConfig( UART_232, BAUD_RATE );

   uint8_t dato  = 0;

   //imprimirMensajeDeBienvenida();
   delay(1000);
   //Activar impresión de códigos de error
   uartWriteString( UART_232, "AT+CMEE=1\r\n");
   delay(5000);
   while( uartReadByte( UART_232, &dato ) ){
      /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
      uartWriteByte( UART_USB, dato );
   }
   //Activar serivicio de mensajes
   uartWriteString( UART_232, "AT+CMGF=1\r\n");
   delay(5000);
   while( uartReadByte( UART_232, &dato ) ){
      /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
      uartWriteByte( UART_USB, dato );
   }
   //Activar almacenamiento de mensajes en SIM
   uartWriteString( UART_232, "AT+CPMS=\"SM\"\r\n");
   delay(5000);
   while( uartReadByte( UART_232, &dato ) ){
      /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
      uartWriteByte( UART_USB, dato );
   }
   //Para leer el primer mensaje recibido que no parece estar recibiendo
   uartWriteString( UART_232, "AT+CMGR=1\r\n");
   delay(5000);
   while( uartReadByte( UART_232, &dato ) ){
      /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
      uartWriteByte( UART_USB, dato );
   }

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      /* Si recibe un byte de la UART_USB lo guardarlo en la variable dato. */
      //if( uartReadByte( UART_USB, &dato ) ){
         /* Se reenvía el dato a la UART_232 realizando un puente entre ambas */
         //uartWriteByte( UART_232, dato );
         //uartWriteByte( UART_USB, dato );
      //}

      /* Si recibe un byte de la UART_232 guardarlo en la variable dato. */
      while( uartReadByte( UART_232, &dato ) ){
         /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
         uartWriteByte( UART_USB, dato );
      }

      delay(5000);


   }
}

/*==================[end of file]============================================*/