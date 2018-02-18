#ifndef GPRS_H_
#define GPRS_H_

#ifndef BAUD_RATE
#define BAUD_RATE 9600
#endif

void GPRS_config(void);
void GPRS_config(int baud_rate);
void GPRS_config(int baud_rate, char *dest_num);
void GPRS_alerta(void);
void GPRS_critico(void);
void GPRS_set_dest_num(char *dest_num);

#endif /* #ifndef GPRS_H_ */