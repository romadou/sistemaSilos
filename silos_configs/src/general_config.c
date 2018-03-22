#include "general_config.h"
#include "reports.h"

static int desired_temp;
static int desired_hum;
static int current_temp;
static int current_hum;

void CONFIG_init(void){
	desired_temp = 250;
	desired_hum = 100;
	current_temp = 250;
	current_hum = 100;
}

int CONFIG_get_desired_temp(void){
	return desired_temp;
}

int CONFIG_check_temp(int temp_in, int temp_out){
	if (temp_in > 1.2 * desired_temp){
		if (temp_out >= temp_in){
			//refrigeración??
			//apagar ventilación
			return TEMP_DANGER;
		}
		else{
			//encender ventilación
			return TEMP_ALERT;
		}
	} else if (temp_in > 1.4 * desired_temp){
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
	if (hum_in > 1.2 * desired_hum){
		if (hum_out >= hum_in){
			//refrigeración??
			//apagar ventilación
			return HUM_DANGER;
		}
		else{
			//encender ventilación
			return HUM_ALERT;
		}
	} else if (temp > 1.4 * desired_temp){
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

int config_get_desired_hum(void){
	return desired_hum0;
}

int config_set_desired_hum(int desired_hum){
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