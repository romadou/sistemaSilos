#include <stdio.h>
#include <uart.h>

#define CANTS 3			//Cantidad de sensores
#define CANTB 5			//Cantidad de bytes emitidos por sensor

#define COD_STATUS 0x0A		//Código de pedido de estado
#define COD_DATA 0X1E		//Código de pedido de dato


/* Variables privadas */
/* Control */
unsigned char sDown;
unsigned char activeS[CANTS];
unsigned char cantVerifS[CANTS];
/* Estructuras de mensaje */
unsigned char datagram[3];
/*
Datagram:
byte 0: 1;
byte 1: ID sensor;
byte 2: comand;
*/
unsigned char resp_status[4];
unsigned char resp_data[8];
/*
Resp_x:
byte 0: 0;
byte 1: ID sensor;
byte 2-end: data;
*/
unsigned char flag_rx = 0;


/* Funciones privadas */
void init_activeS(void);


void PMM_init(void) {
	uartConfig(UART_RS485, BAUDRATE_9600);
	uartDisableRxInterrupt(UART_RS485);
	init_activeS();
	datagram[0] = 1;
	PMM_verify();
}

void PMM_verify(void) {
	int i, j;
	unsigned char e;
	sDown = 0;
	datagram[2] = COD_STATUS;
	for (i = 0, i<CANTS, i++) {
		datagram[1] = i;
		uartWriteString(UART_RS485, datagram);
		while(!timeout());							// FUNCION A VERIFICAR
		e = uartReceiveByte(UART_RS485, resp_status);
		if (e){		
			activeS[i] = 0;
		}
		else{
			activeS[i] = 1;
			for (j=1;j<4;j++){
				uartReceiveByte(UART_RS485, &resp_status[j]);
			}
		}
	}
}

unsigned char PMM_getData(unsigned char *information) {
	int i, j;
	unsigned char e;
	datagram[2] = COD_DATA;
	for (i = 0, i<CANTS, i++) {
		if (activeS[i]) {			//Si el sensor funciona
			datagram[1] = i;
			uartWriteString(UART_RS485, datagram);
			while(!timeout());							// FUNCION A VERIFICAR
			e = uartReceiveByte(UART_RS485, resp_data);
			if (e){		
				if (++cantVerifS[i] == 3){
					activeS[i] = 0;
					sDown = 1;
					cantVerifS[i] = 0;
				}
			}
			else{
				activeS[i] = 1;
				for (j=1;j<7;j++){
					uartReceiveByte(UART_RS485, &resp_data[j]);
				}
				//VERIFICAR QUE DEVUELVE INFORMATION
			}
		}
	}
	return sDown;
}

/*
unsigned char PMM_testTx(void) {
	datagram[1] = 0x7A;  //Un código de identificación random

	datagram[2] = COD_STATUS;
	uartWriteString(UART_RS485, datagram);

	delay(500);

	datagram[2] = COD_DATA;
	uartWriteString(UART_RS485, datagram);
}
*/

void init_activeS(void) {
	int i;
	for (i = 0, i<CANTS, i++) {
		activeS[i] = 0;
		cantVerifS[i] = 0;
	}
}
