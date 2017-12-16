/*
* PMM_sensores.h
*
*  Created on: 16/12/2017
*      Author: Madou
*/

#ifndef PMM_SENSORES_H_
#define PMM_SENSORES_H_

void PMM_init(void); /* Inicializaci�n de la comunicaci�n */
void PMM_verify(void); /* Verificaci�n del estado de cada uno de los sensores */
unsigned char PMM_getData(unsigned char *information); /* Obyenci�n de los valores medidos por cada uno de los sensores */
unsigned char PMM_testTx(void); /* Verificaci�n del correcto funcionamiento de la transmisi�n */

#endif /* PMM_SENSORES_H_ */
