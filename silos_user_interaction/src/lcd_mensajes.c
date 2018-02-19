/*
 * mensajes.c
 *
 *  Created on: 30/11/2017
 *      Author: Madou
 */
 
#include < lcd_mensajes.h >
#include < lcd.h >

/* Variables privadas */
/* Formato de muestra de mensaje */
char pantallaMensaje[MAX_X];
/* Formato de muestra de los valores numéricos */
char valor[4];
/* Posición del valor numérico ingresado */
int pos = 0;

/* Funciones privadas */
void mostrarNormal(void); /* Visualización del mensaje "NORMAL" en la primera línea del LCD */
void mostrarAlerta(void); /* Visualización del mensaje "ALERTA" en la primera línea del LCD */
void mostrarProblemaTemperatura(void); /* Visualización del mensaje de problema de temperatura en la segunda línea del LCD */
void mostrarProblemaHumedad(void); /* Visualización del mensaje de problema de humedad en la segunda línea del LCD */
void mostrarProblemaVentilando(void); /* Visualización del mensaje de alerta de ventilación encendida en la segunda línea del LCD */
void mostrarProblemaSensor(void); /* Visualización del mensaje de problema de desconexion del sensor en la segunda línea del LCD */
void mostrarProblemaGPRS(void); /* Visualización del mensaje de problema de desconexion GPRS en la segunda línea del LCD */
void mostrarProblemaVentilacion(void); /* Visualización del mensaje de alerta de ventilación no funcionando en la segunda línea del LCD */
void mostrarProblemaTel_No_Conf(void); /* Visualización del mensaje de problema de no configuración de telefóno en la segunda línea del LCD */
void mostrarProblemaTemp_No_Conf(void); /* Visualización del mensaje de problema de no configuración de temperatura en la segunda línea del LCD */ 
void mostrarProblemaHum_No_Conf(void); /* Visualización del mensaje de problema de no configuración de humedad en la segunda línea del LCD */
void mostrarProblemaCritico(void); /* Visualización del mensaje de alerta crítica en la segunda línea del LCD */
void mostrarTemperaturaInterior(int tempi); /* Visualización del mensaje "T.I:" con su valor en la tercer línea del LCD */
void mostrarTemperaturaExterior(int tempe); /* Visualización del mensaje "T.E:" con su valor en la tercer línea del LCD */
void mostrarHumedadInterior(int humi); /* Visualización del mensaje "H.I:" con su valor en la cuarta línea del LCD */
void mostrarHumedadExterior(int hume); /* Visualización del mensaje "H.E:" con su valor en la cuarta línea del LCD */
void mostrarNumeral(void); /* Visualización del caracter numeral en el rincón derecho inferior del LCD */
void numASCII(int num); /* Transformación de un valor numérico a caracter */


void LCD_menuBienvenida(void){
	LCD_init(DISPLAY_8X5|_2_LINES, DISPLAY_ON|CURSOR_OFF|CURSOR_NOBLINK);

	LCD_limpiarPantalla();
	pantallaMensaje	= "Bienvenido al";
	LCD_pos_xy(3,0);
	LCD_write_string(pantallaMensaje);
	pantallaMensaje	= "Sistema de Control";
	LCD_pos_xy(1,1);
	LCD_write_string(pantallaMensaje);
	pantallaMensaje	= "para Silos";
	LCD_pos_xy(5,2);
	LCD_write_string(pantallaMensaje);
	pantallaMensaje	= "AKMM";
	LCD_pos_xy(8,3);
	LCD_write_string(pantallaMensaje);
} 

void LCD_menuOpciones(void){
	LCD_limpiarPantalla();
	pantallaMensaje = "1. Reporte General";
	LCD_pos_xy(0,0);
	LCD_write_string(pantallaMensaje);
	pantallaMensaje = "2. Ver Config Actual";
	LCD_pos_xy(0,1);
	LCD_write_string(pantallaMensaje);
	pantallaMensaje = "3. Config Temp y Hum";
	LCD_pos_xy(0,2);
	LCD_write_string(pantallaMensaje);
	pantallaMensaje = "4. Config Tel";
	LCD_pos_xy(0,3);
	LCD_write_string(pantallaMensaje);
	mostrarNumeral();	
}

