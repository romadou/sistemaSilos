/**
 * @brief Máquina de estados finitos del sistema
 * 
 * @file MEF.c
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */
 
#include "tipos.h"
#include "MEF.h"
#include "lcd_mensajes.h"
#include "lcd.h"
#include "sapi.h"        // <= sAPI header
#include "proyectoSilos.h"
#include "keypad.h"
#include "math.h"
#include "stdio.h"
#include "general_config.h"
#include "stdlib.h"

/* Definiciones y variables privadas */
typedef enum {DEFAULT, REPORTE_COMPONENTES, REPORTE_VENTILADOR, CANCELADO, CRITIC, MENU, REPORTE_CONFIG, CONFIG_TEMPERATURA, CONFIG_HUMEDAD,ERROR_TEMP, TEMPERATURA_INGRESADA, HUMEDAD_INGRESADA, ERROR_HUM, CONFIG_CELULAR, NUMERO_INGRESADO} state;
static state currentState;
static state previousState;
static uint8_t stateTimeout; /* Variable de control para los timeout. 1=500ms */
extern uint8_t key;
static uint8_t input_buffer[11]; /* Buffer de entrada de caracteres */
static uint8_t loaded_input; /* Representa la cantidad de datos que ya fueron ingresados */

/* Funciones privadas */
uint8_t timeout(void); /* Devuelve 1 si alcanzó el timeout, 0 en caso contrario */
int buffer_to_int(void); /* Convierte lo almacenado en el buffer a un entero */


void MEF_Init(){
	currentState=DEFAULT;
	stateTimeout=16;
	loaded_input=0;
 }

void MEF_updateState(uint8_t critico){
	previousState=currentState;
	switch(currentState){
		case DEFAULT:
			if (critico){
				stateTimeout=8;
				currentState=CRITIC;
			} else{
				if(key=='#'){
					stateTimeout=16;
					currentState=MENU;
				}
				else{
					if(timeout()){ //el 0 significa que es tiempo de transición entre pantallas y no de usuario
						stateTimeout=8;
						currentState=REPORTE_COMPONENTES;
					}
				}
			}	
		break;

		case REPORTE_COMPONENTES:
			if (critico){
				stateTimeout=8;
				currentState=CRITIC;
			} else{
				if(key=='#'){
					stateTimeout=16;
					currentState=MENU;
				}
				else{
					if(timeout()){
						stateTimeout=8;
						currentState=REPORTE_VENTILADOR;
					}
				}
			}
		break;

		case REPORTE_VENTILADOR:
			if (critico){
				stateTimeout=8;
				currentState=CRITIC;
			} else{
				if(key=='#'){
					stateTimeout=16;
					currentState=MENU;
				}
				else{
					if(timeout()){
						stateTimeout=16;
						currentState=DEFAULT;
					}
				}
			}
		break;

		case MENU:
			switch(key){
				case '1':
					stateTimeout=16;
					currentState=DEFAULT;
				break;
				case '2':
					stateTimeout=32;
					currentState=REPORTE_CONFIG;
				break;
				case '3':
					stateTimeout=32;
					currentState=CONFIG_TEMPERATURA;
				break;
				case '4':
					stateTimeout=32;
					currentState=CONFIG_CELULAR;
				break;
			}
			if(timeout()){
				stateTimeout=16;
				currentState=DEFAULT;
			}
		break;

		case CRITIC:
			if(timeout()){
				stateTimeout=16;
				if (!critico){
					currentState=DEFAULT;	
				}
			}
		break;

		case CONFIG_TEMPERATURA:
			switch(key){
				case '*':
					stateTimeout=8;
					input_buffer[loaded_input]='\0';
					if (CONFIG_set_desired_temp(atoi(input_buffer)) == TEMP_SET_OK){
						currentState=TEMPERATURA_INGRESADA;
					} else{
						currentState=ERROR_TEMP;
					}
					loaded_input=0;
				break;
				case '#':
					stateTimeout=8;
					loaded_input=0;
					currentState=CANCELADO;
				break;
				case 'B':
					stateTimeout=8;
					if (loaded_input>0){
						loaded_input--;
						LCD_configBorrarChar();
					}
				break;
				case NOT_PRESSED:
				break;
				default:
					stateTimeout=16;
					if (KEYPAD_numero(key) && loaded_input<4 && (loaded_input>0 || key !='0')){
						input_buffer[loaded_input++]=key;
						//Esto estaba implementado en una función de la librería lcd_mensajes
						//LCD_pos_xy(8+loaded_input,2);
						//LCD_write_char(key);
						LCD_configIngresarNum(key);
					}
				break;
			}
			if(timeout()){
				stateTimeout=8;
				loaded_input=0;
				currentState=CANCELADO;
			}
		break;
		case CONFIG_HUMEDAD:
			switch(key){
				case '*':
					stateTimeout=8;
					input_buffer[loaded_input]='\0';
					
					if (CONFIG_set_desired_hum(atoi(input_buffer)) == HUM_SET_OK){
						currentState=HUMEDAD_INGRESADA;
					} else{
						currentState=ERROR_HUM;
					}
					loaded_input=0;
					
					
				break;
				case '#':
					stateTimeout=8;
					loaded_input=0;
					currentState=CANCELADO;
				break;
				case 'B':
					stateTimeout=8;
					if (loaded_input>0){
						loaded_input--;
						LCD_configBorrarChar();
					}
				break;
				case NOT_PRESSED:
				break;
				default:
					stateTimeout=16;
					if (KEYPAD_numero(key) && loaded_input<4 && (loaded_input>0 || key !='0')){
						input_buffer[loaded_input++]=key;
						LCD_configIngresarNum(key);
					}
				break;
			}
			if(timeout()){
				stateTimeout=8;
				loaded_input=0;
				currentState=CANCELADO;
			}
		break;
		case CONFIG_CELULAR:
			switch(key){
				case '*':
					stateTimeout=8;
					if (loaded_input==10){
						input_buffer[loaded_input]='\0';
						GPRS_set_dest_num(input_buffer);
						currentState=NUMERO_INGRESADO;
						loaded_input=0;
					}
				break;
				case '#':
					stateTimeout=8;
					currentState=CANCELADO;
					loaded_input=0;
				break;
				case 'B':
					stateTimeout=8;
					if (loaded_input>0){
						loaded_input--;
						LCD_configBorrarChar();
					}
				break;
				case NOT_PRESSED:
				break;
				default:
					stateTimeout=16;
					if (KEYPAD_numero(key) && loaded_input<10 && (loaded_input>0 || key !='0')){
						input_buffer[loaded_input++]=key;
						LCD_configIngresarNum(key);
					}
				break;
			}
			if(timeout()){
				stateTimeout=32;
				loaded_input=0;
				currentState=MENU;
			}
		break;
		case REPORTE_CONFIG:
			if(timeout()){
				stateTimeout=16;
				currentState=DEFAULT;
			}
			else
				if(key=='#'){
					stateTimeout=16;
					currentState=MENU;
				}
		break;
		case CANCELADO:
			if (timeout()){
				stateTimeout=16;
				currentState=DEFAULT;
			}
		break;
		case ERROR_TEMP:
			if (timeout()){
				stateTimeout=16;
				currentState=CONFIG_TEMPERATURA;
			}
		break;
		case ERROR_HUM:
			if (timeout()){
				stateTimeout=16;
				currentState=CONFIG_HUMEDAD;
			}
		break;
		case TEMPERATURA_INGRESADA:
			if (timeout()){
				stateTimeout=16;
				currentState=CONFIG_HUMEDAD;
			}
		break;

		case HUMEDAD_INGRESADA:
			if (timeout()){
				stateTimeout=16;
				currentState=DEFAULT;
			}
		break;

		case NUMERO_INGRESADO:
			if (timeout()){
				stateTimeout=16;
				currentState=DEFAULT;
			}
		break;
	}
}

