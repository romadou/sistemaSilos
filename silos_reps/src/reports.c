#include "reports.h"
#include "general_config.h"
//#include "sensors.h"
//#include "led.h"
//#include "freeRtos.h" o como se llame, si es necesario hacer delays entre impresión e impresión (preguntar)


void reporte_temperatura_actual(void){
	int temp;
	//temp = sensors_getTempSensada();
	//led_informar_temp(temp);
}

void reporte_humedad_actual(void){
	int hum;
	//hum = sensors_getHumSensada();
	//led_informar_hum(hum);
}

void reporte_temp_y_hum_actual(void){
	reporte_temperatura_actual();
	//delay
	reporte_humedad_actual();

	/* o
	int temp = sensors_getTempSensada();
	int hum = sensors_getHumSensada();
	led_informar_temp_y_hum(temp, hum);
	*/
}

void reporte_gprs_dest_te_number(void){
	char dest[15] = gprs_get_dest_te_number();
	/*led_informar_te_number(dest);
	o led_informar_dest_te_number(dest);*/
}

void reporte_general(void){
	reporte_estado(normal_o_alerta, tipo_de_problema);
	reporte_temp_y_hum_actual();
	reporte_gprs_dest_te_number();
}