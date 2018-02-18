/*
 * Fecha: 2018-02-17
 */

#include "gprs.h" 
#include "sapi.h" 
#include <string.h>


char src_number[10] = "2215410495";
char dest_number[10] = "2314401890";

void GPRS_config(void){
   uint8_t dato = 0;   

   /* Inicializar las UART según BAUD_RATE */
   uartConfig(UART_USB, BAUD_RATE);
   uartConfig(UART_232, BAUD_RATE);
   
   //Activar impresión de códigos de error
   uartWriteString( UART_232, "AT+CMEE=1\r\n");
   delay(1000);
   while( uartReadByte( UART_232, &dato ) ){
      /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
      uartWriteByte( UART_USB, dato );
   }

   //Activar servicio de mensajes
   uartWriteString( UART_232, "AT+CMGF=1\r\n");
   delay(1000);
   while( uartReadByte( UART_232, &dato ) ){
      /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
      uartWriteByte( UART_USB, dato );
   }
}

void GPRS_config(int baud_rate){
   uint8_t dato = 0;   

   /* Inicializar las UART según baud_rate */
   uartConfig(UART_USB, baud_rate);
   uartConfig(UART_232, baud_rate);
   
   //Activar impresión de códigos de error
   uartWriteString( UART_232, "AT+CMEE=1\r\n");
   delay(1000);
   while( uartReadByte( UART_232, &dato ) ){
      /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
      uartWriteByte( UART_USB, dato );
   }

   //Activar servicio de mensajes
   uartWriteString( UART_232, "AT+CMGF=1\r\n");
   delay(1000);
   while( uartReadByte( UART_232, &dato ) ){
      /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
      uartWriteByte( UART_USB, dato );
   }
}

void GPRS_config(int baud_rate, char *dest_num){
   uint8_t dato = 0;   

   strcpy(dest_number, dest_num);

   /* Inicializar las UART según baud_rate */
   uartConfig(UART_USB, baud_rate);
   uartConfig(UART_232, baud_rate);
   
   //Activar impresión de códigos de error
   uartWriteString( UART_232, "AT+CMEE=1\r\n");
   delay(1000);
   while( uartReadByte( UART_232, &dato ) ){
      /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
      uartWriteByte( UART_USB, dato );
   }

   //Activar servicio de mensajes
   uartWriteString( UART_232, "AT+CMGF=1\r\n");
   delay(1000);
   while( uartReadByte( UART_232, &dato ) ){
      /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
      uartWriteByte( UART_USB, dato );
   }
}

void GPRS_alerta(void){
   uint8_t i;
   uint8_t dato  = 0;
   char mens[28] = "SILO: CONDICIONES DE ALERTA";
   strcpy(mens, "AT+CMGS=\"");
   strcat(mens, dest_number);
   strcat(mens, "\"\r");
   for (i=0; i<50; i++){
      delay(10);
   }
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, mens );
   uartWriteString( UART_232, "\x1A");
   for (i=0; i<50; i++){
      delay(10);
   }
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
}

void GPRS_critico(void){
   uint8_t i;
   uint8_t dato  = 0;
   char mens[21] = "SILO: ESTADO CRITICO";
   strcpy(mens, "AT+CMGS=\"");
   strcat(mens, dest_number);
   strcat(mens, "\"\r");
   for (i=0; i<50; i++){
      delay(10);
   }
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, mens );
   uartWriteString( UART_232, "\x1A");
   for (i=0; i<50; i++){
      delay(10);
   }
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
}

void GPRS_set_dest_num(char *dest_num){
   strcpy(dest_number, dest_num);
}
