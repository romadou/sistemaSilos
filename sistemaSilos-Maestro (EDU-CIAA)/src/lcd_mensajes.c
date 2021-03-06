/**
 * @brief Controlador de los mensajes que se muestran por la pantalla lcd
 * 
 * @file lcd_mensajes.c
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */

#include "lcd_mensajes.h"
#include "lcd.h"
#include "string.h"

/* Variables privadas */
/* Formato de muestra de mensaje */
char pantallaMensaje[MAX_X];
/* Formato de muestra de los valores numéricos */
char valor[4];
/* Posición del valor numérico ingresado */
int pos = 0;
/* Referencia al valor numérico ingresado */
configurable cb=NC;

/* Funciones privadas */
void mostrarNormal(void); /* Visualización del mensaje "NORMAL" en la primera línea del LCD */
void mostrarAlerta(void); /* Visualización del mensaje "ALERTA" en la primera línea del LCD */
void mostrarProblemaTemperatura(void); /* Visualización del mensaje de problema de temperatura en la segunda línea del LCD */
void mostrarProblemaHumedad(void); /* Visualización del mensaje de problema de humedad en la segunda línea del LCD */
void mostrarProblemaVentilando(void); /* Visualización del mensaje de alerta de ventilación encendida en la segunda línea del LCD */
void mostrarProblemaSensor(void); /* Visualización del mensaje de problema de desconexion del sensor en la segunda línea del LCD */
void mostrarProblemaGPRS(void); /* Visualización del mensaje de problema de desconexion GPRS en la segunda línea del LCD */
void mostrarProblemaVentilacion(void); /* Visualización del mensaje de alerta de ventilación no funciona en la segunda línea del LCD */
void mostrarProblemaTel_No_Conf(void); /* Visualización del mensaje de problema de no configuración de telefóno en la segunda línea del LCD */
void mostrarProblemaTemp_No_Conf(void); /* Visualización del mensaje de problema de no configuración de temperatura en la segunda línea del LCD */ 
void mostrarProblemaHum_No_Conf(void); /* Visualización del mensaje de problema de no configuración de humedad en la segunda línea del LCD */
void mostrarProblemaCritico(void); /* Visualización del mensaje de alerta crítica en la segunda línea del LCD */
void mostrarTemperaturaInterior(int tempi); /* Visualización del mensaje "T.I:" con su valor en la tercera línea del LCD */
void mostrarTemperaturaExterior(int tempe); /* Visualización del mensaje "T.E:" con su valor en la tercera línea del LCD */
void mostrarHumedadInterior(int humi); /* Visualización del mensaje "H.I:" con su valor en la cuarta línea del LCD */
void mostrarHumedadExterior(int hume); /* Visualización del mensaje "H.E:" con su valor en la cuarta línea del LCD */
void mostrarNumeral(void); /* Visualización del caracter numeral en el rincón derecho inferior del LCD */
void numASCII(int num); /* Transformación de un valor numérico a caracter */


void LCD_menuBienvenida(void){
	LCD_init(DISPLAY_8X5|_2_LINES, DISPLAY_ON|CURSOR_OFF|CURSOR_NOBLINK);

	LCD_limpiarPantalla();
	strcpy(pantallaMensaje, "Bienvenido al");
	LCD_pos_xy(3,0);
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "Sistema de Control");
	LCD_pos_xy(1,1);
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "para Silos");
	LCD_pos_xy(5,2);
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "AKMM");	
	LCD_pos_xy(8,3);
	LCD_write_string(pantallaMensaje);
} 

void LCD_menuOpciones(void){
	LCD_limpiarPantalla();
	strcpy(pantallaMensaje, "1. Reporte General");
	LCD_pos_xy(0,0);
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "2. Ver Config Actual");
	LCD_pos_xy(0,1);
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "3. Config Temp y Hum");
	LCD_pos_xy(0,2);
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "4. Config Tel");
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

	// Segunda línea
	LCD_limpiarLinea(1);
	switch (p){
		case TEMPERATURA : 	
			mostrarProblemaTemperatura();
		break;
		case HUMEDAD : 	
			mostrarProblemaHumedad();
		break;
		case VENTILANDO : 	
			mostrarProblemaVentilando();
		break;
		case SENSOR : 	
			mostrarProblemaSensor();
		break;
		case GPRS : 
			mostrarProblemaGPRS();
		break;
		case VENTILACION : 	
			mostrarProblemaVentilacion();
		break;
		case TEL_NO_CONF :	
			mostrarProblemaTel_No_Conf();
		break;
		case TEMP_NO_CONF : 
			mostrarProblemaTemp_No_Conf();
		break;
		case HUM_NO_CONF : 	
			mostrarProblemaHum_No_Conf();
		break;
		case CRITICO : 	
			mostrarProblemaCritico();
		break;
		case OK : 	
		default:	
			LCD_limpiarLinea(1);
		break;
	}

	// Final de display
	mostrarNumeral();
}

