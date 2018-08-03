#ifndef KEYPAD_H_
#define KEYPAD_H_

#ifdef __cplusplus
extern "C" {
#endif

void KEYPAD_init(void); /* Inicialización del teclado */
unsigned char KEYPAD_update(unsigned char *tecla); /* Actualización del teclado */
unsigned char KEYPAD_ScanAutorepeat (unsigned char *pkey);
unsigned char KEYPAD_getkey(unsigned char *key);
unsigned char KEYPAD_numero(unsigned char tecla); /* Comprobación de si la entrada corresponde a un número */


#ifdef __cplusplus
}
#endif

#endif /* KEYPAD_H_ */