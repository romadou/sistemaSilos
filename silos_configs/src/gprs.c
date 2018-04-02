/*
 * Fecha: 2018-02-17
 */

#include "gprs.h" 
#include "sapi.h" 
#include <string.h>


//char src_number[11] = "2215410495";
char dest_number[11] = "2314401890";
char dest_aux[11] = "";
uint8_t dato;
uint8_t i;

//Regenerar PDU: Por ahora dice "testing"
//char length_alert_PDU = 20;
//char PDU_alert[56] = "07914570090008F111000AA132410481090000FF07F4F29C9E769F01";
//Por simplicidad de código, se hardcodea

//Regenerar PDU: Por ahora dice "ok"
//char length_danger_PDU = 15;
//char PDU_danger[46] = "07914570090008F111000A9132410481090004AA026F6B";
//Por simplicidad de código, se hardcodea

void GPRS_config(void){
   dato = 0;   

   /* Inicializar las UART según BAUD_RATE */
   uartConfig(UART_USB, BAUD_RATE);
   uartConfig(UART_232, BAUD_RATE);
   
   /* Activar impresión de códigos de error */
   /*uartWriteString( UART_232, "AT+CMEE=1\r\n");
   delay(1000);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }*/

   /* Activar servicio de mensajes por texto */
   uartWriteString( UART_232, "AT+CMGF=1\r\n");
   delay(1000);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
}

void GPRS_alerta(void){
   dato  = 0;
   uartWriteString( UART_232, "AT+CMGS=\"" );
   delay(200);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, dest_number );
   delay(200);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "\"\r\n" );
   delay(200);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "SILO: CONDICION");
   delay(200);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "ES DE ALERTA\x1A");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   delay(300);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
}

void GPRS_critico(void){
   dato  = 0;
   uartWriteString( UART_232, "AT+CMGS=\"" );
   delay(200);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, dest_number );
   delay(200);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "\"\r\n" );
   delay(200);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "SILO: ESTADO");
   delay(200);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, " CRITICO\x1A");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   delay(300);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
}

void GPRS_set_dest_num(char *dest_num){
   strcpy(dest_number, dest_num);
}

char* GPRS_get_dest_num(void){
   strcpy(dest_aux, dest_number);
   return dest_aux;
}