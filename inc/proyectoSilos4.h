/* Copyright 2014, Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _PROYECTOSILOS4_H_
#define _PROYECTOSILOS4_H_

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

#define MAXSLAVES 32 /*Cantidad máxima de esclavos que tendrá la tabla de datos*/
#define COLUMN_DATA 4/* Cantidad de columnas que tendrá la tabla de datos (columnas ej.: activo, temp, hum, etc)*/
#define C_STATE 0 /* En la columna 0 está el estado (activo o inactivo) de c/esclavo*/
#define C_INACTIVE 1 /*En la columna 1 está la cantidad de veces consecutivas que estuvo inactivo c/esclavo*/
#define C_TEMP 2 /*En la columna 2 está la última temperatura en °C de c/esclavo*/
#define C_HUM 3 /*En la columna 3 está la última humedad relativa (%) de c/esclavo*/


/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*==================[end of file]============================================*/
#endif /* #ifndef _PROYECTOSILOS4_H_ */

