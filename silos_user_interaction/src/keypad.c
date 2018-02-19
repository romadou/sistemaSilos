/*
 * keypad.c
 *
 *  Created on: 03/02/2018
 *      Author: Krasowski - Madou
 */

#include < keypad.h >
#include < sapi_keypad.h >

/* Variables privadas */
// Teclado
keypad_t keypad;

// Filas
uint8_t keypadRowPins[4] = {
  RS232_TXD, // Row 0
  CAN_RD,    // Row 1      			/* MODIFICAR */
  CAN_TD,    // Row 2
  T_COL1     // Row 3
};

// Columnas
uint8_t keypadColPins[4] = {
  T_FIL0,    // Column 0
  T_FIL3,    // Column 1			/* MODIFICAR */
  T_FIL2,    // Column 2
  T_COL0     // Column 3
};

void KEYPAD_init(void){
   keypadConfig(&keypad, keypadRowPins, 4, keypadColPins, 4);
}

unsigned char KEYPAD_update(unsigned char *tecla){
	unsigned char error;
	int *key;
	error = keypadRead(keypad, key);
	*tecla = (unsigned char) (*key);
	return error;
}

unsigned char KEYPAD_numero(unsigned char tecla){
	if ((tecla >= '0') && ('9' >= tecla)) return 1;
	return 0;
}

unsigned char KEYPAD_char(unsigned char tecla){
	static char teclado[] =
	{'1','2','3','A',
			'4','5','6','B',
			'7','8','9','C',
			'*','0','#','D'
	};
	return teclado[tecla];
}
