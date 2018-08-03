/**
 * @file VENTILACION.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#include "tipos.h"
#ifndef VENTILACION_H_
#define VENTILACION_H_

/* Inicializa el pin correspondiente como salida */
void VENTILACION_Init();

/* Evalúa las condiciones y activa o desactiva el ventilador */
uint8 VENTILACION_actuar(uint8 tempInterior, uint8 tempExterior, uint8 humInterior, uint8 humExterior, uint8 tempVentilacion);

#endif /* VENTILACION_H_ */