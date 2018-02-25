#include "general_config.h"
#include "tipos.h"
#include "MEF.h"
#include "lcd_mensajes.h"
#include "lcd.h"
#include "sapi.h"        // <= sAPI header
#include "proyectoSilos4.h"
#include "keypad.h"
#include "math.h"
#include "stdio.h"



typedef enum {DEFAULT, REPORTE_COMPONENTES, REPORTE_VENTILADOR, CANCELADO, CRITIC, MENU, REPORTE_CONFIG, CONFIG_TEMPERATURA, CONFIG_HUMEDAD,ERROR_TEMP, TEMPERATURA_INGRESADA, HUMEDAD_INGRESADA, ERROR_HUM, CONFIG_CELULAR, NUMERO_INGRESADO} state;
static state currentState;

static uint8_t stateTimeout;
extern uint8_t key;
//MOMENTANTEO
static uint8_t cel;
//MOMENTANEO
/* 
Devuelve 1 si alcanzó el timeout, 0 en caso contrario
*/
uint8_t timeout(void);

static uint8_t input_buffer[10];

/* Representa la cantidad de datos que ya fueron ingresados*/
static uint8_t loaded_input;

int buffer_to_int(void);


void MEF_Init(){
	currentState=DEFAULT;
	stateTimeout=16;
	loaded_input=0;
	cel=2395403455;
 }

void MEF_updateState(uint8_t critico){
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
				if(timeout()){
					stateTimeout=8;
					currentState=REPORTE_VENTILADOR;
				}
			}
		break;

		case REPORTE_VENTILADOR:
			if (critico){
				stateTimeout=8;
				currentState=CRITIC;
			} else if(timeout()){
				stateTimeout=16;
				currentState=DEFAULT;
			}
		break;

		case MENU:
			switch(key){
				case '1':
					stateTimeout=16;
					currentState=DEFAULT;
				break;
				case '2':
					stateTimeout=8;
					currentState=REPORTE_CONFIG;
				break;
				case '3':
					stateTimeout=16;
					currentState=CONFIG_TEMPERATURA;
				break;
				case '4':
					stateTimeout=16;
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
				case NOT_PRESSED:
				break;
				default:
					stateTimeout=8;
					if (KEYPAD_numero(key) && loaded_input<4 && (loaded_input>0 || key !='0')){
						input_buffer[loaded_input++]=key;
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
				case NOT_PRESSED:
				break;
				default:
					stateTimeout=8;
					if (KEYPAD_numero(key) && loaded_input<4 && (loaded_input>0 || key !='0')){
						input_buffer[loaded_input++]=key;
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
						//GPRS_set_dest_num();
						currentState=NUMERO_INGRESADO;
						loaded_input=0;
					}
				break;
				case '#':
					stateTimeout=8;
					currentState=CANCELADO;
					loaded_input=0;
				break;
				case NOT_PRESSED:
				break;
				default:
					stateTimeout=8;
					if (KEYPAD_numero(key) && loaded_input<10 && (loaded_input>0 || key !='0')){
						input_buffer[loaded_input++]=key;
					}
				break;
			}
			if(timeout()){
				stateTimeout=16;
				loaded_input=0;
				currentState=MENU;
			}
		break;
		case REPORTE_CONFIG:
			if(timeout()){
				stateTimeout=16;
				currentState=DEFAULT;
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

//ATENCION!! LOS VALORES DE TEMPERATURA Y HUMEDAD DEBEN VENIR SOLO EN SU PARTE ENTERA: EL LCD NO MUESTRA PARTE DECIMAL
void MEF_updateOutput(uint8_t tempi, uint8_t tempe, uint8_t humi, uint8_t hume, uint8_t sensores_activos, uint8_t vent){
	switch(currentState){
		case DEFAULT:
			LCD_menuMonitor(NORMAL, OK, tempi, tempe, humi, hume);
		break;

		case REPORTE_COMPONENTES:
			//LCD_sensoresActivos(sensores_activos);
			LCD_limpiarPantalla();
			LCD_pos_xy(0,1);			
			LCD_write_string("Sensores activos");
		break;

		case REPORTE_VENTILADOR:
			if (vent){
				//LCD_menuMonitor(CRITICO, VENTILANDO, tempi, tempe, humi, hume);
				LCD_limpiarPantalla();
				LCD_pos_xy(0,1);			
				LCD_write_string("Ventilacion");
			} else{
				//LCD_valores(tempi, tempe, humi, hume);
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
			LCD_menuConfiguracion(TELEFONO);
		break;

		case NUMERO_INGRESADO:
			LCD_configConfirmarNum();
		break;

		case CANCELADO:
			LCD_configEliminarNum();
		break;

		case REPORTE_CONFIG:
			LCD_menuConfigActual(CONFIG_get_desired_temp(), CONFIG_get_desired_hum(), &cel);
		break;
	}

}
/*
1=500ms
*/
uint8_t timeout(void){
	stateTimeout--;
	if(stateTimeout<=0)
		return 1; //se terminó el tiempo
	else
		return 0;
}
/**
int buffer_to_int(void){
	uint8_t index;
	int aux=0;
	for (index=loaded_input-1; index>0; index--){
		aux+=((int)(input_buffer[index])*(int)pow(10, index));
	}
	return aux;
}
**/