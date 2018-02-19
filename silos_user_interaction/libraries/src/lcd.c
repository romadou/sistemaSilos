/*
 * lcd.h
 *
 *  Created on: 17/12/2016
 *      Author: Alvarez
 */


#include "lcd.h"
#include "chip.h"
#include "cmsis.h"

#define INACCURATE_TO_MS 20400
#define INACCURATE_TO_US 21

#define LCD4_P 			4   //BIT 4
#define LCD4_P_			6
#define LCD4_GPIO		2
#define LCD4_PIN 		6
 
#define LCD5_P 			4 	//BIT 5
#define LCD5_P_			5
#define LCD5_GPIO		2
#define LCD5_PIN    	5

#define LCD6_P 			4 	//BIT 6
#define LCD6_P_			4
#define LCD6_GPIO		2
#define LCD6_PIN 		4

#define LCD7_P 			4 	//BIT 7
#define LCD7_P_			3
#define LCD7_GPIO		2
#define LCD7_PIN  		3

#define LCDRS_P 		4 	//RS
#define LCDRS_P_		10
#define LCDRS_GPIO		5
#define LCDRS_PIN 		14

#define LCDE_P    		4   //ENABLE
#define LCDE_P_   		8
#define LCDE_GPIO 		5
#define LCDE_PIN  		12

#define ON 				1
#define OFF 			0

#define INPUT       	0
#define OUTPUT      	1


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

// Display configuration global variable
static char lcd_mode;	

//**************************************************************************
//* A simple delay function (used by LCD functions)
//**************************************************************************
//* Calling arguments
//* unsigned char time: aproximate delay time in miliseconds
//**************************************************************************
void LCD_delay_ms (uint8_t time)
{
	volatile uint64_t i;
	for( i=INACCURATE_TO_MS * time; i>0; i-- );
}

//**************************************************************************
//* Send a nibble to the LCD
//**************************************************************************
//* Calling arguments
//* char data : data to be sent to the display
//**************************************************************************
void LCD_send_nibble(int8_t data)
{
	volatile uint64_t i;
	union ubyte my_union;
	my_union._byte = data;

	// Output the four data bits
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, LCD4_GPIO, LCD4_PIN, my_union.bit.b0);  
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, LCD5_GPIO, LCD5_PIN, my_union.bit.b1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, LCD6_GPIO, LCD6_PIN, my_union.bit.b2);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, LCD7_GPIO, LCD7_PIN, my_union.bit.b3);
	
	for( i=INACCURATE_TO_US * 40; i>0; i-- );

	// pulse the LCD enable line
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, LCDE_GPIO, LCDE_PIN, ON);

	for( i=INACCURATE_TO_US * 2; i>0; i-- );

	Chip_GPIO_SetPinState(LPC_GPIO_PORT, LCDE_GPIO, LCDE_PIN, OFF);
}

//**************************************************************************
//* Write a byte into the LCD
//**************************************************************************
//* Calling arguments:
//* char address : 0 for instructions, 1 for data
//* char data : command or data to be written
//**************************************************************************
void LCD_send_byte(int8_t address, int8_t data)
{
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, LCDRS_GPIO, LCDRS_PIN, OFF);

	if(address==0)
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, LCDRS_GPIO, LCDRS_PIN, OFF);               // config the R/S line
	else
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, LCDRS_GPIO, LCDRS_PIN, ON);

	LCD_delay_ms(2);

	Chip_GPIO_SetPinState(LPC_GPIO_PORT, LCDE_GPIO, LCDE_PIN, OFF);               // set LCD enable line to 0

	LCD_send_nibble(data >> 4);     // send the higher nibble
	LCD_send_nibble(data & 0x0F);   // send the lower nibble
}

