/*
 * Fecha: 2018-02-17
 */

#include "gprs.h" 
#include "sapi.h" 
#include <string.h>


char src_number[10] = "2215410495";
char dest_number[10] = "2314401890";

//Regenerar PDU: Por ahora dice "testing"
char length_alert_PDU = 20;
//char PDU_alert[56] = "07914570090008F111000AA132410481090000FF07F4F29C9E769F01";
//Por simplicidad de código, se hardcodea

//Regenerar PDU: Por ahora dice "ok"
char length_danger_PDU = 15;
//char PDU_danger[46] = "07914570090008F111000A9132410481090004AA026F6B";
//Por simplicidad de código, se hardcodea

void GPRS_config(void){
   uint8_t dato = 0;   

   /* Inicializar las UART según BAUD_RATE */
   uartConfig(UART_USB, BAUD_RATE);
   uartConfig(UART_232, BAUD_RATE);
   
   /* Activar impresión de códigos de error */
   /*uartWriteString( UART_232, "AT+CMEE=1\r\n");
   delay(1000);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }*/

   /* Activar servicio de mensajes por PDU */
   uartWriteString( UART_232, "AT+CMGF=0\r\n");
   delay(1000);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
}

void GPRS_alerta(void){
   uint8_t i;
   uint8_t dato  = 0;
   //char mens[28] = "SILO: CONDICIONES DE ALERTA";
   uartWriteString( UART_232, "AT+CMGS=20\r\n" );
   delay(200);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "079145");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "70090");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "008F");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   delay(300);
   uartWriteString( UART_232, "11100");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "0AA13");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "24104");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   delay(300);
   uartWriteString( UART_232, "81090");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "000FF");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "07F4F");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   delay(300);
   uartWriteString( UART_232, "29C9E");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "769F01\x1A")
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   delay(300);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
}

void GPRS_critico(void){
   uint8_t i;
   uint8_t dato  = 0;
   //char mens[21] = "SILO: ESTADO CRITICO";
   uartWriteString( UART_232, "AT+CMGS=15\r\n" );
   delay(200);
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "07914");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "57009");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "0008F");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   delay(300);
   uartWriteString( UART_232, "11100");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "0A913");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "24104");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   uartWriteString( UART_232, "81090");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   delay(300);
   uartWriteString( UART_232, "004AA");
   while( uartReadByte( UART_232, &dato ) ){
      uartWriteByte( UART_USB, dato );
   }
   delay(300);
   //con Ctrl-Z final
   uartWriteString( UART_232, "026F6B\x1A");
   //con Esc final
   //uartWriteString( UART_232, "026F6B\x1B");
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
   char dest_aux[10];
   strcpy(dest_aux, dest_number);
   return dest_aux;
}