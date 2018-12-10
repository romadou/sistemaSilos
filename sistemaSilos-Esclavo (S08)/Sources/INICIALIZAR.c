/*
 * INICIALIZAR.c
 *
 *  Created on: 12-oct-2017
 */

#include <Tipos.h>
#include <RTC.h>
#include <INICIALIZAR.h>
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */


/*internas*/
uint8 establec_comp=0;
state estado;

/*externas*/
extern uint8 TPM_cont;
extern uint8 error1;
extern uint8 error2;
extern uint8 RTC_flagms;
extern uint8 RTC_flagseg;
extern uint8 flanco;
extern uint8 TPM_flag;
extern uint16 arrDatos[50];
extern uint8 contador;
extern uint8 MTIM_flag;


/*Envio de pulsos en alto y en bajo para la respuesta del sensor*/

void enviaPulsobajo(){
	/*************************TPM********************************/
	
	/*Configurar pines del temporizador para proposito general */
	TPM1C0SC_ELS0A=0;
	TPM1C0SC_ELS0B=0;
	/*Deshabilitar la interrupcion del TPM*/
	TPM1C0SC_CH0IE=0;
	
	/*************************RTC********************************/
	
	/*Configurar puerto como salida (Canal 0 del TPM1)*/
	PTCDD_PTCDD0=1;
	/*enviar un pulso en bajo*/
	PTCD_PTCD0=0;
	
	RTC_asignarTiempoCom();
	
	/*Habilito la interrupcion del RTC*/
	RTCSC_RTIE=1;

	estado=ENVIARPULSOALTO;
}

void enviaPulsoalto(){
	/*Cuando se genero la interrupcion*/
	if(RTC_flagseg){	
		/*Se vuelve el flag del RTC a 0 */
		RTC_flagseg=0;
		
		/*Configurar puerto como entrada*/
		PTCDD_PTCDD0=0;
		
		/*enviar un pulso en alto*/
		PTCD_PTCD0=1; //ver si es necesario por presencia de pull up
			
		
		/*Colocar el puerto en modo entrada de captura
		* Con estos dos bits se indica que se quiere un aviso
		* ante la ocurrencia de flanco ascendente o descendente*/
		TPM1C0SC_ELS0A=1;
		TPM1C0SC_ELS0B=1;
				
		/*Habilitar interrupcion para entrada de captura*/
		TPM1C0SC_CH0IE=1;
		
		/*Marcar el flag de interrupcion en 0 (Por las dudas, no necesario)*/
		TPM1C0SC_CH0F=0;

		/*No se vuelve a usar el RTC. Se deshabilita la interrupcion*/
		RTCSC_RTIE=0;
		
		establec_comp=1;
	}
}
void INICIALIZAR_reiniciar(){
	estado=ENVIARPULSOBAJO;
}

void INICIALIZAR_actualizar(){
	switch(estado){
	case ENVIARPULSOBAJO:
		enviaPulsobajo();
		break;
	case ENVIARPULSOALTO:
		enviaPulsoalto();
		break;
	}
}
