#ifndef _GPRS_CONFIG_H
#define _GPRS_CONFIG_H

#ifndef GPRS_OK
#define GPRS_OK 0
#endif

#ifndef GPRS_INIT_ERROR
#define GPRS_INIT_ERROR 4
#endif

void gprs_init(void);
char* get_dest_te_number(void);
char* get_src_te_number(void);
int set_dest_te_number(char* new_dest_te_number);

#endif