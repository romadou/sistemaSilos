/**
 * @brief Controlador y protocolo de comunicación de los sensores
 * 
 * @file PMM_sensores.c
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#include <stdio.h>
#include <uart.h>
#include "PMM_sensores.h"

#define COD_STATUS 0x0A		// Código de pedido de estado
#define COD_DATA 0X1E		// Código de pedido de dato

/* Estructuras de mensaje */

/* Estructura pedido */
unsigned char datagram[3];
/*
Datagram:
byte 0: 1;
byte 1: ID sensor;
byte 2: command;
*/

/* Estructura respuesta */
unsigned char resp[5];
/*
Resp_x:
byte 0: 0;
byte 1: ID sensor;
byte 2-3: data;
byte 4: checksum;
*/


void PMM_init(void) {
	uartConfig(UART_RS485, BAUDRATE_9600);
	uartEnableRxInterrupt(4);
}

void PMM_setPaq(unsigned char id_sensor, operacion cod_op, unsigned char *paq) {
	int i, j=0;
	datagram[0] = 1;
	datagram[1] = id_sensor;
	if (cod_op == COD_STATUS){
		datagram[2] = COD_STATUS;
	}
	else{
		datagram[2] = COD_DATA;	
	}
	for (i=0;i<3;i++){
		paq[j] = datagram[j];
		j++;
	}
}	

unsigned char PMM_verify(unsigned char *paq, unsigned char id_sensor) {
	if (paq[0] == 0){
		if (paq[1] == id_sensor){
			return 1;
		}
	}
	return 0;
}

unsigned char PMM_getData(unsigned char *paq, unsigned char id_sensor, unsigned char *temp, unsigned char *hum) {
	int i, j=0;
	for (i=0;i<5;i++){
		resp[j] = paq[j];
		j++;
	}
	if (resp[0] == 0){
		if (resp[1] == id_sensor){
			*temp = resp[3];
			*hum = resp[2];
			if(resp[4] == (*temp+*hum)){
				return 1;
			}
		}
	}
	return 0;

}
