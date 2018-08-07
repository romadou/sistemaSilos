<<<<<<< HEAD
#include "tipos.h"
#ifndef VENTILACION_H_
#define VENTILACION_H_
//Inicializa el pin correspondiente como salida
void VENTILACION_Init();

//Evalua las condiciones y activa o desactiva el ventilador
uint8 VENTILACION_actuar(uint8 tempInterior, uint8 tempExterior, uint8 humInterior, uint8 humExterior, uint8 tempVentilacion);
#endif /* VENTILACION_H_ */
=======
/**
 * @file VENTILACION.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#include "tipos.h"
#ifndef VENTILACION_H_
#define VENTILACION_H_

void VENTILACION_Init(); /* Inicialización del pin de ventilación */
uint8 VENTILACION_actuar(uint8 tempInterior, uint8 tempExterior, uint8 humInterior, uint8 humExterior, uint8 tempVentilacion); /* Evaluación de las condiciones y activación/desactivación del ventilador */

#endif
>>>>>>> 1e9519dcb9abf10e77dac072b899c256c6f4cede
