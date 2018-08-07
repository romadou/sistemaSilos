<<<<<<< HEAD
#include "sapi.h"
#ifndef MEF_H_
#define MEF_H_
void MEF_Init();
void MEF_updateState(uint8 critico);

void MEF_updateOutput(uint8_t tempi, uint8_t tempe, uint8_t humi, uint8_t hume, uint8_t sensores_activos, uint8_t sensorCaido, uint8_t vent);
#endif /* MEF_H_ */
=======
/**
 * @file MEF.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#include "sapi.h"
#ifndef MEF_H_
#define MEF_H_

void MEF_Init(); /* Inicialización de la MEF */
void MEF_updateState(uint8 critico); /* Actualización de estado */
void MEF_updateOutput(uint8_t tempi, uint8_t tempe, uint8_t humi, uint8_t hume, uint8_t sensores_activos, uint8_t sensorCaido, uint8_t vent); /* Actualización de las salidas del sistema, según el estado */

#endif
>>>>>>> 1e9519dcb9abf10e77dac072b899c256c6f4cede

#ifndef NOT_PRESSED
#define NOT_PRESSED 's'
#endif