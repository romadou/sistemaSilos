/* 
 * lcd_mensajes.h
 *
 *  Created on: 22/10/2017
 *      Author: Krasowski - Madou
 */

#ifndef LCD_MENSAJES_H_
#define LCD_MENSAJES_H_

#ifndef MAX_X
#define MAX_X 20
#endif 

#ifndef MAX_Y
#define MAX_Y 4
#endif 

typedef enum {NORMAL, ALERTA} estado; 
typedef enum {TEMPERATURA, HUMEDAD, VENTILANDO, SENSOR, GPRS, VENTILACION, TEL_NO_CONF, TEMP_NO_CONF, HUM_NO_CONF, CRITICO, OK} problema;
typedef enum {TEL, TEMP, HUM, NC} configurable;

void LCD_menuBienvenida(void); /* Configuración inicial del display y  menu con mensaje de bienvenida */
void LCD_menuOpciones(void); /* Menu de opciones a otros menus */
void LCD_estado(estado e, problema p); /* Actualización de los mensajes de estado del sistema */
void LCD_sensoresActivos(int sensact); /* Visualización del mensaje "Sensores activos:" con su cantidad en la segunda línea del LCD */
void LCD_valores(int tempi, int tempe, int humi, int hume); /* Actualización de los valores de temperatura y humedad */
void LCD_menuMonitor(estado e, problema p, int tempi, int tempe, int humi, int hume); /* Menu formado por el estado del sistema y los valores de temperatura y humedad */
void LCD_menuConfiguracion(configurable c); /* Menu de pedido de configuración */
void LCD_configIngresarNum(char num); /* Se muestra el pantalla el número recibido */
void LCD_configBorrarChar(void); /* Se elimina el último dígito ingresado de pantalla */
void LCD_configConfirmarNum(void); /* Mensaje indicando que la operación fue exitosa */
void LCD_configEliminarNum(void); /* Mensaje indicando que la operación se canceló */
void LCD_configErrorNum(void); /* Mensaje indicando que se presentó un error */
void LCD_menuConfigActual(int temp, int hum, char* tel); /* Menu que refleja los valores seteados */
void LCD_limpiarLinea(int l); /* Limpieza del número de línea recibido */
void LCD_limpiarPantalla(void); /* Limpieza de las cuatro líneas correspondientes al display */



#endif /* MENSAJES_H_ */
