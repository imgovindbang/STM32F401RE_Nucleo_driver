#ifndef INC_STM32_USART_DRIVER_H_
#define INC_STM32_USART_DRIVER_H_

#include "STM32_driver.h"

/* USART user configuration */

typedef struct
{
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t  Tx_State;
	uint8_t  Rx_State;
}USART_StoreData;

typedef struct
{
	uint8_t USART_Mode;
	uint8_t USART_Baudrate;
	uint8_t USART_StopBits;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;
}USART_Config;

/* USART Handle */
typedef struct
{
	USART_Registers *pUSART;
	USART_Config USART_Config;
	USART_StoreData USART_Data;
}USART_Handle;


/* Macros for SR register Bits*/
enum
{
	USART_SR_PE,
	USART_SR_FE,
	USART_SR_NF,
	USART_SR_ORE,
	USART_SR_IDLE,
	USART_SR_RXNE,
	USART_SR_TC,
	USART_SR_TXE,
	USART_SR_LBD,
	USART_SR_CTS
};

/* Macros for CR1 Register Bits*/
enum
{
	USART_CR1_SBK,
	USART_CR1_RWU,
	USART_CR1_RE,
	USART_CR1_TE,
	USART_CR1_IDLEIE,
	USART_CR1_RXNEIE,
	USART_CR1_TCIE,
	USART_CR1_TXEIE,
	USART_CR1_PEIE,
	USART_CR1_PS,
	USART_CR1_PCE,
	USART_CR1_WAKE,
	USART_CR1_M,
	USART_CR1_UE,
//	USART_CR1_RESERVED,
	USART_CR1_OVER8 = 15
};

/* Macros for CR2 Register Bits */
enum
{
	USART_CR2_ADD,
//	USART_CR2_RESERVED = 4,
	USART_CR2_LBDL = 5,
	USART_CR2_LBDIE,
//	USART_CR2_RESERVED,
	USART_CR2_LBCL = 8,
	USART_CR2_CPHA,
	USART_CR2_CPOL,
	USART_CR2_CLKEN,
	USART_CR2_STOP,
	USART_CR2_LINEN = 14
};

/* Macros for CR3 Register Bits */
enum
{
	USART_CR3_EIE,
	USART_CR3_IREN,
	USART_CR3_IRLP,
	USART_CR3_HDSEL,
	USART_CR3_NACK,
	USART_CR3_SCEN,
	USART_CR3_DMAR,
	USART_CR3_DMAT,
	USART_CR3_RTSE,
	USART_CR3_CTSE,
	USART_CR3_CTSIE,
	USART_CR3_ONEBIT
};

/* @USART Modes*/
enum
{
	USART_TX,
	USART_RX,
	USART_TXRX
};


/* @USART baud rate */

#define USART_BAUD_RATE_1200 		1200				/*< Desired :  1.2KBps >*/
#define USART_BAUD_RATE_2400 		2400				/*< Desired :  2.4KBps >*/
#define USART_BAUD_RATE_9600 		9600				/*< Desired :  9.6KBps >*/
#define USART_BAUD_RATE_19200 		19200				/*< Desired :  19.2KBps >*/
#define USART_BAUD_RATE_38400 		38400				/*< Desired :  38.4KBps >*/
#define USART_BAUD_RATE_57600 		57600				/*< Desired :  57.6KBps >*/
#define USART_BAUD_RATE_115200 		115200				/*< Desired :  115.2KBps >*/
#define USART_BAUD_RATE_230400 		230400				/*< Desired :  230.4KBps >*/
#define USART_BAUD_RATE_460800 		460800				/*< Desired :  460.8KBps >*/
#define USART_BAUD_RATE_921600 		921600				/*< Desired :  921.6KBps >*/
#define USART_BAUD_RATE_2M 			2000000				/*< Desired :  2MBps >*/
#define USART_BAUD_RATE_3M 			3000000				/*< Desired :  3MBps >*/


/* @Parity control */

enum
{
	DISABLE_PARITY,
	EVEN_PARITY,
	ODD_PARITY,
};

/* @USART Word length*/
enum
{
	USART_8BIT,
	USART_9BIT
};

/* @USART Stop bit*/
enum
{
	USART_STOP1,
	USART_STOP0_5,
	USART_STOP2,
	USART_STOP1_5,
};

/* @USART Hardware control flow*/
enum
{
	USART_NONE,
	USART_CTSE,
	USART_RTSE,
	USART_CTSE_RTSE
};



enum
{
	USART_READY,
	USART_BUSY_TX,
	USART_BUSY_RX
};
/****************************************************************************************************************************************************************/

/*										USART API implementation																																*/

/****************************************************************************************************************************************************************/

//API for Peripheral clock enable for USART
void USART_PClkControl(USART_Registers *pUSART, uint8_t ENorDI);

//USART Initialization API
void USART_Init(USART_Handle *pHandle);

//USART DeInitialization API
void USART_DeInit(USART_Registers *pUSART);

//USART Send data API
void USART_SendData(USART_Handle *pHandle, uint8_t *pTxBuffer, uint32_t Length);

//USART Receive data API
void USART_ReceiveData(USART_Handle *pHandle, uint8_t *pRxBuffer, uint32_t Length);

//Send and Receive data in interrupt mode
uint8_t USART_SendDataIT(USART_Handle *pHandle,uint8_t *pTxBuffer, uint32_t Length);
uint8_t USART_ReceiveDataIT(USART_Handle *pHandle, uint8_t *pRxBuffer, uint32_t Length);


//IRQ Configuration and ISR handling
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle *pHandle);


//Supporting APIs to control peripheral
void USART_PeripheralControl(USART_Registers *pUSART, uint8_t EnOrDi);
uint8_t USART_GetFlagStatus(USART_Registers *pUSART , uint32_t FlagName);
void USART_ClearFlag(USART_Registers *pUSART, uint16_t StatusFlagName);

//Application callback
void USART_ApplicationEventCallback(USART_Handle *pHandle,uint8_t AppEv);

void USART_BaudRate(USART_Registers *pUSART, uint32_t Baudrate);


#endif /* INC_STM32_USART_DRIVER_H_ */
