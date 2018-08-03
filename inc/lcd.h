/**
 * @file lcd.h 
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#ifndef LCD_H_
#define LCD_H_

/* Definición de los pines por defecto para el LCD */
#define LCD_SEC_LINE    0xC0    // Address of the second line of the LCD
#define LCD_THR_LINE    0x94
#define LCD_FRT_LINE    0xD4

/* LCD configuration constants */
#define CURSOR_ON       2
#define CURSOR_OFF      0
#define CURSOR_BLINK    1
#define CURSOR_NOBLINK  0
#define DISPLAY_ON      4
#define DISPLAY_OFF     0
#define DISPLAY_8X5     0
#define DISPLAY_10X5    4
#define _2_LINES        8
#define _1_LINE         0

void LCD_send_nibble(char data);
void LCD_send_byte(char address, char data); /* Envío de un byte al LCD. "address" dice si se envía un dato o un comando */
void LCD_init(char mode1, char mode2); /* Inicialización del LCD */
void LCD_pos_xy(char x, char y); /* Posicionamiento del cursor del lcd en la posición (x,y) */
void LCD_write_char(char c);
void LCD_write_string (char *c);
void LCD_display_on(void);s
void LCD_display_off(void);
void LCD_cursor_on(void);
void LCD_cursor_off(void);
void LCD_cursor_blink_on(void);
void LCD_cursor_blink_off(void);



#endif /* LCD_H_ */
