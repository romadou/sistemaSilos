/**
 * @brief Controlador del módulo GPRS SIM800L
 * 
 * @file gprs.c
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#include "gprs.h" 
#include "uart.h"
#include "sapi.h" 
#include "string.h"

/* Variables privadas */
char src_number[11] = "2215410495"; // Número de teléfono origen (SIM insertada)
char dest_number[11] = "3764391747"; // Número de teléfono destino (receptor de los SMS)
char dest_aux[11] = " ";
uint8_t dato;
uint8_t i;

/* Funciones privadas */
void delay_GPRS(uint8_t ms); /* Delay por software (milisegundos) para operaciones del módulo GPRS */

void GPRS_config(void){
   dato = 0;   
   
   // Inicialización de las UART según BAUD_RATE
   uartConfig(UART_USBX, BAUDRATE_38400);
   uartConfig(UART_RS232, BAUDRATE_38400);

   // Activación del servicio de mensajes por texto
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

void delay_GPRS(uint8_t ms){
    volatile uint64_t tiempo;
    for(tiempo=0;tiempo<=20400*ms;tiempo++);
}
