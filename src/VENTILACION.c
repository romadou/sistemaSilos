/**
 * @brief Controlador de la ventilación del sistema
 * 
 * @file VENTILACION.c
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#include "sapi.h"
#include "VENTILACION.h"
#include "tipos.h"
#include "proyectoSilos.h"

uint8 VENTILACION_actuar(uint8 tempInterior, uint8 tempExterior, uint8 humInterior, uint8 humExterior, uint8 tempVentilacion){
	//Además de las condiciones de temperatura y humedad, los datos deben ser validos, sino no se ventila
	if((tempInterior!=DATO_INVALIDO)&& (tempExterior!=DATO_INVALIDO) &&(tempInterior>tempVentilacion) && (tempExterior<=tempVentilacion) && (humExterior<humInterior)){
		gpioWrite(ENET_RXD1,1);
		return 1;
	}
	else{
		gpioWrite(ENET_RXD1,0);
		return 0;
	}
}

void VENTILACION_Init(void){
	gpioConfig( ENET_RXD1, GPIO_OUTPUT );
}  