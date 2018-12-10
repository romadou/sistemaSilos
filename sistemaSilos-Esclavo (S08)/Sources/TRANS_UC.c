/*
 * ENVPARAMETROSCOM.c
 *
 *  Created on: 15-oct-2017
 */
#include <Tipos.h>
#include <SCI.h>
#include <MEF.h>
#include <RTC.h>
#include "derivative.h" /* include peripheral declarations */


/*Externas*/
extern uint8 flag_envdato;
extern uint8 fin_trans;
extern uint8 SCI_paqenv;
extern uint8 SCI_transcomp;
extern uint8 humint;
extern uint8 tempint;


/*Internas*/
uint8 borrar=0;

void TRANS_UC_actualizar(){
	
	//pedido de estado
		SCIC2_TIE=1;
		if(SCI_paqenv==ESTADO){
			SCI_Write_char(0);
			SCI_Write_char(ID);
		}
		//pedido de dato
		else if(SCI_paqenv==DATO){
		    SCI_Write_char(0);
		    SCI_Write_char(ID);
		    SCI_Write_char(humint);
		    SCI_Write_char(tempint);
		    SCI_Write_char(humint+tempint);
	  		flag_envdato=2;
		    
		}
	  	while (SCIS1_TC==0); //transmisión en espera completa 
		//finalizo la transferencia
	  	SCI_habilitarRec();
		RTCSC_RTIE=1;
		SCIC2_RIE=1;
	    fin_trans=1;
		}	  

