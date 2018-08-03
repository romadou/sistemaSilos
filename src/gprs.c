/*
 * Fecha: 2018-02-17
 */

#include "gprs.h" 
#include "uart.h"
#include "sapi.h" 
#include "string.h"

char src_number[11] = "2215410495";
//char dest_number[11] = "3764391747";
char dest_number[11] = "2314401890";
char dest_aux[11] = " ";
uint8_t dato;
uint8_t i;


void delay_GPRS(uint8_t ms);

void GPRS_config(void){
   dato = 0;   

   /* Inicializar las UART según BAUD_RATE */
   uartConfig(UART_USBX, BAUDRATE_38400);
   uartConfig(UART_RS232, BAUDRATE_38400);
   
   /* Activar impresión de códigos de error */
   uartWriteString( UART_RS232, "AT+CMEE=1\r\n");
   delay_GPRS(1000);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }

   /* Activar servicio de mensajes por texto */
   uartWriteString( UART_RS232, "AT+CMGF=1\r\n");

}

void GPRS_alerta(void){
   dato  = 0;
   uartWriteString( UART_RS232, "AT+CMGS=\"" );
   delay_GPRS(200);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
   uartWriteString( UART_RS232, dest_number );
   delay_GPRS(200);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
   uartWriteString( UART_RS232, "\"\r\n" );
   delay_GPRS(200);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
   uartWriteString( UART_RS232, "SILO: CONDICION");
   delay_GPRS(200);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
   uartWriteString( UART_RS232, "ES DE ALERTA\x1A");
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
   delay_GPRS(300);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
}

void GPRS_critico(void){
   dato  = 0;
   uartWriteString( UART_RS232, "AT+CMGS=\"" );
   delay_GPRS(200);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
   uartWriteString( UART_RS232, dest_number );
   delay_GPRS(200);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
   uartWriteString( UART_RS232, "\"\r\n" );
   delay_GPRS(200);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
   uartWriteString( UART_RS232, "SILO: ESTADO");
   delay_GPRS(200);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
   uartWriteString( UART_RS232, " CRITICO\x1A");
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
   delay_GPRS(300);
   while( uartReceiveByte( UART_RS232, &dato ) ){
      uartWriteByte( UART_USBX, dato );
   }
}

void GPRS_set_dest_num(char *dest_num){
   strcpy(dest_number, dest_num);
}

char* GPRS_get_dest_num(void){
   strcpy(dest_aux, dest_number);
   return dest_aux;
}

void delay_GPRS(uint8_t ms)
{  volatile uint64_t tiempo;
   for(tiempo=0;tiempo<=20400*ms;tiempo++);
}