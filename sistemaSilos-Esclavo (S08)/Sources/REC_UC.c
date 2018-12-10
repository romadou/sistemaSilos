/*
 * RECPARAMETROS.c
 *
 *  Created on: 13-oct-2017
 */

#include <Tipos.h>
#include <SCI.h>
#include <MEF.h>
#include <RTC.h>
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

/*Externas*/
extern uint8 RTC_flagseg;
extern uint8 inic_trans;
extern uint8 SCI_datagrec;
extern uint8 paquetedescart;

/*obtencion del datagrama e indicacion para la transicion de estado*/
void REC_UC_actualizar(){
	
	if(SCI_datagrec){
		SCI_datagrec=0;
		//El paquete corresponde al micro
		if(SCI_verifPaquete()){
			inic_trans=1;
			SCI_habilitarTrans();
			SCIC2_RIE=0;
		}
		else{
			paquetedescart=1;
			SCIC2_RIE=1;
			//RTC_asignarTiempoRec();
			RTCSC_RTIE=1;
			SCIC2_RIE=1;
		}
	}
}