void LCD_estado(estado e, problema p){
	// Primera línea
	LCD_limpiarLinea(0);
	if (e == NORMAL){
		mostrarNormal();	
	}
	else{
		mostrarAlerta();
	}	

	//Segunda línea
	LCD_limpiarLinea(1);
	switch (p){
		case TEMPERATURA : 	mostrarProblemaTemperatura();
							break;
		case HUMEDAD : 	mostrarProblemaHumedad();
						break;
		case VENTILANDO : 	mostrarProblemaVentilando();
							break;
		case SENSOR : 	mostrarProblemaSensor();
						break;
		case GPRS : 	mostrarProblemaGPRS();
						break;
		case VENTILACION : 	mostrarProblemaVentilacion();
							break;
		case TEL_NO_CONF :	mostrarProblemaTel_No_Conf();
							break;
		case TEMP_NO_CONF : mostrarProblemaTemp_No_Conf();
							break;
		case HUM_NO_CONF : 	mostrarProblemaHum_No_Conf();
							break;
		case CRITICO : 	mostrarProblemaCritico();
						break;
		case OK : 	
		default:	LCD_limpiarLinea(1);
					break;
	}

	// Final de display
	mostrarNumeral();
}

void LCD_valores(int tempi, int tempe, int humi, int hume){
	// Tercer y cuarta línea
	LCD_limpiarLinea(2);
	mostrarTemperaturaInterior(tempi);
	mostrarTemperaturaExterior(tempe);
	LCD_limpiarLinea(3);
	mostrarHumedadInterior(humi);
	mostrarHumedadExterior(hume);
	mostrarNumeral();
}

void LCD_menuMonitor(estado e, problema p, int tempi, int tempe, int humi, int hume){
	LCD_limpiarPantalla();
	// Primera línea
	if (e == NORMAL){
		mostrarNormal();	
	}
	else{
		mostrarAlerta();
	}	

	// Segunda línea
	switch (p){
		case TEMPERATURA : 	mostrarProblemaTemperatura();
							break;
		case HUMEDAD : 	mostrarProblemaHumedad();
						break;
		case SENSOR : 	mostrarProblemaSensor();
						break;
		case GPRS : 	mostrarProblemaGPRS();
						break;
		case VENTILACION : 	mostrarProblemaVentilacion();
							break;
		case TEL_NO_CONF :	mostrarProblemaTel_No_Conf();
							break;
		case TEMP_NO_CONF : mostrarProblemaTemp_No_Conf();
							break;
		case HUM_NO_CONF : 	mostrarProblemaHum_No_Conf();
							break;
		case CRITICO : 	mostrarProblemaCritico();
						break;
		case OK : 	
		default:	LCD_limpiarLinea(1);
					break;
	}

	// Tercer y Cuarta línea
	mostrarTemperaturaInterior(tempi);
	mostrarTemperaturaExterior(tempe);
	mostrarHumedadInterior(humi);
	mostrarHumedadExterior(hume);

	// Final de display
	mostrarNumeral();
}

void LCD_menuConfiguracion(configurable c){
	LCD_limpiarPantalla();
	pantallaMensaje = "Ingrese";
	LCD_pos_xy(6,0);
	LCD_write_string(pantallaMensaje);
	switch(p){
		case TELEFONO : pantallaMensaje = "nro de telefono";
						LCD_pos_xy(2,1);
						break;
		case TEMPERATURA: 	pantallaMensaje = "temperatura";
							LCD_pos_xy(4,1);
							break;
		case HUMEDAD : 	pantallaMensaje = "humedad";
						LCD_pos_xy(6,1);
						break;
		default : ;
	}
	LCD_write_string(pantallaMensaje);
	pantallaMensaje = "*:Guardar #:Cancelar";
	LCD_pos_xy(0,3);
	LCD_write_string(pantallaMensaje);
}

void LCD_configIngresarNum(char num){
	LCD_pos_xy(5+pos,2);
	LCD_write_char(num);
	pos++;
}

void LCD_configConfirmarNum(void){
	LCD_limpiarPantalla();
	pantallaMensaje = "VALOR";
	LCD_pos_xy(7,1);
	LCD_write_string(pantallaMensaje);
	pantallaMensaje = "GUARDADO";
	LCD_pos_xy(6,2);
	LCD_write_string(pantallaMensaje);
	pos = 0;
}

void LCD_configEliminarNum(void){
	LCD_limpiarPantalla();
	pantallaMensaje = "OPERACION";
	LCD_pos_xy(5,1);
	LCD_write_string(pantallaMensaje);
	pantallaMensaje = "CANCELADA";
	LCD_pos_xy(5,2);
	LCD_write_string(pantallaMensaje);
	pos = 0;
}

void LCD_configErrorNum(void){
	LCD_limpiarPantalla();
	pantallaMensaje = "VALOR FUERA";
	LCD_pos_xy(4,1);
	LCD_write_string(pantallaMensaje);
	pantallaMensaje = "DE RANGO";
	LCD_pos_xy(6,2);
	LCD_write_string(pantallaMensaje);
	pos = 0;
}

