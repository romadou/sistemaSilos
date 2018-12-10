/*
 * ESPERANDO.c
 *
 *  Created on: 12-oct-2017
 */

#include <Tipos.h>
#include "derivative.h" /* include peripheral declarations */
#include <RTC.h>
#include <SCI.h>

//Externas
extern uint8 a1,a2;
extern uint8 inicio_sensado;
extern uint8 RTC_flagseg;
extern uint8 flag_envdato;
extern uint8 inic_rec;
extern uint8 inic_trans;
extern uint8 SCI_flagrec;

void ESPERANDO_actualizar(){
	//si se envio un dato anteriormente y es tiempo de iniciar el sensado
	//if((flag_envdato==2) && (RTC_flagseg==1)){
	    if((RTC_flagseg==1) || (flag_envdato==2)){
		RTC_reiniciarflag();
		//Deshabilitar interrupcion del RTC
		RTC_deshabilitarint();
		SCI_deshabintRec();
		inicio_sensado=1;
		flag_envdato=0;
	
	}
	//Si se recibio un pedido de id o dato de sensado
	else if (SCI_flagrec==1) {
		RTC_reiniciarflag();
		//Deshabilitar interrupcion del RTC
		RTC_deshabilitarint();
		inic_rec=1;
		SCI_flagrec=0;
	}
	
}
