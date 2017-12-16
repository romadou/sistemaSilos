 *	lcd_mensajes.h
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
typedef enum problema {TEMPERATURA, HUMEDAD, SENSOR, GPRS, VENTILACION, TEL_NO_CONF, TEMP_NO_CONF, HUM_NO_CONF};

void LCD_mostrarNormal(void); /* Visualización del mensaje "NORMAL" en la primera línea del LCD */
void LCD_mostrarAlerta(void); /* Visualización del mensaje "ALERTA" en la primera línea del LCD */
void LCD_mostrarProblemaTemperatura(void); /* Visualización del mensaje de problema de temperatura en la segunda línea del LCD */
void LCD_mostrarProblemaHumedad(void); /* Visualización del mensaje de problema de humedad en la segunda línea del LCD */
void LCD_mostrarProblemaSensor(void); /* Visualización del mensaje de problema de desconexion del sensor en la segunda línea del LCD */
void LCD_mostrarProblemaGPRS(void); /* Visualización del mensaje de problema de desconexion GPRS en la segunda línea del LCD */
void LCD_mostrarProblemaVentilacion(void); /* Visualización del mensaje de problema de no configuración de telefóno en la segunda línea del LCD */
void LCD_mostrarProblemaTel_No_Conf(void); /* Visualización del mensaje de problema de no configuración de temperatura en la segunda línea del LCD */
void LCD_mostrarProblemaTemp_No_Conf(void); /* Visualización del mensaje de problema de no configuración de humedad en la segunda línea del LCD */
void LCD_mostrarProblemaHum_No_Conf(void); /* Visualización del mensaje de problema de temperatura en la segunda línea del LCD */
void LCD_mostrarTemperaturaInterior(int temp); /* Visualización del mensaje "T. Int:" con su valor en la tercer línea del LCD */
void LCD_mostrarTemperaturaExterior(int temp); /* Visualización del mensaje "T. Ext:" con su valor en la tercer línea del LCD */
void LCD_mostrarHumedadInterior(int hum); /* Visualización del mensaje "H. Int:" con su valor en la cuarta línea del LCD */
void LCD_mostrarHumedadExterior(int hum); /* Visualización del mensaje "H. Ext:" con su valor en la cuarta línea del LCD */
void LCD_mostrarNumeral(void); /* Visualización del caracter numeral en el rincón derecho inferior del LCD */

#endif /* MENSAJES_H_ */