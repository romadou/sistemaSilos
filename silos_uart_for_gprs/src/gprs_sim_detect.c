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
   uartWriteString( UART_USB, "AT\r\n");
   uartWriteString( UART_232, "AT" );

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      /* Si recibe un byte de la UART_USB lo guardarlo en la variable dato. */
      //if( uartReadByte( UART_USB, &dato ) ){
         /* Se reenvía el dato a la UART_232 realizando un puente entre ambas */
         //uartWriteByte( UART_232, dato );
         //uartWriteByte( UART_USB, dato );
      //}

      /* Si recibe un byte de la UART_232 lo guardarlo en la variable dato. */
      if( uartReadByte( UART_232, &dato ) ){
         /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
         uartWriteByte( UART_USB, dato );
         delay(100);
      }
      else{
         uartWriteString( UART_232, "AT" );
         uartWriteString( UART_USB, "AT\r\n");
         delay(1000);
      }
   }
}

/*==================[end of file]============================================*/