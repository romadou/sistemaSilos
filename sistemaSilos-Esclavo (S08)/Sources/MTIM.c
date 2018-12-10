/*
 * MTIM.c
 *
 *  Created on: 24/08/2018
 */

#include <MTIM.h>
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <Tipos.h>

uint8 MTIM_flag=0;

/*Inicializacion del MTIM. Interrupcion des*/
void MTIM_inicializar(){
	  MTIMSC_TRST=1;
	  MTIMSC_TSTP=0;
	  MTIMSC_TOIE=0;
}

/*Habilitar interrupcion*/
void MTIM_habilitarint(){
	  MTIMSC_TOIE=1;
}

/*Deshabilitar interrupcion*/
void MTIM_deshabilitarint(){
	  MTIMSC_TOIE=0;
}
