/**
 * @brief Controlador del teclado matricial 4x4 del sistema
 * 
 * @file keypad.c
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */
#include "keypad.h"
#include "chip.h"
#include "lcd.h"
#include "board.h"
#include "cmsis.h"
#include "sapi.h"

#define OUTPUT	1
#define INPUT	0

uint8_t evaluarCol(uint8_t *pkey,uint8_t i);
uint8_t KEYPAD_Scan(uint8_t*pkey);
static void pausems(uint32_t t);

uint8_t teclado[] =
{ '1','2','3','A',
'4','5','6','B',
'7','8','9','C',
'*','0','#','D' };

uint8_t key=0;
uint8_t x=0,y=0;
static uint8_t KeyChanged;
static uint8_t valid_key;


static uint32_t pausems_count;

/**
 * @brief Configuración inicial del teclado matricial
 * 
 */
void KEYPAD_init(){
	/* Se configuran los primeros pines como salida y los últimos como entrada */

	// CAN_RD P3_1 GPIO5[8]
	Chip_SCU_PinMux(3,1,SCU_MODE_INACT|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC4);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 5, ( 1 << 8 ), OUTPUT );

	// CAN_TD P3_2 GPIO5[9]
	Chip_SCU_PinMux(3,2,SCU_MODE_INACT|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC4);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 5, ( 1 << 9 ), OUTPUT );

	// T_col1 P7_4 GPIO3[12]
	Chip_SCU_PinMux(7,4,SCU_MODE_INACT|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 3, ( 1 << 12 ), OUTPUT );

	// T_fil0 P4_0 GPIO2[0]
	Chip_SCU_PinMux(4,0,SCU_MODE_INACT|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 2, ( 1 << 0 ), OUTPUT );

	/* Entradas. Se habilitan las resistencias pull-up para mantener un valor logico '1' cuando no se está apretando nada */
	// T_fil3 P4_3 GPIO2[3]
	Chip_SCU_PinMux(4,3,SCU_MODE_PULLUP|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 2, ( 1 << 3 ), INPUT );

	//T_fil2 P4_2 GPIO2[2]
	Chip_SCU_PinMux(4,2,SCU_MODE_PULLUP|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 2, ( 1 << 2 ), INPUT );

	//T_col0 P1_5 GPIO1[8]
	Chip_SCU_PinMux(1,5,SCU_MODE_PULLUP|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 1, ( 1 << 8 ), INPUT );

	//T_fil1 P4_1 GPIO2[1]
	Chip_SCU_PinMux(4,1,SCU_MODE_PULLUP|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 2, ( 1 << 1 ), INPUT );

}

/**
 * @brief Escaneo del teclado en busca de una tecla presionada
 * Control contra detecciones duplicadas
 * 
 * @param pkey Tecla presionada, si la hay
 * @return uint8_t "1" si hay tecla presionada, "0" si no la hay
 */
uint8_t KEYPAD_ScanAutorepeat (uint8_t *pkey){
	static char old_key, last_valid_key;
	uint8_t key='s';
	if(!(KEYPAD_Scan(&key))){
		old_key='s';
		last_valid_key='s';
		return 0;
	}
	else{
		if(key==old_key){
			if(key!=last_valid_key){
				*pkey=key;
				last_valid_key=key;
				KeyChanged=1;
				valid_key=key;
				return 1;
			}
		}
		old_key=key;
		return 0;
	}
}

/**
 * @brief Barrido del teclado en busca de una tecla presionada
 * 
 * @param pkey Tecla presionada, si la hay
 * @return uint8_t "1" si hay tecla presionada, "0" si no la hay
 */
uint8_t KEYPAD_Scan(uint8_t *pkey){

	uint8_t i;

	/* Valor lógico 1 a los pines configurados como salida */
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 8, 1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 9, 1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 12, 1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 0, 1);


	for (i=0; i<4; i++){
		switch(i){
			case 0:
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 8, 0);
				break;
			case 1:
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 8, 1);
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 9, 0);
				break;
			case 2:
				
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 9, 1);
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 12, 0);
				break;
			case 3:
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 12, 1);
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 0, 0);
				break;
		}
		

		if(Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, 2, 3)==0){
			*pkey=teclado[4*i+0];
			return 1;
		}
		else if (Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, 2, 2)==0){
			*pkey=teclado[4*i+1]; 
			return 1;
		}	
		else if (Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, 1, 8)==0){
			*pkey=teclado[4*i+2];
			return 1;
		}	
		else if (Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, 2, 1)==0){
			*pkey=teclado[4*i+3];
			return 1;
		}
		
	}
	return 0;

}

/**
 * @brief Decisión sobre si una tecla presionada es un dígito
 * 
 * @param tecla Tecla presionada
 * @return unsigned char "1" si es un dígito, "0" si no lo es
 */
unsigned char KEYPAD_numero(unsigned char tecla){
	if ((tecla >= '0') && ('9' >= tecla)) return 1;
	return 0;
}

/**
 * @brief Devuelve la tecla presionada, si la hay
 * 
 * @param_out key Tecla presionada 
 * @return uint8_t "1" si hay tecla válida presionada, "0" si no la hay
 */
uint8_t KEYPAD_getkey(uint8_t *key){
	/* Evita que se tome una tecla 2 veces */
	if(!KeyChanged)
		return 0;
	else{
		KeyChanged=0;
		*key=valid_key;
		return 1;
	}
}