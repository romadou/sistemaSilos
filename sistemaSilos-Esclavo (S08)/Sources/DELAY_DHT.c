/*
 * INICIALIZAR.c
 *
 *  Created on: 12-oct-2017
 */

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#include <Tipos.h>
#include <DELAY_DHT.h>
#include <MTIM.h>
#include <TPM.h>
#include <INICIALIZAR.h>


/*Internas*/
uint8 contflancos=0;
uint8 tiempo=0;

/*Externas*/
extern volatile uint16 tiempoant;
extern volatile uint16 tiempoact;
extern uint8 trans_completa;
extern uint8 TPM_cont;
extern uint8 RTC_flagms;
extern uint8 flanco;
extern uint8 TPM_flag;
extern uint16 arrDatos[50];
extern uint8 contador;
extern uint8 MTIM_flag;


void DELAY_DHT_actualizar(){
	/*CH0F*/
	//Configuracion periferico MTIM
	MTIMSC_TRST=1;
	//MTIMSC_TSTP=0;
	MTIMSC_TOIE=1;
	MTIM_flag=0;
	TPM_cont=0;
	TPM_flag=0;

	//Espera a recibir todos los datos o al temporizador
	while((TPM_cont<39) && (MTIM_flag!=1)){
		/*Se cuenta la cantidad de interrupciones o cantidad de flancos detectados*/
		TPM_flag=0;
		//Espera recepcion de inicio de transferencia
		while((trans_completa!=1)&& (MTIM_flag!=1)){
			//Se genero una interrupcion por entrada de captura
			if(TPM_flag==1){
				TPM_flag=0;
				arrDatos[TPM_cont]=tiempoact-tiempoant;
				TPM_cont++;
				if(TPM_cont==2){
				  TPM_cont=0;
				  //Entre 77 y 82 us
				  if((arrDatos[0]>=616) && (arrDatos[0]<=656) && (arrDatos[1]>=616) && (arrDatos[1]<=656))
					trans_completa=1;
				}
				
			}
		}
		//Espera recepcion de datos
		while((TPM_cont<40) && (MTIM_flag!=1)){
			//flanco descendente
			if((TPM_flag==1) && (PTCD_PTCD0==0)){
				TPM_flag=0;
				arrDatos[TPM_cont]=tiempoact-tiempoant;
				TPM_cont++;

			}
		}
	}
	MTIMSC_TOIE=0;
	//Si se recibieron todos los valores
	if((MTIM_flag==0) && (trans_completa==1)){
		for(contador=0;contador<40;contador++)
			arrDatos[contador]=arrDatos[contador]/8;
	 }
	 else{
		MTIM_flag = 0;
		trans_completa=2;	
	   }
	TPM_flag = 0;
	TPM_cont = 0;	
}

