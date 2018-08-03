/**
 * @file PMM_sensores.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#ifndef PMM_SENSORES_H_
#define PMM_SENSORES_H_


typedef enum {ESTADO, DATA} operacion;

void PMM_init(void); /* Inicializaci�n de la comunicaci�n */

/* Armado del paquete correspondiente al pedido de estado o de informaci�n que ser� enviado al sensor recibido por par�metro */
/* Variables
 * Entrada: 
 *		id_sensor: ID del sensor receptor;
 *		cod_op: c�digo de operaci�n (enumerativo - ESTADO/DATA); 
 * Salida:
 *		*paq: paquete de pedido listo para ser transmitido;
 */
void PMM_setPaq(unsigned char id_sensor, operacion cod_op, unsigned char *paq); 

/* Verificaci�n de la correcta recepci�n del mensaje y obtenci�n de los valores medidos por uno de los sensores */
/* Variables
 * Entrada:
 *		*paq: paquete recibido; 
 *		id_sensor: ID del sensor transmisor; 
 * Salida:
 *		*temp: valor de temperatura leido;
 *		*hum: valor de humedad leido;
 * 		0 si el mensaje recibido contiene errores, 1 si fue correcto;
 */
unsigned char PMM_getData(unsigned char *paq, unsigned char id_sensor, unsigned char *temp, unsigned char *hum); 

/* Verificaci�n del mensaje de estado del sensor recibido por par�metro */
/* Variables
 * Entrada:
 *		*paq: paquete recibido; 
 *		id_sensor: ID del sensor transmisor; 
 * Salida:
 *		0 si el mensaje recibido contiene errores, 1 si fue correcto;
 */
unsigned char PMM_verify(unsigned char *paq, unsigned char id_sensor); 

#endif /* PMM_SENSORES_H_ */
