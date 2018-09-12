/**
 * @brief Configuraciones generales del sistema
 * 
 * @file general_config.c
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */
 
#include "general_config.h"

/* Variables privadas */
static int desired_temp;
static int desired_hum;
static int current_temp;
static int current_hum;

void CONFIG_init(void){
	desired_temp = 25;
	desired_hum = 10;
	current_temp = 25;
	current_hum = 10;
}

int CONFIG_get_desired_temp(void){
	return desired_temp;
}
int CONFIG_set_desired_temp(int new_temp){
	if (new_temp < TEMP_MAX){
		if (new_temp > TEMP_MIN){
			desired_temp = new_temp;
			return TEMP_SET_OK;
		}
		else{
			return TEMP_TOO_LOW;
		}
	}
	else{
		return TEMP_TOO_HIGH;
	}
	
}

int CONFIG_get_desired_hum(void){
	return desired_hum;
}
int CONFIG_set_desired_hum(int new_hum){
	if (new_hum < HUM_MAX){
		if (new_hum > HUM_MIN){
			desired_hum = new_hum;
			return HUM_SET_OK;
		}
		else{
			return HUM_TOO_LOW;
		}
	}
	else{
		return HUM_TOO_HIGH;
	}
	
}