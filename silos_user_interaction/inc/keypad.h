/*
 * keypad.h
 *
 *  Modified on: 07/12/2017
 *      Author: Madou
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

void KEYPAD_init(void); /* Inicializaci�n del teclado */
unsigned char KEYPAD_update(unsigned char *tecla); /* Actualizaci�n del teclado */
unsigned char KEYPAD_numero(unsigned char tecla); /* Comprobaci�n si la entrada corresponde a un n�mero */
unsigned char KEYPAD_char(unsigned char tecla); /* Transformaci�n de c�digo de teclado al caracter correspondiente */

#endif /* KEYPAD_H_ */
