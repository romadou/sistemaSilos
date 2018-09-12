/**
 * @brief Controlador de la interfaz UART
 * 
 * @file uart.c
 * @author Arambarri-Krasowski-Madou-Maxit
 * @date 2018-08
 */
 
#include "uart.h"
#include "chip.h"
#include "stdint.h"
#include "cmsis.h"

/**
 * @brief   Configs UART
 * @param   uart     : UART channel to be configured
 * @param   baudRate : baud rate to be configured
 * @return  Nothing
 */
void uartConfig(uint8_t uart, uint32_t baudRate){
	switch(uart){
		case UART_USBX: 
			/* Init Uart 2 */
			Chip_UART_Init(LPC_USART2);
			/* Set Baud rate */
   		Chip_UART_SetBaud(LPC_USART2, baudRate);  
   		/* Modify FCR (FIFO Control Register)*/
   		Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV3); 
   		/* Enable UART Transmission */
   		Chip_UART_TXEnable(LPC_USART2); 
   		/* Set pin functions */ 
   		Chip_SCU_PinMux(UART_USB_TXD_P, UART_USB_TXD_P_ , MD_PDN, FUNC6);              /* P7_1,FUNC6: UART_USB_TXD */
   		/* Set direction pin function */
   		Chip_SCU_PinMux(UART_USB_RXD_P, UART_USB_RXD_P_ , MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2,FUNC6: UART_USB_RXD */
   	break;
   	case UART_RS485:
   		/* Init Uart 0 */
			Chip_UART_Init(LPC_USART0);
			/* Set Baud Rate*/
			Chip_UART_SetBaud(LPC_USART0, baudRate);
			/* Enable TX and RX 16 character FIFO */
			Chip_UART_SetupFIFOS(LPC_USART0, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV3);
			/* Enable Uart TX */
			Chip_UART_TXEnable(LPC_USART0);
			/* Set data to 8N1 */
			Chip_UART_ConfigData(LPC_USART0, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);
			/* Set pin functions */ 
			Chip_SCU_PinMux(UART_RS485_TXD_P, UART_RS485_TXD_P_, MD_PDN, FUNC7);              /* P9_5: UART0_TXD */
			Chip_SCU_PinMux(UART_RS485_RXD_P, UART_RS485_RXD_P_, MD_PLN|MD_EZI|MD_ZI, FUNC7); /* P9_6: UART0_RXD */
			/* Set RS-485 flags*/ /* Auto Direction Control Enabled */
			Chip_UART_SetRS485Flags(LPC_USART0, UART_RS485CTRL_DCTRL_EN | UART_RS485CTRL_OINV_1);
			/* Set direction pin function */
			Chip_SCU_PinMux(UART_RS485_DIR_P, UART_RS485_DIR_P_, MD_PDN, FUNC2);              /* P6_2: UART0_DIR */
		break;
		case UART_RS232:
			/* Init Uart 3 */
		   Chip_UART_Init(LPC_USART3);
		   /* Set Baud rate */
   		Chip_UART_SetBaud(LPC_USART3, baudRate);  
   		/* Modify FCR (FIFO Control Register)*/
   		Chip_UART_SetupFIFOS(LPC_USART3, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV3); 
   		/* Enable UART Transmission */
   		Chip_UART_TXEnable(LPC_USART3); 
   		/* Set pin functions */ 
   		Chip_SCU_PinMux(UART_RS232_TXD_P, UART_RS232_TXD_P_ , MD_PDN, FUNC2);                         /* P2_3,FUNC2: UART_RS232_TXD */
   		/* Set direction pin function */
   		Chip_SCU_PinMux(UART_RS232_RXD_P, UART_RS232_RXD_P_ , MD_PLN|MD_EZI|MD_ZI, FUNC2);           /* P2_4,FUNC2: UART_RS232_RXD */
		break;
      case UART_0:
         /* Init Uart 0 */
         Chip_UART_Init(LPC_USART0);
         /* Set Baud rate */
         Chip_UART_SetBaud(LPC_USART0, baudRate);  
         /* Modify FCR (FIFO Control Register)*/
         Chip_UART_SetupFIFOS(LPC_USART0, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV3); 
         /* Enable UART Transmission */
         Chip_UART_TXEnable(LPC_USART0); 
         /* Set pin functions */ 
         Chip_SCU_PinMux(UART_0_TXD_P, UART_0_TXD_P_ , SCU_MODE_INACT | SCU_MODE_ZIF_DIS, FUNC2);                       /* P6_4,FUNC2: UART_0_TXD */
         /* Set pin functions */
         Chip_SCU_PinMux(UART_0_RXD_P, UART_0_RXD_P_ , SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS, FUNC2);           /* P6_5,FUNC2: UART_0_RXD */
      break;
      case UART_2:
         /* Init Uart 2 */
         Chip_UART_Init(LPC_USART2);
         /* Set Baud rate */
         Chip_UART_SetBaud(LPC_USART2, baudRate);  
         /* Modify FCR (FIFO Control Register)*/
         Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV3); 
         /* Enable UART Transmission */
         Chip_UART_TXEnable(LPC_USART2); 
         /* Set pin functions */ 
         Chip_SCU_PinMux(UART_2_TXD_P, UART_2_TXD_P_ , MD_PDN, FUNC1);                       /* P1_15,FUNC1: UART_2_TXD */
         /* Set direction pin function */
         Chip_SCU_PinMux(UART_2_RXD_P, UART_2_RXD_P_ , MD_PLN|MD_EZI|MD_ZI, FUNC1);           /* P1_16,FUNC1: UART_2_RXD */
      break;
	}
   
}

