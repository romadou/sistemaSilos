#include <stdio.h>
#include <uart.h>

#define COD_STATUS 0x0A		//Código de pedido de estado
#define COD_DATA 0X1E		//Código de pedido de dato


/* Variables privadas */
/* Control */
//unsigned char error;
/* Estructuras de mensaje */
/*Estructura pedido*/
unsigned char datagram[3];
/*
Datagram:
byte 0: 1;
byte 1: ID sensor;
byte 2: comand;
*/
/*Estructura respuesta*/
unsigned char resp[6];
/*
Resp_x:
byte 0: 0;
byte 1: ID sensor;
byte 2-end: data;
*/


void PMM_init(void) {
	uartConfig(UART_RS485, BAUDRATE_9600);
}

void PMM_setPaq(unsigned char id_sensor, operacion cod_op, unsigned char *paq) {
	int i;
	datagram[0] = 1;
	datagram[1] = id_sensor;
	if (cod_op == ESTADO){
		datagram[2] = COD_STATUS;
	}
	else{
		datagram[2] = COD_DATA;	
	}
	for (i=0;i<3;i++){
		*paq++ = *datagram++;
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
	int i;
	for (i=0;i<6;i++){
		*resp++ = *paq++;
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