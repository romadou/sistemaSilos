/**
 * @brief Controlador del display lcd
 * 
 * @file lcd.c
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

/*
Configuracion de pines como E/S y valores logicos:
https://groups.google.com/forum/#!topic/ciaa-firmware/fjderuTG2hk

Funcion retardo (NO sapi, solo retardo bloqueante con valores de constantes):
https://github.com/capse3Co2017/capse3Co_Nivel2/blob/master/Alumnos/Turno2/EricPernia/Nivel1/exmen/libs/sapi/api_reference_es.md
*/

#include "lcd.h"
#include "chip.h"
#include "board.h"
#include "cmsis.h"

#define OUTPUT	1
#define INPUT	0

/* Configuracion del display */
static char lcd_mode;

/* Representacion del caracter */

union ubyte
{
	char _byte;
	struct
	{
		unsigned char b0 : 1;
		unsigned char b1 : 1;
		unsigned char b2 : 1;
		unsigned char b3 : 1;
		unsigned char b4 : 1;
		unsigned char b5 : 1;
		unsigned char b6 : 1;
		unsigned char b7 : 1;
	} bit;
};

/* Delay por software para operaciones de teclado (milisegundos) */
static void LCD_delay_ms(uint8_t ms){
	volatile uint64_t tiempo;
	for(tiempo=0;tiempo<=20400*ms;tiempo++);
}

/* Delay por software para operaciones de teclado (microsegundos) */
static void LCD_delay_us(uint8_t us){
	volatile uint64_t tiempo;
	for(tiempo=0;tiempo<=21*us;tiempo++); // 20400/1000
}


void LCD_send_nibble(char data){
	union ubyte my_union;
	my_union._byte = data;

	/* Se envían los parámetros */
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 13, my_union.bit.b3);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 3, my_union.bit.b2);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 15, my_union.bit.b1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 5, my_union.bit.b0);

	LCD_delay_us(43);

	/* Se habilita el LCD */
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 7, 1);

	LCD_delay_us(2);

	/* Se deshabilita el LCD */
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 7, 0);
}




void LCD_send_byte(char address, char data){

	if(address==0)
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 8, 0); // Pin R/S
	else
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 8, 1);
	

	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 7, 0); // Pin E=0


	LCD_send_nibble(data >> 4);     // Parte alta
	LCD_send_nibble(data & 0x0f);   // Parte baja

}

void LCD_pos_xy(char x, char y){
	char address;
	if (y==1) address = LCD_SEC_LINE; 
	else if (y==2) address = LCD_THR_LINE;
	else if (y==3) address = LCD_FRT_LINE;
	else address = 0;
	address += x;
	LCD_send_byte(0,0x80|address);
}

void LCD_write_char(char c){
	switch (c){
		case '\f' :	
			LCD_send_byte(0,1);
			LCD_delay_ms(5);
		break;
		case '\n' :
		case '\r' :	
			LCD_pos_xy(0,1);
		break;
		default:
			LCD_send_byte(1,c);
	}
}

void LCD_write_string (char *c){
	while (*c){
	  	LCD_write_char(*c);
	  	c++;
	}
}

void LCD_display_on(void){
	lcd_mode |= 4;
	LCD_send_byte (0,lcd_mode);
}

void LCD_display_off(void){
	lcd_mode &= 0b11111011;
	LCD_send_byte (0,lcd_mode);
}

void LCD_cursor_on(void){
	lcd_mode |= 2;
	LCD_send_byte (0,lcd_mode);
}

void LCD_cursor_off(void){
	lcd_mode &= 0b11111101;
	LCD_send_byte (0,lcd_mode);
}

void LCD_cursor_blink_on(void){
	lcd_mode |= 1;
	LCD_send_byte (0,lcd_mode);
}

void LCD_cursor_blink_off(void){
	lcd_mode &= 0b11111110;
	LCD_send_byte (0,lcd_mode);
}

void LCD_init(char mode1, char mode2){
	char aux;
	/* Se configuran los pines de datos como salida */

	// TXD0 P1_18 GPIO0[13]
	Chip_SCU_PinMux(1,18,SCU_MODE_INACT|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 0, ( 1 << 13 ), OUTPUT );

	// GPIO1 P6_4 GPIO3[3]
	Chip_SCU_PinMux(6,4,SCU_MODE_INACT|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 3, ( 1 << 3 ), OUTPUT );

	// GPIO3 P6_7 GPIO5[15]
	Chip_SCU_PinMux(6,7,SCU_MODE_INACT|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC4);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 5, ( 1 << 15 ), OUTPUT );

	// GPIO5 P6_9 GPIO3[5]
	Chip_SCU_PinMux(6,9,SCU_MODE_INACT|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 3, ( 1 << 5 ), OUTPUT );

	
	/* Se configura el pin de enable y RS como salida */
	
	// ENABLE GPIO7 P6_11 GPIO3[7]
	Chip_SCU_PinMux(6,11,SCU_MODE_INACT|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 3, ( 1 << 7 ), OUTPUT );


	// ENABLE GPIO8 P6_12 GPIO2[8]
	Chip_SCU_PinMux(6,12,SCU_MODE_INACT|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS,SCU_MODE_FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT, 2, ( 1 << 8 ), OUTPUT );
	

	/* Se ponen los pines del lcd en cero */
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 13, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 3, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 15, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 5, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 7, 0); // LCD enable = 0
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 8, 0); //RS =0

	/*---------------------Inicializacion del display--------------------*/
 
	/*R/W conectado a tierra y RS en 0*/
	
	/*1: Esperar mas de 15 ms*/
	LCD_delay_ms(20);
	
	/*2: Enviar tres veces 0011 */
	for(aux=0;aux<3;++aux)
	{		
	  LCD_send_nibble(3);
	  /*delay5*/
	  LCD_delay_ms(5);
	}

	/*3: Enviar 0010 */
	LCD_send_nibble(2);

	/* Datos de configuracion del LCD */
	LCD_send_byte(0,0x20 | mode1);
	LCD_send_byte(0,0x08 | mode2);
	lcd_mode = 0x08 | mode2;
	
	LCD_send_byte(0,0x01);
	LCD_delay_ms(5);
	LCD_send_byte(0,6); // entry mode set I/D=1 S=0
}