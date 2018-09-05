/**
 * @file proyectoSilos.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#ifndef _PROYECTOSILOS_H_
#define _PROYECTOSILOS_H_


#define CANT_SLAVES 2
#define MAXSLAVES 32 /* Cantidad máxima de esclavos que tendrá la tabla de datos */
#define COLUMN_DATA 4/* Cantidad de columnas que tendrá la tabla de datos (columnas ej.: activo, temp, hum, etc) */
#define C_STATE 0 /* En la columna 0 está el estado (activo o inactivo) de c/esclavo */
#define C_INACTIVE 1 /* En la columna 1 está la cantidad de veces consecutivas que estuvo inactivo c/esclavo */
#define C_TEMP 2 /* En la columna 2 está la última temperatura en °C de c/esclavo */
#define C_HUM 3 /* En la columna 3 está la última humedad relativa (%) de c/esclavo */

#define TEMP_ALERTA 24
#define DATO_INVALIDO 255

#define ACTIVE 1 
#define INACTIVE 0
#define MAX_INACTIVE 30 /* Cantidad máxima de veces que puede estar inactivo un componente hasta ser notificado */

#define DETECT_TASK 4 /* Indicador de tarea DetectActiveSlavesTask */
#define DATA_TASK 5 /* Indicador de tarea TakeDataSlavesTask */

#endif /* _PROYECTOSILOS_H_ */