void LCD_sensoresActivos(int sensores_activos){
	LCD_limpiarLinea(1);
	LCD_pos_xy(0,1);
	strcpy(pantallaMensaje, "Sensores activos: ");
	LCD_write_string(pantallaMensaje);
	numASCII(sensores_activos);
	LCD_write_string(valor);
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
		case TEMPERATURA : 	
			mostrarProblemaTemperatura();
		break;
		case HUMEDAD : 	
			mostrarProblemaHumedad();
		break;
		case VENTILANDO : 	
			mostrarProblemaVentilando();
		break;
		case SENSOR : 	
			mostrarProblemaSensor();
		break;
		case GPRS : 	
			mostrarProblemaGPRS();
		break;
		case VENTILACION : 	
			mostrarProblemaVentilacion();
		break;
		case TEL_NO_CONF :	
			mostrarProblemaTel_No_Conf();
		break;
		case TEMP_NO_CONF : 
			mostrarProblemaTemp_No_Conf();
		break;
		case HUM_NO_CONF : 	
			mostrarProblemaHum_No_Conf();
		break;
		case CRITICO : 	
			mostrarProblemaCritico();
		break;
		case OK : 	
		default:	
			LCD_limpiarLinea(1);
		break;
	}

	// Tercera y Cuarta líneas
	mostrarTemperaturaInterior(tempi);
	mostrarTemperaturaExterior(tempe);
	mostrarHumedadInterior(humi);
	mostrarHumedadExterior(hume);

	// Final de display
	mostrarNumeral();
}

void LCD_menuConfiguracion(configurable c){
	LCD_limpiarPantalla();
	strcpy(pantallaMensaje, "Ingrese");
	LCD_pos_xy(6,0);
	LCD_write_string(pantallaMensaje);
	switch(c){
		case TEL : 
			strcpy(pantallaMensaje, "nro de telefono");
			LCD_pos_xy(2,1);
		break;
		case TEMP : 	
			strcpy(pantallaMensaje, "temperatura");
			LCD_pos_xy(4,1);
		break;
		case HUM : 	
			strcpy(pantallaMensaje, "humedad");
			LCD_pos_xy(6,1);
		break;
		default : ;
	}
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "*:Guardar #:Cancelar");
	LCD_pos_xy(0,3);
	LCD_write_string(pantallaMensaje);
	switch(c){
		case TEL : 
			LCD_pos_xy(4,2);
		break;
		case TEMP : 	
			LCD_pos_xy(4,2);
		break;
		case HUM : 	
			LCD_pos_xy(8,2);
		break;
		default : ;
	}
	cb = c;
}

void LCD_configIngresarNum(char num){
	LCD_write_char(num);
	pos++;
}

void LCD_configBorrarChar(void){
	pos--;
	switch(cb){
		case TEL : 
			LCD_pos_xy(4+pos,2);
			LCD_write_char(' ');
			LCD_pos_xy(4+pos,2);
		break;
		case TEMP : 	
			LCD_pos_xy(4+pos,2);
			LCD_write_char(' ');
			LCD_pos_xy(4+pos,2);
		break;
		case HUM : 	
			LCD_pos_xy(8+pos,2);
			LCD_write_char(' ');
			LCD_pos_xy(8+pos,2);
		break;
		default : ;
	}
}

void LCD_configConfirmarNum(void){
	LCD_limpiarPantalla();
	strcpy(pantallaMensaje, "VALOR");
	LCD_pos_xy(7,1);
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "GUARDADO");
	LCD_pos_xy(6,2);
	LCD_write_string(pantallaMensaje);
	pos = 0;
	cb = NC;
}

void LCD_configEliminarNum(void){
	LCD_limpiarPantalla();
	strcpy(pantallaMensaje, "OPERACION");
	LCD_pos_xy(5,1);
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "CANCELADA");
	LCD_pos_xy(5,2);
	LCD_write_string(pantallaMensaje);
	pos = 0;
	cb = NC;
}

void LCD_configErrorNum(void){
	LCD_limpiarPantalla();
	strcpy(pantallaMensaje, "VALOR FUERA");
	LCD_pos_xy(4,1);
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "DE RANGO");
	LCD_pos_xy(6,2);
	LCD_write_string(pantallaMensaje);
	pos = 0;
	cb = NC;
}