void LCD_menuConfigActual(int temp, int hum, char* tel){
	LCD_limpiarPantalla();
	pantallaMensaje = "Config Actual";
	LCD_pos_xy(3,0);
	LCD_write_string(pantallaMensaje);
	pantallaMensaje = "Temp: ";
	LCD_pos_xy(2,0);
	LCD_write_string(pantallaMensaje);
	numASCII(temp);
	LCD_write_string(valor);
	pantallaMensaje = "Hum: ";
	LCD_pos_xy(2,0);
	LCD_write_string(pantallaMensaje);
	numASCII(hum);
	LCD_write_string(valor);
	pantallaMensaje = "Tel: ";
	LCD_pos_xy(2,0);
	LCD_write_string(pantallaMensaje);
	LCD_write_string(tel);
	mostrarNumeral();
}

void LCD_limpiarLinea(int l){
	if (l < MAX_Y){
		pantallaMensaje	= "                    ";
		LCD_pos_xy(0,l);
		LCD_write_string(pantallaMensaje);
	}
}

void LCD_limpiarPantalla(void){
	int l;
	for (l=0;i<MAX_Y;i++){
		pantallaMensaje	= "                    ";
		LCD_pos_xy(0,l);
		LCD_write_string(pantallaMensaje);
	}
}



void numASCII(int num){
	int c; 
	c = num / 100;
	if (c){
		valor[0] = '0' + c;
		num = num % 100;
		c = num / 10;
		valor[1] = '0' + c;
		num = num % 10;
		valor[2] = '0' + num;
		valor[3] = '\0';
	}
	else{
		num = num % 100;
		c = num / 10;
		if (c){
			valor[0] = '0' + c;
			num = num % 10;
			valor[1] = '0' + num;
			valor[2] = '\0';
		}
		num = num % 10;
		valor[0] = '0' + num;
		valor[1] = '\0';
	}
}

void mostrarNormal(void){
	pantallaMensaje = "FUNC NORMAL";
	LCD_pos_xy(4,0);
	LCD_write_string(pantallaMensaje);
}
void mostrarAlerta(void){
	pantallaMensaje = "ALERTA";
	LCD_pos_xy(7,0);
	LCD_write_string(pantallaMensaje);
}

void mostrarProblemaTemperatura(void){
	pantallaMensaje = "Temp alta";
	LCD_pos_xy(5,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaHumedad(void){
	pantallaMensaje	= "Hum alta";
	LCD_pos_xy(6,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaVentilando(void){
	pantallaMensaje	= "Ventilando";
	LCD_pos_xy(5,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaSensor(void){
	pantallaMensaje	= "Sensor caido";
	LCD_pos_xy(3,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaGPRS(void){
	pantallaMensaje	= "GPRS OFF";
	LCD_pos_xy(6,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaVentilacion(void){
	pantallaMensaje	= "Vent caido";
	LCD_pos_xy(5,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaTel_No_Conf(void){
	pantallaMensaje	= "Tel no config";
	LCD_pos_xy(4,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaTemp_No_Conf(void){
	pantallaMensaje	= "Temp no config";
	 LCD_pos_xy(3,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaHum_No_Conf(void){
	pantallaMensaje	= "Hum no config";
	LCD_pos_xy(4,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaCritico(void){
	pantallaMensaje	= "CRITICO";
	LCD_pos_xy(6,1);
	LCD_write_string(pantallaMensaje);
}

void mostrarTemperaturaInterior(int tempi){
	pantallaMensaje	= "T.I: ";
	LCD_pos_xy(1,2);
	LCD_write_string(pantallaMensaje);
	numASCII(tempi);
	LCD_write_string(valor);
}
void mostrarTemperaturaExterior(int tempe){
	pantallaMensaje	= "T.E: ";
	LCD_pos_xy(11,2);
	LCD_write_string(pantallaMensaje);
	numASCII(tempe);
	LCD_write_string(valor);	
}
void mostrarHumedadInterior(int humi){
	pantallaMensaje	= "H.I: ";
	LCD_pos_xy(1,3);
	LCD_write_string(pantallaMensaje);
	numASCII(humi);
	LCD_write_string(valor);
}
void mostrarHumedadExterior(int hume){
	pantallaMensaje	= "H.E: ";
	LCD_pos_xy(11,3);
	LCD_write_string(pantallaMensaje);
	numASCII(hume);
	LCD_write_string(valor);
}

void mostrarNumeral(void){
	LCD_pos_xy(MAX_X-1, 3);
	LCD_write_char('#');
}