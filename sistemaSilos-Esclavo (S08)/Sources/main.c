#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <Tipos.h>
#include <MEF.h>
#include <RTC.h>
#include <SCI.h>
#include <MTIM.h>

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */
extern volatile unsigned char RTC_flagms;
extern unsigned char flag_envdato;
void main(void) {
	
  //Inicializacion del MCU, MEF y condiciones iniciales del SCI
  MCU_init();	/* call Device Initialization */
  MEF_init();
  SCI_deshabIdleint();
  MTIM_inicializar();
  SCI_inicializar();
  
  for(;;) {
	  MEF_actualizarEstado();
	  MEF_actualizarSalida();
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}


