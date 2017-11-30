#ifndef _REPORTS_H
#define _REPORTS_H

#ifndef ESTADO_NORMAL
#define ESTADO_NORMAL 0
#endif

#ifndef ESTADO_ALERTA
#define ESTADO_ALERTA 0
#endif

typedef enum estados{ESTADO_NORMAL, ESTADO_ALERTA};
typedef enum problemas{TEMPERATURA, HUMEDAD, SENSOR, GPRS, VENTILACION, TELEFONO, OK};

void reporte_general(void);
void reporte_temperatura_actual(void);
void reporte_humedad_actual(void);
void reporte_temp_y_hum_actual(void);
void reporte_gprs_src_te_number(void);
void reporte_gprs_dest_te_number(void);


#endif