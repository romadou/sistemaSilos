/*
 * TPM.c
 *
 *  Created on: 25/02/2018
 */

#include <Tipos.h>
/*Para llevar el control de la cantidad de bytes recibidos*/
unsigned char TPM_cont=0;
volatile unsigned char TPM_flag=0;
unsigned char flanco=1;
uint8 valorasc;
volatile uint16 tiempoact=0;
volatile uint16 tiempoant=0;

extern uint16 arrDatos[50];

/*Handler para la rutina de servicio de interrupcion*/
void TPM_handler(){
		/*Si es un flanco ascendente*/
		if(flanco==1)
			flanco=0;
		else{
			arrDatos[TPM_cont]=tiempoact-tiempoant;
			TPM_cont++;
			flanco=1;
		}
}
