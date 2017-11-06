#include "gprs_config.h"
//#include "gprs_module.h"
#include <string.h>

const char *src_te_number = "+5492215410495"
static char *dest_te_number = "+5492314401890";


int gprs_init(void){
	if (gprs_module_init(dest_te_number) == 0){
		return GPRS_OK;
	}
	else{
		return GPRS_INIT_ERROR;
	}
}

char* get_dest_te_number(void){
	char dest_aux[15];
	strcpy(dest_aux, dest_te_number);
	return dest_aux;
}

char* get_src_te_number(void){
	char src_aux[15];
	strcpy(src_aux, src_te_number);
	return src_aux;
}

/**
 **FUNCIÓN A DESARROLLAR
 **
 **new_dest_te_number:
 **    Número de teléfono destino
 **    Formato "+549xxxxxxxxxx" (sin 15 ni 0)
 **
int set_dest_te_number(char* new_dest_te_number){
	if (strlen(new_dest_te_number) == 14){
		if (new_dest_te_number[0] == '+'){
			strcpy(dest_te_number, new_dest_te_number);
			//gprs_set_number(te_number);
			return TE_SET_OK;
		}
		else{
			return TE_MISSING_PLUS;
		}
	}
	else{
		return TE_INCORRECT_LENGTH;
	}
}
**/