/**
 * @file keypad.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#ifdef __cplusplus
extern "C" {
#endif

void KEYPAD_init(void); /* Inicialización del teclado */
unsigned char KEYPAD_ScanAutorepeat (unsigned char *pkey); /* Actualización del teclado */
unsigned char KEYPAD_getkey(unsigned char *key); /* Recuperación de la última tecla detectada, si la hay */
unsigned char KEYPAD_numero(unsigned char tecla); /* Comprobación de si la entrada corresponde a un número */


#ifdef __cplusplus
}
#endif

#endif
