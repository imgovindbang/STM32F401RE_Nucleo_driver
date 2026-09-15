/* This File Contain The Header File For I2C Drivers*/

#ifndef INC_STM32_I2C_DRIVER_H_
#define INC_STM32_I2C_DRIVER_H_

#include "STM32_driver.h"

/* I2C Application Status */

#define I2C_READY		0
#define I2C_BUSY_IN_RX	1
#define I2C_BUSY_IN_TX	2

#define I2C_DISABLE_SR  0
#define I2C_ENABLE_SR   1

enum
{
	I2C_EVENT_STOP,
	I2C_EVENT_RX_COMP,
	I2C_EVENT_TX_COMP,
	I2C_ERROR_BERR,
	I2C_ERROR_ARLO,
	I2C_ERROR_AF,
	I2C_ERROR_OVR,
	I2C_ERROR_TIMEOUT,
	I2C_EVENT_DATA_REQ,
	I2C_EVENT_DATA_REC
};


/* @I2C Control Register 1 (I2C_CR1)*/
enum
{
	CR1_PE,
	CR1_SMBUS,
	CR1_RESERVED1,
	CR1_SMBTYPE,
	CR1_ENARP,
	CR1_ENPEC,
	CR1_ENGC,
	CR1_NOSTRETCH,
	CR1_START,
	CR1_STOP,
	CR1_ACK,
	CR1_POS,
	CR1_PEC,
	CR1_ALERT,
	CR1_RESERVED2,
	CR1_SWRST
};


/* @I2C Control Register 2 (I2C_CR2)*/
enum
{
	CR2_FREQ,
	CR2_RESERVED1 = 6,
	CR2_ITERREN = 8,
	CR2_ITEVTEN,
	CR2_ITBUFEN,
	CR2_DMAEN,
	CR2_LAST,
	CR2_RESERVED2,
};

/* @I2C Status Register 1 I2S_SR1*/

enum
{
	SR1_SB,
	SR1_ADDR,
	SR1_BTF,
	SR1_ADD10,
	SR1_STOPF,
	SR1_RESERVED1,
	SR1_RxNE,
	SR1_TxE,
	SR1_BERR,
	SR1_ARLO,
	SR1_AF,
	SR1_OVR,
	SR1_PECERR,
	SR1_RESERVED2,
	SR1_TIMEOUT,
	SR1_SMBALERT
};

/* @I2C Status Register 2 I2S_SR2 */
enum
{
	SR2_MSL,
	SR2_BUSY,
	SR2_TRA,
	SR2_RESERVED1,
	SR2_GENCALL,
	SR2_SMBDE_FAULT,
	SR2_SMB_HOST,
	SR2_DUALF,
	SR2_PEC
};



/* @I2C Clock control register (I2C_CCR) Macros */
#define CCR 			    0			/*< Bits 11:0 CCR[11:0]: Clock control register in Fm/Sm mode  >*/
#define I2C_DUTY			14			/*< BBit 14 DUTY: Fm mode duty cycle 0: Fm mode tlow/thigh = 2 1: Fm mode tlow/thigh = 16/9 (see CCR)  >*/
#define I2C_MODE_SELECT		15			/*< Bit 15 F/S: I2C controller mode selection  0: Sm mode I2C  1: Fm mode I2C  >*/



/* @I2C Configuration Structure */

typedef struct
{
	volatile uint32_t I2C_SCLSpeed;
	volatile uint32_t I2C_DeviceAddr;
	volatile uint32_t I2C_ACK;
	volatile uint32_t I2C_FMDutyCycle;
}I2C_Config;

/* I2C Interrupt helping to store data */
typedef struct
{
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t  Tx_Rx_State;
	uint8_t  Device_Address;
	uint32_t RxSize;
	uint8_t  sr;
}I2C_StoreData;

/* @I2C Handle Structure */

typedef struct
{
	I2C_Registers *pI2C;
	I2C_Config I2C_Handle;
	I2C_StoreData I2C_DataStore;
}I2C_Handle;


/* @I2C_SCLSpeed Macros*/
#define I2C_SPEED_SM		100000					/* I2C Serial clock Speed in Standard mode 100KHz*/
#define I2C_SPEED_NM		200000					/* I2C Serial clock Speed in Normal mode 200KHz*/
#define I2C_SPEED_FM		400000					/* I2C Serial clock Speed in Fast mode 400KHz*/


/* @I2C_ACK Macros*/
#define I2C_ACK_DISBALE		0						/* Automatic Acknowledgment Disable */
#define I2C_ACK_ENABLE		1						/* Automatic Acknowledgment Enable */

/* @I2C_FMDutyCycle Macros*/
#define I2C_FMDUTY_MODE2 		0
#define I2C_FMDUTY_MODE16_9 	1



/****************************************************************************************************************************************************************/

/*								I2C API implementation																																*/

/****************************************************************************************************************************************************************/


/* I2C peripheral clock enable */

void I2C_PClkControl(I2C_Registers *pI2Cx, uint8_t ENorDI);

/* I2C Initialization and De-initialization*/

void I2C_Init(I2C_Handle *pI2CHandle);
void I2C_DeInit(I2C_Registers *pI2C);

/* I2C send and received data*/

void I2C_MasterSendData(I2C_Handle *pI2CHandle, uint8_t *TxBuffer , uint32_t Len, uint8_t SlaveAddress, uint8_t sr);

void I2C_MasterReciveData(I2C_Handle *pI2CHandle, uint8_t *RxBuffer , uint32_t Len, uint8_t SlaveAddress, uint8_t sr);

void I2C_StopDataSent(I2C_Handle *pI2CHandle);
void I2C_StopReceiveData(I2C_Handle *pI2CHandle);


// I2C Flag status
uint8_t I2C_GetFlagStatus(I2C_Registers *pI2C, uint32_t FlagName);

/* I2C Interrupt Handle	*/
void I2C_IRQIntr_Config(uint16_t IRQnumber, uint8_t ENorDI);
void I2C_IRQPerio_Config(uint16_t IRQnumber,uint32_t IRQpriority);
void I2C_EV_IRQHandling(I2C_Handle *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle *pI2CHandle);


void I2C_PeriContr(I2C_Registers *pI2Cx, uint8_t ENorDI);
void I2C_SSIEn(I2C_Registers *pI2Cx, uint8_t ENorDI);



void I2C_Appli_Event_CB(I2C_Handle *I2C_Handle, uint8_t I2C_EVENT_RX_COMP);


/****************************************************************************************************************************************************************/

/*								I2C API implementation for Interrupt handling																															*/

/******************sa**********************************************************************************************************************************************/

uint8_t I2C_MasterSendData_INT(I2C_Handle *pI2CHandle, uint8_t *TxBuffer , uint32_t Len, uint8_t SlaveAddress, uint8_t sr);

uint8_t I2C_ReceiveSendData_INT(I2C_Handle *pI2CHandle, uint8_t *RxBuffer , uint32_t Len, uint8_t SlaveAddress, uint8_t sr);


/****************************************************************************************************************************************************************/

/*								I2C API implementation for Slave working																															*/

/****************************************************************************************************************************************************************/
void I2C_SlaveSendData(I2C_Registers *pI2Cx, uint8_t data);
uint8_t I2C_SlaveReceiveData(I2C_Registers *pI2Cx);




#endif /* INC_STM32_I2C_DRIVER_H_ */
