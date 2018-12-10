#include <SCI.h>
#include "derivative.h" /* include peripheral declarations */
#include <Tipos.h>


uint8 flag_SCIr;
extern uint8 arrRecep[20];
extern uint8 indarrRecep;

uint8 SCI_flagrec=0;
uint8 contrec =0;
uint8 SCI_datagrec=0;
uint8 flag_envdato=0;
uint8 SCI_paqenv=0;
uint8 SCI_transcomp=0;
volatile char datorec;
unsigned char BUFFER_Tx[3];
unsigned char BUFFER_Rx[7];
unsigned char contrx=0;
unsigned char IndiceEscritura;
unsigned char IndiceLectura;
extern uint8 a1,a2;
extern uint8 humint,tempint;


/**
 * Configuracion de pines para la comunicacion
 * Pines de transmision y recepcion como entradas y salidas respectivamente
 * Pines DI y RO como salidas (Para configurar modulo MAX485)
 */
void SCI_inicializar(){
	//Pines de transmision y recepcion
	PTBDD_PTBDD0=0;
	PTBDD_PTBDD1=1;
	
	//Pines DI y RO como salidas
	PTBDD_PTBDD2=1;
	PTBDD_PTBDD3=1;
}

/**
 * Habilita la transferencia de datos estableciendo el valor de los pines DI y RO en '1'
 * 
 */
void SCI_habilitarTrans(){
	PTBD_PTBD2=1;
	PTBD_PTBD3=1;

}


/**
 * Habilita la recepcion de datos configurando los pines DI y RO
 * como entradas
 */
void SCI_habilitarRec(){
	PTBD_PTBD2=0;
	PTBD_PTBD3=0;
	//SCIC2_RIE=1;
}



/*Escribe un caracter en el buffer*/
void SCI_Write_char(char datoenv){
	BUFFER_Tx[IndiceEscritura]=datoenv;
	IndiceEscritura++;
	SCIC2_TIE=1;
}

/*Handler para la ISR de SCI*/
void SCIrx_handler(){
	//Se habilita en el primer caso la interrupcion de Idle Line
	if(contrec==0){
		SCIC2_ILIE=1;
		SCI_flagrec=1;
	}
	//Se recibio interrupcion por linea inactiva
	if(SCIS1_IDLE){
		SCIC2_RIE=0;
		SCIC2_ILIE=0;
		if(BUFFER_Rx[2]==0x1E) SCI_paqenv=DATO;
		else SCI_paqenv=ESTADO;
		contrec=0;
		//Se recibio el paquete
		SCI_datagrec=1;
	}
	else{
		BUFFER_Rx[contrec]=datorec;
		contrec++;
	}
}

/*Determina si el paquete corresponde al ID del micro */
uint8 SCI_verifPaquete(){
	if((BUFFER_Rx[0]==1) && (BUFFER_Rx[1]==ID))
		return 1;
	else return 0;
}


/*Handler para la ISR de SCI (transferencia)*/
void SCItx_handler(){
if(IndiceLectura<IndiceEscritura){
		if(SCIS1_TDRE==1){
			SCID=BUFFER_Tx[IndiceLectura];
			IndiceLectura++;
		}
	}
	else{
		IndiceLectura=0;
		IndiceEscritura=0;
		SCIC2_TIE=0;
	}
}

void SCI_deshabIdleint(){
	  SCIC2_ILIE=0;
}

void SCI_habIdleint(){
	  SCIC2_ILIE=1;
}


void SCI_habintRec(){
	SCIC2_RIE=1;
}

void SCI_deshabintRec(){
	SCIC2_RIE=0
	;
}
