#ifndef SCI_H_
#define SCI_H_

#define DATO 1
#define ESTADO 2
#define ID 1



void SCI_inicializar(void);
void SCI_habilitarTrans(void);
void SCI_habilitarRec(void);
void SCIrx_handler(void);
void SCI_Write_char(char);
void SCIrx_handler(void);
void SCItx_handler(void);
void SCI_habIdleint(void);
void SCI_deshabIdleint(void);
void SCI_habintRec(void);
void SCI_deshabintRec(void);
unsigned char SCI_verifPaquete(void);
#endif /* SCI_H_ */
