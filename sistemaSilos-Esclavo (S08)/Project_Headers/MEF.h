#ifndef MEF_H_
#define MEF_H_

typedef enum{ESPERANDO, INICIALIZAR, DELAY_DHT,RECPARAMETROS, TRANS_UC, REC_UC} state;
void MEF_actualizarEstado(void);
void MEF_actualizarSalida(void);
void MEF_init(void);
#endif /* MEF_H_ */