/**
 * @brief   Enables Rx Interrupt
 * @param   uart     : UART channel to be configured
 * @return  Nothing
 */
void uartEnableRxInterrupt(uint8_t uart){
	switch(uart){
      case UART_2:
		case UART_USBX: 
			/* Enable RX interrupt */
   			Chip_UART_IntEnable(LPC_USART2, UART_IER_RBRINT);
   			NVIC_ClearPendingIRQ(USART2_IRQn);
   			NVIC_EnableIRQ(USART2_IRQn);
      break;
      case UART_0:
      case UART_RS485:
   		/* Enable RX interrupt */
			Chip_UART_IntEnable(LPC_USART0, UART_IER_RBRINT);
			NVIC_ClearPendingIRQ(USART0_IRQn);
			NVIC_EnableIRQ(USART0_IRQn);
		break;
		case UART_RS232:
			/* Enable RX interrupt */
			Chip_UART_IntEnable(LPC_USART3, UART_IER_RBRINT);
			NVIC_ClearPendingIRQ(USART3_IRQn);
			NVIC_EnableIRQ(USART3_IRQn);
		break;
   	}
}

/**
 * @brief   Disables Rx Interrupt
 * @param   uart     : UART channel to be configured
 * @return  Nothing
 */
void uartDisableRxInterrupt(uint8_t uart){
	switch(uart){
      case UART_2:
		case UART_USBX: 
			/* Disable RX interrupt */
   			Chip_UART_IntDisable(LPC_USART2, UART_IER_RBRINT);
   			NVIC_DisableIRQ(USART2_IRQn);

      	break;
         case UART_0:
      	case UART_RS485:
      		/* Disable RX interrupt */
   			Chip_UART_IntDisable(LPC_USART0, UART_IER_RBRINT);
   			NVIC_DisableIRQ(USART0_IRQn);
   		break;
   		case UART_RS232:
   			/* Disable RX interrupt */
   			Chip_UART_IntDisable(LPC_USART3, UART_IER_RBRINT);
   			NVIC_DisableIRQ(USART3_IRQn);
   		break;
   	}
}


/**
 * @brief   Reads 1 byte from UART
 * @param   uart     : UART channel to be read
 * @return  NO_ERROR if data was received, NO_DATA_RECEIVED_ERROR if not
 * @note    Non Blocking Receive
 */
