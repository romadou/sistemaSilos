#include "general_config.h"

static int desired_temp_x10;
static int desired_hum_x10;
static int current_temp_x10;
static int current_hum_x10;


void config_init(void){
	desired_temp_x10 = 250;
	desired_hum_x10 = 100;
	current_temp_x10 = 250;
	current_hum_x10 = 100;
}

int config_get_desired_temp(void){
	return desired_temp_x10;
}

int config_set_desired_temp(int desired_temp){
	if (desired_temp < TEMP_MAX){
		if (desired_temp > TEMP_MIN){
			desired_temp_x10 = desired_temp;
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

/*int config_get_current_temp(){
	return current_temp_x10;
}

int config_save_current_temp(int current_temp){
	//
}

int config_get_current_hum(){
	return current_hum_x10;
}

int config_save_current_hum(int current_hum){
	//
}*/

int config_get_desired_hum(void){
	return desired_hum_x10;
}

int config_set_desired_hum(int desired_hum){
	if (desired_hum < HUM_MAX){
		if (desired_hum > HUM_MIN){
			desired_hum_x10 = desired_hum;
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