#include "derivative.h" /* include peripheral declarations */
#include <Tipos.h>
#include <MEF.h>
#include <RTC.h>
#include <MTIM.h>
#include <SCI.h>
#include <ESPERANDO.h>
#include <INICIALIZAR.h>
#include <RECPARAMETROS.h>
#include <REC_UC.h>
#include <TRANS_UC.h>
#include <DELAY_DHT.h>



state MEF_estado;

/*internas*/
uint16 hum_relativa=0;
uint16 temperatura=0;
uint8 humint=0;
uint8 tempint=0;
uint8 checksum=0;
uint8 flag_errorrec=0;
uint8 inicio_sensado=0;
uint8 inic_rec=0;
uint8 inic_trans=0;
uint8 fin_trans=0;
uint8 paquetedescart=0;
uint8 trans_completa=0;


/*externas*/
extern uint8 establec_comp;
extern uint8 MTIM_flag;
extern uint8 contRTC;
extern uint8 inicializacion_comp;
extern uint8 pedido485;
extern uint8 inic_completa;
extern uint8 RTC_flagseg;
extern uint8 RTC_flagms;
extern uint8 TPM_cont;
extern uint8 TPM_flag;

/*Estado inicial*/
void MEF_init(){
	MEF_estado=ESPERANDO;
	//Cada 3 segundos se realizan sensados
	RTC_asignarTiempoRec();
	//Habilitar interrupcion del RTC
	RTC_habilitarint();
	//Habilitar interrupcion de Recepcion
	SCI_habintRec();
	//Configurar pines para recepcion del SCI
	SCI_habilitarRec();
}


void MEF_actualizarEstado(){
	switch(MEF_estado){
	case ESPERANDO:
		if(inicio_sensado){
			RTC_reiniciarflag();
			//se coloca nivel logico 0 en el bus de datos (micro <-> sensor)
			PTCD_PTCD0=0;
			inicio_sensado=0;
			MEF_estado=INICIALIZAR;
		}
		else if (inic_rec){
			inic_rec=0;
			MEF_estado=REC_UC;
		}
		break;
	case INICIALIZAR:
			/*La inicializacion termino correctamente*/
			if (establec_comp==1){
				INICIALIZAR_reiniciar();
				establec_comp=0;
				MEF_estado=DELAY_DHT;
			}
		break;
	case DELAY_DHT:
			if(trans_completa==1){
				trans_completa=0;
				MEF_estado=RECPARAMETROS;
			}
			/*Se obtuvo un error. Se repite la operacion
			 * Se reinicia RTC, se habilita la interrupcion y se reinicia INICIALIZAR*/
			else if (trans_completa==2){
				RTC_reiniciarflag();
				INICIALIZAR_reiniciar();
				RTC_asignarTiempoRec();
				RTC_habilitarint();
				SCI_habintRec();
				trans_completa=0;
				MEF_estado=ESPERANDO;
			}
			
	case RECPARAMETROS:
		if((fin_trans==1)){
			fin_trans=0;
			MEF_estado=ESPERANDO;
		}
		break;
	
	case REC_UC:
		if(inic_trans==1){
			inic_trans=0;
			MEF_estado = TRANS_UC;
		}
		else if (paquetedescart==1){
			paquetedescart=0;
			MEF_estado = ESPERANDO;
		}
	break;
	
	case TRANS_UC:
		if(fin_trans==1){
			fin_trans=0;
			MEF_estado = ESPERANDO;
		}
	break;
	
	}
}


void MEF_actualizarSalida(){
	switch(MEF_estado){
	case ESPERANDO:
		ESPERANDO_actualizar();
		break;
	case INICIALIZAR:
		INICIALIZAR_actualizar();
		break;
	case RECPARAMETROS:
		RECPARAMETROS_actualizar();
		break;
	case DELAY_DHT:
		DELAY_DHT_actualizar();
		break;
	case REC_UC:
		REC_UC_actualizar();
		break;
	case TRANS_UC:
		TRANS_UC_actualizar();
		break;
	}

}