uint8_t uartReceiveByte(uint8_t uart, uint8_t *data){ 
	switch(uart){
      case UART_2:
		case UART_USBX: 
			if (Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_RDR) {
      			*data = Chip_UART_ReadByte(LPC_USART2);
      			return NO_ERROR;
   			}
   			else return NO_DATA_RECEIVED_ERROR;
      	break;
      case UART_0:
      case UART_RS485:
      	if (Chip_UART_ReadLineStatus(LPC_USART0) & UART_LSR_RDR) {
      		*data = Chip_UART_ReadByte(LPC_USART0);
      		return NO_ERROR;
   		}
   		else return NO_DATA_RECEIVED_ERROR;
   	break;
   	case UART_RS232:
   		if (Chip_UART_ReadLineStatus(LPC_USART3) & UART_LSR_RDR) {
      		*data = Chip_UART_ReadByte(LPC_USART3);
      		return NO_ERROR;
   		}
   		else return NO_DATA_RECEIVED_ERROR;
   	break;
   }
	
}

/**
 * @brief   Reads N bytes from UART
 * @param   uart     : UART channel to be read
 * @param   data     : Pointer to where to store data
 * @param   length   : Bytes to be read
 * @return  Nothing
 * @note    Blocking Receive
 */
void uartReceiveString(uint8_t uart, uint8_t data[], uint8_t length){  
	uint8_t received_length=0, n;
   
	switch(uart){
      case UART_2:
		case UART_USBX: 
			while(received_length!=length){
            n=uartReceiveByte(UART_USBX, &data[received_length]);
            while(NO_DATA_RECEIVED_ERROR == n)
               n=uartReceiveByte(UART_USBX, &data[received_length]);
            received_length++;
         }
      break;
      case UART_RS485:
      case UART_0:
      	while(received_length!=length){
            n=uartReceiveByte(UART_RS485, &data[received_length]);
            while(NO_DATA_RECEIVED_ERROR == n)
               n=uartReceiveByte(UART_RS485, &data[received_length]);
            received_length++;
         }
   	break;
   	case UART_RS232:
   		while(received_length!=length){
            n=uartReceiveByte(UART_RS232, &data[received_length]);
            while(NO_DATA_RECEIVED_ERROR == n)
               n=uartReceiveByte(UART_RS232, &data[received_length]);
            received_length++;
         }
   	break;
   }
}



/**
 * @brief   Writes 1 byte from UART
 * @param   uart     : UART channel to be written
 * @param   data     : data to be written
 * @return  Nothing
 */
void uartWriteByte(uint8_t uart, uint8_t data){
	switch(uart){
      case UART_2:
		case UART_USBX: 
			/* Wait for space in FIFO */
			while ((Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_THRE) == 0); 
   			Chip_UART_SendByte(LPC_USART2, data);
   	break;
      case UART_0:
   	case UART_RS485:
      	/* Wait for space in FIFO */
			while ((Chip_UART_ReadLineStatus(LPC_USART0) & UART_LSR_THRE) == 0); 
   			Chip_UART_SendByte(LPC_USART0, data);
		break;
		case UART_RS232:
   		/* Wait for space in FIFO */
			while ((Chip_UART_ReadLineStatus(LPC_USART3) & UART_LSR_THRE) == 0); 
   			Chip_UART_SendByte(LPC_USART3, data);
   	break;
   	}
}

/**
 * @brief   Writes N bytes from UART
 * @param   uart     : UART channel to be written
 * @param   data     : Pointer to data to be written
 * @return  Nothing
 */
void uartWriteString(uint8_t uart, char* data){
	while(*data){
	   uartWriteByte(uart, (uint8_t)*data);
	   data++;
   }
}

/**
 * @brief   Resets UART FIFO
 * @param   uart     : UART channel
 * @return  Nothing
 */
void uartResetFIFO(uint8_t uart){
   switch(uart){
      case UART_2:
      case UART_USBX: 
         /* Modify FCR (FIFO Control Register)*/
         Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TRG_LEV3); 
      break;
      case UART_0:
      case UART_RS485:
         /* Modify FCR (FIFO Control Register)*/
         Chip_UART_SetupFIFOS(LPC_USART0, UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TRG_LEV3); 
      break;
      case UART_RS232:
         /* Modify FCR (FIFO Control Register)*/
         Chip_UART_SetupFIFOS(LPC_USART3, UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TRG_LEV3); 
      break;
   }
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/