void MEF_updateOutput(uint8_t tempi, uint8_t tempe, uint8_t humi, uint8_t hume, uint8_t sensores_activos, uint8_t sensorCaido, uint8_t vent){
	if(currentState!=previousState){
		switch(currentState){
			case DEFAULT:
				if(sensorCaido)
					LCD_menuMonitor(ALERTA, SENSOR, tempi, tempe, humi, hume);
				else
					LCD_menuMonitor(NORMAL, OK, tempi, tempe, humi, hume);
			break;

			case REPORTE_COMPONENTES:
				LCD_sensoresActivos(sensores_activos);
			break;

			case REPORTE_VENTILADOR:
				if (vent){
					if(sensorCaido)
						LCD_menuMonitor(ALERTA, VENTILANDO, tempi, tempe, humi, hume);
					else
						LCD_menuMonitor(NORMAL, VENTILANDO, tempi, tempe, humi, hume);
				} else{
					LCD_valores(tempi, tempe, humi, hume);
				}
			break;

			case CRITIC:
				LCD_menuMonitor(ALERTA, CRITICO, tempi, tempe, humi, hume);
			break;

			case MENU:
				LCD_menuOpciones();
			break;

			case CONFIG_TEMPERATURA:
				LCD_menuConfiguracion(TEMP);
			break;

			case ERROR_TEMP:
				LCD_configErrorNum();
			break;

			case TEMPERATURA_INGRESADA:
				LCD_configConfirmarNum();
			break;
			case CONFIG_HUMEDAD:
				LCD_menuConfiguracion(HUM);
			break;
			case ERROR_HUM:
				LCD_configErrorNum();
			break;

			case HUMEDAD_INGRESADA:
				LCD_configConfirmarNum();
			break;

			case CONFIG_CELULAR:
				LCD_menuConfiguracion(TEL);
			break;

			case NUMERO_INGRESADO:
				LCD_configConfirmarNum();
			break;

			case CANCELADO:
				LCD_configEliminarNum();
			break;

			case REPORTE_CONFIG:
				LCD_menuConfigActual(CONFIG_get_desired_temp(), CONFIG_get_desired_hum(), GPRS_get_dest_num());
			break;
		}
	}
}

uint8_t timeout(void){
	stateTimeout--;
	if(stateTimeout<=0)
		return 1; // Se terminó el tiempo
	else
		return 0;
}

int buffer_to_int(void){
	uint8_t index;
	int aux=0;
	for (index=loaded_input-1; index>0; index--){
		aux+=((int)(input_buffer[index])*(int)pow(10, index));
	}
	return aux;
}