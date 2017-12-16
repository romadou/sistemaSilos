/*
* PMM_sensores.h
*
*  Created on: 16/12/2017
*      Author: Madou
*/

#ifndef PMM_SENSORES_H_
#define PMM_SENSORES_H_

void PMM_init(void); /* Inicialización de la comunicación */
void PMM_verify(void); /* Verificación del estado de cada uno de los sensores */
unsigned char PMM_getData(unsigned char *information); /* Obyención de los valores medidos por cada uno de los sensores */
unsigned char PMM_testTx(void); /* Verificación del correcto funcionamiento de la transmisión */

#endif /* PMM_SENSORES_H_ */
