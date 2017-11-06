#include "general_config.h"

static int temp_x10;
static int hum_x10;


void config_init(void){
	temp_x10 = 250;
	hum_x10 = 100;
}

int get_desired_temp(void){
	return temp_x10;
}

int set_desired_temp(int desired_temp){
	if (desired_temp < TEMP_MAX){
		if (desired_temp > TEMP_MIN){
			temp_x10 = desired_temp;
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

int get_desired_hum(void){
	return hum_x10;
}

int set_desired_hum(int desired_hum){
	if (desired_hum < HUM_MAX){
		if (desired_hum > HUM_MIN){
			hum_x10 = desired_hum;
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