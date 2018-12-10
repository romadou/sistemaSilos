/*
 * RTC.h
 *
 *  Created on: 19-oct-2017
 *      Author: a
 */

#ifndef RTC_H_
#define RTC_H_

void RTC_handler(void);
void RTC_asignartiempo(unsigned char tiempoasig);
void RTC_reiniciarflag(void);
void RTC_asignarTiempoRec(void);
void RTC_asignarTiempoCom(void);
void RTC_habilitarint(void);
void RTC_deshabilitarint(void);

#endif /* RTC_H_ */