void LCD_menuConfigActual(int temp, int hum, char* tel){
	LCD_limpiarPantalla();
	strcpy(pantallaMensaje, "Config Actual");
	LCD_pos_xy(3,0);
	LCD_write_string(pantallaMensaje);
	strcpy(pantallaMensaje, "Temp: ");
	LCD_pos_xy(2,1);
	LCD_write_string(pantallaMensaje);
	numASCII(temp);
	LCD_write_string(valor);
	strcpy(pantallaMensaje, "Hum: ");
	LCD_pos_xy(2,2);
	LCD_write_string(pantallaMensaje);
	numASCII(hum);
	LCD_write_string(valor);
	strcpy(pantallaMensaje, "Tel: ");
	LCD_pos_xy(2,3);
	LCD_write_string(pantallaMensaje);
	LCD_write_string(tel);
	mostrarNumeral();
}

void LCD_limpiarLinea(int l){
	if (l < MAX_Y){
		strcpy(pantallaMensaje, "                    ");
		LCD_pos_xy(0,l);
		LCD_write_string(pantallaMensaje);
	}
}

void LCD_limpiarPantalla(void){
	int l;
	for (l=0;l<MAX_Y;l++){
		strcpy(pantallaMensaje, "                    ");
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
		else{
			valor[0] = '0' + num;
			valor[1] = '\0';
		}
	}
}

void mostrarNormal(void){
	strcpy(pantallaMensaje, "FUNC NORMAL");
	LCD_pos_xy(4,0);
	LCD_write_string(pantallaMensaje);
}
void mostrarAlerta(void){
	strcpy(pantallaMensaje, "ALERTA");
	LCD_pos_xy(7,0);
	LCD_write_string(pantallaMensaje);
}

void mostrarProblemaTemperatura(void){
	strcpy(pantallaMensaje, "Temp alta");
	LCD_pos_xy(5,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaHumedad(void){
	strcpy(pantallaMensaje, "Hum alta");
	LCD_pos_xy(6,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaVentilando(void){
	strcpy(pantallaMensaje, "Ventilando");
	LCD_pos_xy(5,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaSensor(void){
	strcpy(pantallaMensaje, "Sensor caido");
	LCD_pos_xy(3,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaGPRS(void){
	strcpy(pantallaMensaje, "GPRS OFF");
	LCD_pos_xy(6,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaVentilacion(void){
	strcpy(pantallaMensaje, "Vent caido");
	LCD_pos_xy(5,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaTel_No_Conf(void){
	strcpy(pantallaMensaje, "Tel no config");
	LCD_pos_xy(4,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaTemp_No_Conf(void){
	strcpy(pantallaMensaje, "Temp no config");
	 LCD_pos_xy(3,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaHum_No_Conf(void){
	strcpy(pantallaMensaje, "Hum no config");
	LCD_pos_xy(4,1);
	LCD_write_string(pantallaMensaje);
}
void mostrarProblemaCritico(void){
	strcpy(pantallaMensaje, "CRITICO");
	LCD_pos_xy(6,1);
	LCD_write_string(pantallaMensaje);
}

void mostrarTemperaturaInterior(int tempi){
	strcpy(pantallaMensaje, "T.I: ");
	LCD_pos_xy(1,2);
	LCD_write_string(pantallaMensaje);
	if (tempi == 255){
		strcpy(valor, "XX");	
	}
	else{
		numASCII(tempi);
	}
	LCD_write_string(valor);
}
void mostrarTemperaturaExterior(int tempe){
	strcpy(pantallaMensaje, "T.E: ");
	LCD_pos_xy(11,2);
	LCD_write_string(pantallaMensaje);
	if (tempe == 255){
		strcpy(valor, "XX");	
	}
	else{
		numASCII(tempe);
	}
	LCD_write_string(valor);
}
void mostrarHumedadInterior(int humi){
	strcpy(pantallaMensaje, "H.I: ");
	LCD_pos_xy(1,3);
	LCD_write_string(pantallaMensaje);
	if (humi == 255){
		strcpy(valor, "XX");	
	}
	else{
		numASCII(humi);
	}
	LCD_write_string(valor);
}
void mostrarHumedadExterior(int hume){
	strcpy(pantallaMensaje, "H.E: ");
	LCD_pos_xy(11,3);
	LCD_write_string(pantallaMensaje);
	if (hume == 255){
		strcpy(valor, "XX");	
	}
	else{
		numASCII(hume);
	}
	LCD_write_string(valor);
}

void mostrarNumeral(void){
	LCD_pos_xy(MAX_X-1, 3);
	LCD_write_char('#');
}
