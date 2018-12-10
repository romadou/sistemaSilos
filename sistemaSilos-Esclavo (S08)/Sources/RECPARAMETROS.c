/*
 * RECPARAMETROS.c
 *
 *  Created on: 13-oct-2017
 */

#include <Tipos.h>
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <INICIALIZAR.h>
#include <RTC.h>
#include <SCI.h>
#include <MEF.h>
#include <MTIM.h>

/**********************************VARIABLES**********************************************/


/*Externas*/

extern uint8 TPM_flag;
extern uint8 TPM_cont;
extern uint16 hum_relativa;
extern uint16 temperatura;
extern uint8 humint;
extern uint8 tempint;
extern uint8 checksum;
extern uint8 flag_envdato;
extern uint8 flag_errorrec;
extern uint8 MTIM_flag;
extern uint8 fin_trans; //Cuando cont=39 se pone en 1 y avisa a la MEF que cambie el estado

/*Internas*/
uint8 hum1=255,hum2=255,temp1=255,temp2=255,auxparam=0;
uint16 arrDatos[50];
uint8 contador=0;
uint8 flag_cero=0;
uint8 a1,a2,a3,a4,a5;


/*Conversion de los parametros recibidos a bits y valores enteros con decimal.*/
void RECPARAMETROS_actualizar(){
	if((arrDatos[16])>=68 && (arrDatos[contador])<=75)
		flag_cero=1;
	for(contador=0;contador<40;contador++){	
		if((arrDatos[contador]>=22) && (arrDatos[contador])<=32){
			if(contador<16)
				hum_relativa=hum_relativa<<1;
			else if (contador<32)
				temperatura=temperatura<<1;
			else
				checksum=checksum<<1;
			}
		else if((arrDatos[contador])>=68 && (arrDatos[contador])<=75){
			if(contador<16)
				hum_relativa=(hum_relativa<<1)|1;
			else if (contador<32)
				temperatura=(temperatura<<1)|1;
			else
				checksum=(checksum<<1)|1;
				}
	}
	
	//Valores obtenidos de temperatura, humedad y checksum (parte alta y baja)
	a1=hum_relativa;
	a2=hum_relativa >> 8;
	a3=temperatura;
	a4=temperatura >> 8;
	a5=a1+a2+a3+a4;
	
	//Comprobacion de checksum
	if(a5==checksum){
		//Si el valor es negativo
		if (flag_cero){
			//Se almacena un 0
			flag_cero=0;
			temperatura=0;
		}
		//Si la comprobacion es correcta, se comprueban los parametros (hoja de datos)
		if((hum_relativa/10 < 101) && temperatura/10 < 81){
			//Almacenamiento de los valores enteros
			humint=hum_relativa/10;
			tempint=temperatura/10;
			//Se tienen dos datos anteriores
			if((hum1!=255) && (hum2!=255)){
				auxparam=humint;
				humint=(auxparam+hum1+hum2) / 3;
				hum1=hum2;
				hum2=auxparam;
				auxparam=tempint;
				tempint=(auxparam+temp1+temp2) / 3;
				temp1=temp2;
				temp2=auxparam;
			}
			else{
				hum1=hum2;
				hum2=humint;
				temp1=temp2;
				temp2=tempint;
			}
			
		}
	}
	TPM_flag=0;
	TPM_cont=0;
	//Reseteo de tiempos y hab. del flag de interrupcion
	INICIALIZAR_reiniciar();
	RTC_reiniciarflag();
	RTC_asignarTiempoRec();
	RTCSC_RTIE=1;
	SCIC2_RIE=1;
	fin_trans=1;
	
	}


