/* 
 * lcd_mensajes.h
 *
 *  Created on: 22/10/2017
 *      Author: Krasowski - Madou
 */

#ifndef MENSAJES_H_
#define MENSAJES_H_

#ifndef MAX_X
#define MAX_X 20
#endif 

#ifndef MAX_Y
#define MAX_Y 4
#endif 

typedef enum estado {NORMAL, ALERTA};
typedef enum problema {TEMPERATURA, HUMEDAD, SENSOR, GPRS, VENTILACION, TEL_NO_CONF, TEMP_NO_CONF, HUM_NO_CONF, CRITICO, OK};
typedef enum configurable {TELEFONO, TEMPERATURA, HUMEDAD};

void LCD_limpiarLinea(int l); /* Limpieza del número de línea recibido */
void LCD_limpiarPantalla(void); /* Limpieza de las cuatro líneas correspondientes al display */
void LCD_estado(estado e, problema p); /* Actualización de los mensajes de estado del sistema */
void LCD_valores(int ti, int te, int hi, int he); /* Actualización de los valores de temperatura y humedad */
void LCD_menuBienvenida (void); /* Menu con mensaje de bienvenida */
void LCD_menuMonitor (estado e, problema p, int ti, int te, int hi, int he); /* Menu formado por el estado del sistema y los valores de temperatura y humedad */
void LCD_menuConfiguracion(configurable c); /* Menu de pedido de configuración */




#endif /* MENSAJES_H_ */