#include "reports.h"
#include "general_config.h"
#include "gprs.h"
#include "sensors.h"
#include "lcd_mensajes.h"
//#include "freeRtos.h" o como se llame


void REPORTE_general(int temp_in, int temp_out, int hum_in, int hum_out){
	//revisar lógica y funciones de ok de sensores, ventilacion y gprs
	/* Prioridad de problemas: crítico, temperatura, humedad, sensor, ventilación, gprs */ 
	int aux_temp = CONFIG_check_temp(temp_in, temp_out); 
	int aux_hum = CONFIG_check_hum(hum_in, hum_out); 
	if (aux_temp == TEMP_ALERT){
		LCD_menuMonitor(ALERTA, TEMPERATURA, temp_in/10, temp_out/10, hum_in/10, hum_out/10);
		//GPRS_alerta();	
	} else if (aux_temp == TEMP_DANGER){
		LCD_menuMonitor(ALERTA, CRITICO, temp_in/10, temp_out/10, hum_in/10, hum_out/10);
		//GPRS_critico();	
	} else if (aux_hum == HUM_ALERT){
		LCD_menuMonitor(ALERTA, HUMEDAD, temp_in/10, temp_out/10, hum_in/10, hum_out/10);
		//GPRS_alerta();	
	} else if (aux_hum == HUM_DANGER){
		LCD_menuMonitor(ALERTA, CRITICO, temp_in/10, temp_out/10, hum_in/10, hum_out/10);
		//GPRS_critico();	
	} else if (!SENSOR_is_ok()){
		LCD_menuMonitor(ALERTA, SENSOR, temp_in/10, temp_out/10, hum_in/10, hum_out/10);
		//GPRS_alerta();
	} else if (!VENT_is_ok()){
		LCD_menuMonitor(ALERTA, VENTILACION, temp_in/10, temp_out/10, hum_in/10, hum_out/10);
		//GPRS_alerta();	
	} else if (!GPRS_is_ok()){
		LCD_menuMonitor(ALERTA, GPRS, temp_in/10, temp_out/10, hum_in/10, hum_out/10);
		//GPRS_alerta();	
	} else{
		LCD_menuMonitor(NORMAL, OK, temp_in/10, temp_out/10, hum_in/10, hum_out/10);
	}
}