/**
 * @file uart.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#ifndef _UART_H_
#define _UART_H_

#include "chip.h"
#include "stdint.h"
#include "cmsis.h"

#define UART_RS485 		0
#define UART_USBX 		2
#define UART_RS232		3

#define UART_0 			4
#define UART_2			5


#define UART_RS485_TXD_P  	9
#define UART_RS485_TXD_P_  	5
#define UART_RS485_RXD_P    9
#define UART_RS485_RXD_P_   6
#define UART_RS485_DIR_P    6
#define UART_RS485_DIR_P_   2

#define UART_USB_TXD_P   7
#define UART_USB_TXD_P_  1
#define UART_USB_RXD_P   7
#define UART_USB_RXD_P_  2

#define UART_RS232_TXD_P   2
#define UART_RS232_TXD_P_  3
#define UART_RS232_RXD_P   2
#define UART_RS232_RXD_P_  4

#define UART_0_TXD_P   6
#define UART_0_TXD_P_  4
#define UART_0_RXD_P   6
#define UART_0_RXD_P_  5

#define UART_2_TXD_P   1
#define UART_2_TXD_P_  15
#define UART_2_RXD_P   1
#define UART_2_RXD_P_  16

#define BAUDRATE_2048		2048
#define BAUDRATE_2400 		2400
#define BAUDRATE_4800 		4800
#define BAUDRATE_9600 		9600
#define BAUDRATE_19200 		19200
#define BAUDRATE_28800 		28800
#define BAUDRATE_38400 		38400
#define BAUDRATE_57600 		57600
#define BAUDRATE_115200		115200
#define BAUDRATE_230400		230400

#define NO_DATA_RECEIVED_ERROR  1
#define NO_ERROR 				0

void uartConfig(uint8_t uart, uint32_t baudRate); /* Configuración general */
void uartWriteByte(uint8_t uart, uint8_t data); /* Enviar un byte por la terminal UART */
void uartWriteString(uint8_t uart, char *data); /* Enviar una cadena de bytes por la terminal UART */
void uartEnableRxInterrupt(uint8_t uart); /* Habilitar las interrupciones de recepción de la UART */
void uartDisableRxInterrupt(uint8_t uart); /* Deshabilitar las interrupciones de recepción de la UART */
uint8_t uartReceiveByte(uint8_t uart, uint8_t *data); /* Recibir un byte por la terminal UART */
void uartReceiveString(uint8_t uart, uint8_t  data [], uint8_t length); /* Recibir una cadena de bytes por la terminal UART */
void uartResetFIFO(uint8_t uart); /* Resetear el buffer de la UART */

#endif
