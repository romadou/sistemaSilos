#include "sapi.h"
#ifndef MEF_H_
#define MEF_H_
void MEF_Init();
void MEF_updateState(uint8 critico);

void MEF_updateOutput(uint8_t tempi, uint8_t tempe, uint8_t humi, uint8_t hume, uint8_t sensores_activos, uint8_t sensorCaido, uint8_t vent);
#endif /* MEF_H_ */

#ifndef NOT_PRESSED
#define NOT_PRESSED 's'
#endif