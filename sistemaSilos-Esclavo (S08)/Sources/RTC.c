/*
 * RTC.c
 *
 *  Created on: 19-oct-2017
 */
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <Tipos.h>

uint16 tiempoint=0;
uint8 RTC_flagseg=0;
volatile unsigned char RTC_flagms=0;


/**
 * Funcion llamada desde la ISR
 */
void RTC_handler(){
	RTC_flagseg=1;
}

/**
 * Configurar interrupcion cada 3s aproximadamente
 */
void RTC_asignarTiempoRec(){
	RTCSC=0b11001110;
	RTCMOD=0b11001000;
}

/**
 * Configurar interrupcion cada 18ms aproximadamente
 */
void RTC_asignarTiempoCom(){
	RTCSC=0b10001000;
	RTCMOD=0b00010001;
}

/**
 * Reset del flag del RTC
 */
void RTC_reiniciarflag(){
	RTC_flagseg=0;
}

void RTC_habilitarint(){
	RTCSC_RTIE=1;
}

void RTC_deshabilitarint(){
	RTCSC_RTIE=0;
}

