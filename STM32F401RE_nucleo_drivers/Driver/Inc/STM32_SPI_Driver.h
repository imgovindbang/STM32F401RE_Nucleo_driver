
#ifndef STM32_SPI_DRIVER_H_
#define STM32_SPI_DRIVER_H_


#include "STM32_driver.h"

typedef struct
{
	uint8_t SPI_Device_Mode;
	uint8_t SPI_Bus_Config;
	uint8_t SPI_DFF;
	uint8_t SPI_CPHA;
	uint8_t SPI_CPOL;
	uint8_t SPI_SSM;
	uint8_t SPI_Speed;
}SPI_Config_t;


typedef struct
{
	uint8_t *pTxBuffer;					/*	< To Store the TxBuffer	>	*/
	uint8_t *pRxBuffer;					/*	< To Store the RxBuffer	>	*/
	uint8_t TxLen;						/*	< To Store the TxBuffer Length	>	*/
	uint8_t Rxlen;						/*	< To Store the RxBuffer	Length  >	*/
	uint8_t TxState;					/*	< To Store the TxBuffer State 	>	*/
	uint8_t RxState;					/*	< To Store the RxBuffer	State   >	*/
}SPI_Store_Data_t;


typedef struct
{
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPI_Config;
	SPI_Store_Data_t *SPI_Data_Store;
}SPI_Handle_t;


/* @SPI Device Mode */

typedef enum
{
	SPI_DEVICE_MODE_SLAVE,
	SPI_DEVICE_MODE_MASTER
}Device_Mode;

/* @SPI Bus Configuration*/

typedef enum
{
	SPI_FULL_DUPLEX = 1,
	SPI_HALF_DUPLEX,
	SPI_SIMPLEX_RXONLY
}SPI_Bus_config;

/* @SPI DFF (Data frame format)*/

typedef enum
{
	SPI_DFF_8BIT,
	SPI_DFF_16BIT
}SPI_DFF;


/* @SPI SPEED*/

typedef enum
{
	SPI_SPEED_DIV2,
	SPI_SPEED_DIV4,
	SPI_SPEED_DIV8,
	SPI_SPEED_DIV16,
	SPI_SPEED_DIV32,
	SPI_SPEED_DIV64,
	SPI_SPEED_DIV128,
	SPI_SPEED_DIV256,
}SPI_Speed;

/*	@SPI Clock phase (CPHA)*/

typedef enum
{
	SPI_CPHA_LOW,
	SPI_CPHA_HIGH
}SPI_CPHA;


/* @SPI CPOL (CLock Polarity) */

typedef enum
{
	SPI_CPOL_LOW,
	SPI_CPOL_HIGH
}SPI_CPOL;

/* @SPI SSM (Software slave management) */

typedef enum
{
	SPI_SSM_DI,
	SPI_SSM_EN
}SPI_SSM;


/*****************************************************************************************************************************************************************************************
* 	 	 	 	 	 	 	 	 	 	SPI CR1 (Control Register 1) macros 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 *
******************************************************************************************************************************************************************************************/

typedef enum
{
	SPI_CR1_CPHA,
	SPI_CR1_CPOL,
	SPI_CR1_MSTR,
	SPI_CR1_BR,
	SPI_CR1_SPE = 6,
	SPI_CR1_LSBFIRST,
	SPI_CR1_SSI,
	SPI_CR1_SSM,
	SPI_CR1_RXONLY,
	SPI_CR1_DFF,
	SPI_CR1_CRCNEXT,
	SPI_CR1_CRCEN,
	SPI_CR1_BIDIOE,
	SPI_CR1_BIDIMODE,
}SPI_CR1_Bits;




/*****************************************************************************************************************************************************************************************
* 	 	 	 	 	 	 	 	 	 	SPI CR2 (Control Register 2) macros 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 *
******************************************************************************************************************************************************************************************/