//**************************************************************************
//* LCD initialization
//**************************************************************************
//* Calling arguments:
//* char mode1 : display mode (number of lines and character size)
//* char mode2 : display mode (cursor and display state)
//**************************************************************************
void LCD_init(int8_t mode1, int8_t mode2)
{
	uint8_t aux;

	// Configure the pins as outputs
	Chip_SCU_PinMux(LCDE_P, LCDE_P_, SCU_MODE_INACT, FUNC4);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LCDE_GPIO, (1<<LCDE_PIN), OUTPUT);

	Chip_SCU_PinMux(LCDRS_P, LCDRS_P_, SCU_MODE_INACT, FUNC4); 
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LCDRS_GPIO, (1<<LCDRS_PIN), OUTPUT);

	Chip_SCU_PinMux(LCD4_P, LCD4_P_, SCU_MODE_INACT, FUNC0); 
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LCD4_GPIO, (1<<LCD4_PIN), OUTPUT);

	Chip_SCU_PinMux(LCD5_P, LCD5_P_, SCU_MODE_INACT, FUNC0); 
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LCD5_GPIO, (1<<LCD5_PIN), OUTPUT);

	Chip_SCU_PinMux(LCD6_P, LCD6_P_, SCU_MODE_INACT, FUNC0); 
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LCD6_GPIO, (1<<LCD6_PIN), OUTPUT);

	Chip_SCU_PinMux(LCD7_P, LCD7_P_, SCU_MODE_INACT, FUNC0); 
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LCD7_GPIO, (1<<LCD7_PIN), OUTPUT);

	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LCD4_GPIO, (1<<LCD4_PIN));
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LCD5_GPIO, (1<<LCD5_PIN));
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LCD6_GPIO, (1<<LCD6_PIN));
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LCD7_GPIO, (1<<LCD7_PIN));
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LCDRS_GPIO, (1<<LCDRS_PIN));
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LCDE_GPIO, (1<<LCDE_PIN));

	LCD_delay_ms(35);
	// LCD 4-bit mode initialization sequence
	// send three times 0x03 and then 0x02 to finish configuring the LCD
	for(aux=0;aux<3;aux++)
	{		
	  LCD_send_nibble(3);  //0011 tres veces
	  LCD_delay_ms(5);
	}
	LCD_send_nibble(2);  //0010 una vez
	// Now send the LCD configuration data
	LCD_send_byte(0,0x20 | mode1);  //primero 0010, despues 1000
	LCD_send_byte(0,0x08 | mode2);
    //LCD_send_byte(0,0x08); //primero 0000, despues 1000
	lcd_mode = 0x08 | mode2;
	
	LCD_send_byte(0,0x01); //primero 0000, despues 0001
	LCD_delay_ms(5);
	LCD_send_byte(0,6); //primero 0000, despues 0110 // entry mode set I/D=1 S=0
}

//**************************************************************************
//* LCD cursor position set
//**************************************************************************
//* Calling arguments:
//* char x : column (0-20)
//* char y : line (0,1,2,3)
//**************************************************************************
void LCD_pos_xy(uint8_t x, uint8_t y)  /*Ver si modificar o no*/
{
  uint8_t address;
  if (y==1) 
  	address = LCD_SECOND_LINE; 
  else if(y==2)
  	address = LCD_THIRD_LINE;
  else if(y==3)
  	address = LCD_FOURTH_LINE;
  else{
  	address=LCD_FIRST_LINE;
  }
  address += x;
  LCD_send_byte(0,0x80|address);
}

//**************************************************************************
//* Write a character on the display
//**************************************************************************
//* Calling arguments:
//* char c : character to be written
//**************************************************************************
//* Notes :
//* \f clear the display
//* \n and \r return the cursor to line 1 column 0
//**************************************************************************
void LCD_write_char(char c)
{
  switch (c)
	{
	  case '\f' :	
	    LCD_send_byte(0,1);
	    LCD_delay_ms(5);
	    break;
	  case '\n' :
	  case '\r' :	
	    LCD_pos_xy(0,1);
	    break;
	  case (char)186 :
	  	LCD_write_char(0xDF);
	  	break;
	  default:
	    LCD_send_byte(1,c);
   }
}

//**************************************************************************
//* Write a string on the display
//**************************************************************************
//* Calling arguments:
//* char *c : pointer to the string
//**************************************************************************
void LCD_write_string (char *c)
{
	while (*c)
	{
	  LCD_write_char(*c);
	  c++;
	}
}

//**************************************************************************
//* Turn the display on
//**************************************************************************
void LCD_display_on(void)
{
	lcd_mode |= 4;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Turn the display off
//**************************************************************************
void LCD_display_off(void)
{
	lcd_mode &= 0b11111011;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Turn the cursor on
//**************************************************************************
void LCD_cursor_on(void)
{
  lcd_mode |= 2;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Turn the cursor off
//**************************************************************************
void LCD_cursor_off(void)
{
	lcd_mode &= 0b11111101;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Turn on the cursor blink function
//**************************************************************************
void LCD_cursor_blink_on(void)
{
	lcd_mode |= 1;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Turn off the cursor blink function
//**************************************************************************
void LCD_cursor_blink_off(void)
{
	lcd_mode &= 0b11111110;
	LCD_send_byte (0,lcd_mode);
}
//**************************************************************************
//* Cleans display's indicated line
//**************************************************************************

void LCD_clear_line(uint8_t line){	
	LCD_pos_xy(0,line);
	LCD_write_string("                    ");
}