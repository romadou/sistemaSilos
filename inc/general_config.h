/**
 * @file general_config.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#ifndef _GENERAL_CONFIG_H
#define _GENERAL_CONFIG_H

#ifndef TEMP_MAX
#define TEMP_MAX 80
#endif

#ifndef TEMP_MIN
#define TEMP_MIN 0
#endif

#ifndef HUM_MAX
#define HUM_MAX 100
#endif

#ifndef HUM_MIN
#define HUM_MIN 0
#endif

#ifndef TEMP_SET_OK
#define TEMP_SET_OK 0
#endif

#ifndef TEMP_SET_OK
#define TEMP_SET_OK 0
#endif

#ifndef TEMP_TOO_LOW
#define TEMP_TOO_LOW 1
#endif

#ifndef TEMP_TOO_HIGH
#define TEMP_TOO_HIGH 2
#endif

#ifndef HUM_SET_OK
#define HUM_SET_OK 0
#endif

#ifndef HUM_TOO_LOW
#define HUM_TOO_LOW 1
#endif

#ifndef HUM_TOO_HIGH
#define HUM_TOO_HIGH 2
#endif

void CONFIG_init(void); /* Configuración inicial de los parámetros del sistema */
int CONFIG_get_desired_temp(void); /* Pedido de la temperatura configurada como deseada para el sistema */
int CONFIG_set_desired_temp(int new_temp); /* Configuración de la temperatura deseada para el sistema */
int CONFIG_get_desired_hum(void); /* Pedido de la humedad configurada como deseada para el sistema */
int CONFIG_set_desired_hum(int new_hum); /* Configuración de la humedad deseada para el sistema */

#endif