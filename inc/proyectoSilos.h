/**
 * @file proyectoSilos.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#ifndef _PROYECTOSILOS4_H_
#define _PROYECTOSILOS4_H_

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
#define CANT_SLAVES 2
#define MAXSLAVES 32 /*Cantidad máxima de esclavos que tendrá la tabla de datos*/
#define COLUMN_DATA 4/* Cantidad de columnas que tendrá la tabla de datos (columnas ej.: activo, temp, hum, etc)*/
#define C_STATE 0 /* En la columna 0 está el estado (activo o inactivo) de c/esclavo*/
#define C_INACTIVE 1 /*En la columna 1 está la cantidad de veces consecutivas que estuvo inactivo c/esclavo*/
#define C_TEMP 2 /*En la columna 2 está la última temperatura en °C de c/esclavo*/
#define C_HUM 3 /*En la columna 3 está la última humedad relativa (%) de c/esclavo*/

#define TEMP_ALERTA 10

#define ACTIVE 1 
#define INACTIVE 0
#define MAX_INACTIVE 30/*Cantidad máxima de veces que puede estar inactivo un componente hasta ser notificado*/

#define DETECT_TASK 4 /*indicador de tarea DetectActiveSlavesTask*/
#define DATA_TASK 5 /*indicador de tarea TakeDataSlavesTask*/


/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*==================[end of file]============================================*/
#endif /* #ifndef _PROYECTOSILOS4_H_ */

