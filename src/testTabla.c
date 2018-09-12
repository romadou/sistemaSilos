#include "proyectoSilos.h"
#include "sapi.h"

extern uint8_t slaves[MAXSLAVES][COLUMN_DATA];


void ingresarDatos(){	
	uint8_t i;
	slaves[0][0]=1;
	slaves[0][1]=0;
	slaves[0][2]=21;
	slaves[0][3]=54;

	slaves[1][0]=1;
	slaves[1][1]=0;
	slaves[1][2]=23;
	slaves[1][3]=62;

	slaves[2][0]=1;
	slaves[2][1]=29;
	slaves[2][2]=20;
	slaves[2][3]=60;

	slaves[3][0]=1;
	slaves[3][1]=1;
	slaves[3][2]=22;
	slaves[3][3]=59;
	
	slaves[4][0]=1;
	slaves[4][1]=0;
	slaves[4][2]=19;
	slaves[4][3]=80;
	
	for(i=5; i<MAXSLAVES; i++){
		slaves[i][0]=0;
		slaves[i][1]=0;
		slaves[i][2]=20+i;
		slaves[i][3]=80+i;
	}
		
	
}