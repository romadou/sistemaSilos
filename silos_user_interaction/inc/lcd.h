/*
 * lcd.h
 *
 *  Modified on: 30/11/2017
 *      Author: Madou
 */

#ifndef LCD_H_
#define LCD_H_

#include "chip.h"
#include "cmsis.h"

#define LCD_FIRST_LINE		0x00	// Address of the first line of the LCD (0-19)
#define LCD_SECOND_LINE     0x40    // Address of the second line of the LCD (64- 83)
#define LCD_THIRD_LINE  	0x14	// Address of the third line of the LCD (20-39)
#define LCD_FOURTH_LINE 	0x54	// Address of the fourth line of the LCD (84-103)

// LCD configuration constants
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


//**************************************************************************
//* Prototypes
//**************************************************************************
void LCD_delay_ms (uint8_t time);
void LCD_send_nibble(int8_t data);
void LCD_send_byte(int8_t address, int8_t data);
void LCD_init(int8_t mode1, int8_t mode2);
void LCD_pos_xy(uint8_t x, uint8_t y);
void LCD_write_char(char c);
void LCD_write_string (char *c);
void LCD_display_on(void);
void LCD_display_off(void);
void LCD_cursor_on(void);
void LCD_cursor_off(void);
void LCD_cursor_blink_on(void);
void LCD_cursor_blink_off(void);
void LCD_clear_line(uint8_t line);

#endif /* LCD_H_ */
