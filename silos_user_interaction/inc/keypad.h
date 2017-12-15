/*
 * keypad.h
 *
 *  Modified on: 07/12/2017
 *      Author: Madou
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

void KEYPAD_init(void); /* Inicialización del teclado */
unsigned char KEYPAD_update(unsigned char *tecla); /* Actualización del teclado */
unsigned char KEYPAD_numero(unsigned char tecla); /* Comprobación si la entrada corresponde a un número */
unsigned char KEYPAD_char(unsigned char tecla); /* Transformación de código de teclado al caracter correspondiente */

#endif /* KEYPAD_H_ */
