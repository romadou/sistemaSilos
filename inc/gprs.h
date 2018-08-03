/**
 * @file gprs.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#ifndef GPRS_H_
#define GPRS_H_

#ifndef BAUD_RATE
#define BAUD_RATE 38400
#endif

void GPRS_config(void); /* Configuración inicial del módulo GPRS */
void GPRS_alerta(void); /* Actuación: envío de SMS por alerta en el sistema */
void GPRS_critico(void); /* Actuación: envío de SMS por situación crítica en el sistema */
void GPRS_set_dest_num(char *dest_num); /* Modificación del número de teléfono destino */
char* GPRS_get_dest_num(void); /* Recuperación del número de teléfono destino */

#endif /* #ifndef GPRS_H_ */