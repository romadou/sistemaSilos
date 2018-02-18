#include "general_config.h"
#include "reports.h"

static int desired_temp_x10;
static int desired_hum_x10;
static int current_temp_x10;
static int current_hum_x10;

void CONFIG_init(void){
	desired_temp_x10 = 250;
	desired_hum_x10 = 100;
	current_temp_x10 = 250;
	current_hum_x10 = 100;
}

int CONFIG_get_desired_temp(void){
	return desired_temp_x10;
}

int CONFIG_check_temp(int temp_in, int temp_out){
	if (temp_in > 1.2 * desired_temp_x10){
		if (temp_out >= temp_in){
			//refrigeración??
			//apagar ventilación
			return TEMP_DANGER;
		}
		else{
			//encender ventilación
			return TEMP_ALERT;
		}
	} else if (temp_in > 1.4 * desired_temp_x10){
		if (temp_out >= temp_in){
			//refri??
			//apagar ventilación
		}
		return TEMP_DANGER;
	}
	else{
		//apagar ventilación
		return TEMP_OK;
	}
}

int CONFIG_check_hum(int hum_in, int hum_out){
	if (hum_in > 1.2 * desired_hum_x10){
		if (hum_out >= hum_in){
			//refrigeración??
			//apagar ventilación
			return HUM_DANGER;
		}
		else{
			//encender ventilación
			return HUM_ALERT;
		}
	} else if (temp > 1.4 * desired_temp_x10){
		if (temp_out >= temp_in){
			//refri??
			//apagar ventilación
		}
		return HUM_DANGER;
	}
	else{
		//apagar ventilación
		return HUM_OK;
	}
}

int CONFIG_set_desired_temp(int desired_temp){
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