typedef enum
{
	SPI_CR2_RXDMAEN,
	SPI_CR2_TXDMAEN,
	SPI_CR2_SSOE,
	SPI_CR2_Reserved,
	SPI_CR2_FRF,
	SPI_CR2_ERRIE,
	SPI_CR2_RXNEIE,
	SPI_CR2_TXEIE
}SPI_CR2_Bits;




/*****************************************************************************************************************************************************************************************
* 	 	 	 	 	 	 	 	 	 	SPI SR (SPI status Register) macros 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 *
******************************************************************************************************************************************************************************************/

typedef enum
{
	SPI_SR_RXNE,
	SPI_SR_TXE,
	SPI_SR_CHSIDE,
	SPI_SR_UDR,
	SPI_SR_CRCERR,
	SPI_SR_MODF,
	SPI_SR_OVR,
	SPI_SR_BSY,
	SPI_SR_FRE
}SPI_SR_Bits;




/* SPI Status Register Macros */

#define SPI_TXE_FLAG		(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG		(1 << SPI_SR_RXNE)
#define SPI_CHSIDE_FLAG		(1 << SPI_SR_CHSIDE)
#define SPI_UDR_FLAG		(1 << SPI_SR_UDR)
#define SPI_CRCERR_FLAG		(1 << SPI_SR_CRCERR)
#define SPI_MODF_FLAG		(1 << SPI_SR_MODF)
#define SPI_OVR_FLAG		(1 << SPI_SR_OVR)
#define SPI_BSY_FLAG		(1 << SPI_SR_BSY)
#define SPI_FRE_FLAG		(1 << SPI_SR_FRE)



// @SPI State macros

#define SPI_READY			 0
#define SPI_BUSY_IN_TX   	 1
#define SPI_BUSY_IN_RX   	 2




/* @SPI Application Possible Events */

typedef enum
{
	SPI_EVENT_TX_COMP = 1,
	SPI_EVENT_RX_COMP,
	SPI_EVENT_OVR_ERR,
	SPI_EVENT_CRC_ERR
}SPI_Appl_Event;



/****************************************************************************************************************************************************************/

/*								SPI (Serial peripheral interface) API implementation																																*/

/****************************************************************************************************************************************************************/


/* SPI peripheral clock enable */

void SPI_PClkControl(SPI_RegDef_t *pSPIx, uint8_t ENorDI);

/* SPI Initialization and De-initialization*/

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/* Data send and Received */

void SPI_Data_Send(SPI_RegDef_t *pSPIx, uint8_t *TxBuffer  ,uint32_t Size);

void SPI_Data_Received(SPI_RegDef_t *pSPIx, uint8_t *RxBuffer  ,uint32_t Size);

/* Data Send and Received in Interrupt */

uint8_t SPI_Data_SendIntr(SPI_Handle_t *SPI_Handle ,uint8_t *TxBuffer  ,uint32_t Size);

uint8_t SPI_Data_ReceivedIntr(SPI_Handle_t *SPI_Handle, uint8_t *RxBuffer  ,uint32_t Size);

/* SPI Interrupt Handle	*/

void SPI_IRQIntr_Config(uint16_t IRQnumber, uint8_t ENorDI);
void SPI_IRQPerio_Config(uint16_t IRQnumber,uint32_t IRQpriority);
void SPI_IRQHandle(SPI_Handle_t *pHandle);

void SPI_PeriContr(SPI_RegDef_t *pSPIx, uint8_t ENorDI);
void SPI_SSIEn(SPI_RegDef_t *pSPIx, uint8_t ENorDI);


void SPI_Clr_OVRF(SPI_RegDef_t *pSPIx);
void SPI_Close_Transmit(SPI_Handle_t *pHandle);
void SPI_Close_reception(SPI_Handle_t *pHandle);


void SPI_Appli_Event_CB(SPI_Handle_t *SPI_Handle, uint8_t SPI_EVENT_RX_COMP);


#endif /* STM32_SPI_DRIVER_H_ */
