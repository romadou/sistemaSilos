#ifndef _REPORTS_H
#define _REPORTS_H

typedef enum estados{NORMAL, ALERTA};
typedef enum problemas{TEMPERATURA, HUMEDAD, SENSOR, GPRS, VENTILACION, TEMP_NO_CONF, HUM_NO_CONF, TEL_NO_CONF, OK};

void reporte_general(void);
void reporte_temperatura_actual(void);
void reporte_humedad_actual(void);
void reporte_temp_y_hum_actual(void);
void reporte_gprs_src_te_number(void);
void reporte_gprs_dest_te_number(void);


#endif