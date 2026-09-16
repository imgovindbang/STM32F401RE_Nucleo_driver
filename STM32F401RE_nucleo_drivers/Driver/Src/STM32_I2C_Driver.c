//

#include "STM32_driver.h"

#define READ 	1
#define WRITE	0

static void I2C_GetStartCondition(I2C_Handle *pI2CHandle);

static void I2C_RD_WR_SlaveAddr(I2C_Handle *pI2CHandle, uint8_t SlaveAddress, uint8_t ReadorWrite);

static void I2C_ClearADDRFlag(I2C_Handle *pI2CHandle);
static void I2C_GetStopCondition(I2C_Handle *pI2CHandle);
static void I2C_ACK_Control(I2C_Handle *pI2CHandle, uint8_t Disable);
static void I2C_TXE_Flag_INTR(I2C_Handle *pI2CHandle);
static void RXNE_FLAG_INTR_Handle(I2C_Handle *pI2CHandle);
static void BTF_Flag_INTR(I2C_Handle *pI2CHandle);





static void BTF_Flag_INTR(I2C_Handle *pI2CHandle)
{
	//Check for TX and RX state
	if(pI2CHandle -> I2C_DataStore.Tx_Rx_State == I2C_BUSY_IN_TX)
	{
		if(pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_TxE))
		{
			//It mean Both the BTF and TX is Set
			//Means the Shift register and data register is empty

			//1. generate the stop condition
			//Check for Tx Length before generation stop condition
			if(pI2CHandle -> I2C_DataStore.TxLen == 0)
			{

					if(pI2CHandle -> I2C_DataStore.sr == I2C_DISABLE_SR)
						I2C_GetStopCondition(pI2CHandle);

				//2. Reset all member element of handle
				I2C_StopDataSent(pI2CHandle);

				//3. Notify the application about transmission complete
				I2C_Appli_Event_CB(pI2CHandle, I2C_EVENT_TX_COMP);
			}
		}
	}
}




static void RXNE_FLAG_INTR_Handle(I2C_Handle *pI2CHandle)
{

	//Check for Device Mode
	if(pI2CHandle -> pI2C -> I2C_SR2 & (1 << SR2_MSL))
	{
		//Check for State
		if(pI2CHandle -> I2C_DataStore.Tx_Rx_State == I2C_BUSY_IN_RX)
		{
			if(pI2CHandle -> I2C_DataStore.RxLen == 1)
			{
				*(pI2CHandle -> I2C_DataStore.pRxBuffer) = pI2CHandle -> pI2C -> I2C_DR;

				pI2CHandle -> I2C_DataStore.pRxBuffer++;
			}

			if(pI2CHandle -> I2C_DataStore.RxLen > 1)
			{
				if(pI2CHandle -> I2C_DataStore.RxLen == 2)
				{
					//Disable ACK
					I2C_ACK_Control(pI2CHandle, DISABLE);
				}
				*(pI2CHandle -> I2C_DataStore.pRxBuffer) = pI2CHandle -> pI2C -> I2C_DR;
				pI2CHandle -> I2C_DataStore.pRxBuffer++;
				pI2CHandle -> I2C_DataStore.RxLen--;
			}
		}

		if(pI2CHandle -> I2C_DataStore.RxLen == 0)
		{
			//Stop the Transmission and Notify the Application

			//1. Generate Stop Condition
			if(pI2CHandle -> I2C_DataStore.sr == I2C_DISABLE_SR)
				I2C_GetStopCondition(pI2CHandle);

			//2. Close The Reception
			I2C_StopReceiveData(pI2CHandle);

			//3. Notify the application
			I2C_Appli_Event_CB(pI2CHandle, I2C_EVENT_RX_COMP);


		}
	}else
	{
		//slave mode
		if(! (pI2CHandle -> pI2C -> I2C_SR2 & (1 << SR2_TRA)))
		{
			I2C_Appli_Event_CB(pI2CHandle, I2C_EVENT_DATA_REC);
		}
	}
}

static void I2C_TXE_Flag_INTR(I2C_Handle *pI2CHandle)
{
	//This Only applicable if Device in master mode so check the device is in master or not by SR2 Register by checking bit MSL
			if(pI2CHandle -> pI2C -> I2C_SR2 & (1 << SR2_MSL))
			{
				if(pI2CHandle -> I2C_DataStore.Tx_Rx_State == I2C_BUSY_IN_TX)
				{
					if(pI2CHandle -> I2C_DataStore.TxLen > 0)
					{
						//Read into DR
						pI2CHandle -> pI2C -> I2C_DR = *(pI2CHandle -> I2C_DataStore.pTxBuffer);

						//Decrement the Tx Length;
						pI2CHandle -> I2C_DataStore.TxLen--;

						//Increase TxBuffer address
						pI2CHandle -> I2C_DataStore.pTxBuffer++;
					}
				}
			}else
			{
				//Slave mode
				if(pI2CHandle -> pI2C -> I2C_SR2 & (1 << SR2_TRA))
				{
					I2C_Appli_Event_CB(pI2CHandle, I2C_EVENT_DATA_REQ);
				}
			}

}
static void I2C_ClearADDRFlag(I2C_Handle *pI2CHandle)
{
	uint32_t falseRead;
	//Check for device mode
	if(pI2CHandle -> pI2C -> I2C_SR2 & (1 << SR2_MSL))
	{
		//Check for State
		if(pI2CHandle -> I2C_DataStore.Tx_Rx_State == I2C_BUSY_IN_RX)
		{
			if(pI2CHandle -> I2C_DataStore.RxLen == 1)
			{
				//Disable ACK
				I2C_ACK_Control(pI2CHandle, I2C_ACK_DISBALE);

				//Clear ADDR Flag
				falseRead = pI2CHandle -> pI2C ->I2C_SR1;
				falseRead = pI2CHandle -> pI2C ->I2C_SR2;
				(void)falseRead;
			}
		}
		else
		{
			//Clear ADDR Flag
			falseRead = pI2CHandle -> pI2C ->I2C_SR1;
			falseRead = pI2CHandle -> pI2C ->I2C_SR2;
			(void)falseRead;
		}
	}
	else
	{
		falseRead = pI2CHandle -> pI2C ->I2C_SR1;
		falseRead = pI2CHandle -> pI2C ->I2C_SR2;
		(void)falseRead;
	}
}

//Slave Read write address
static void I2C_RD_WR_SlaveAddr(I2C_Handle *pI2CHandle, uint8_t SlaveAddress, uint8_t ReadorWrite)
{
	if(ReadorWrite == READ)
	{
		SlaveAddress = SlaveAddress << 1;
		SlaveAddress |= 1;
		pI2CHandle -> pI2C -> I2C_DR = SlaveAddress;
	}else if(ReadorWrite == WRITE)
	{
		SlaveAddress = SlaveAddress << 1;
		SlaveAddress &= ~(1);
		pI2CHandle -> pI2C ->I2C_DR = SlaveAddress;
	}
}

static void I2C_GetStopCondition(I2C_Handle *pI2CHandle)
{
	pI2CHandle -> pI2C -> I2C_CR1 |= (1 << CR1_STOP);
}


//Disable ACK
static void I2C_ACK_Control(I2C_Handle *pI2CHandle, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		pI2CHandle -> pI2C -> I2C_CR1 |= (1 << CR1_ACK);
	}else
	{
		pI2CHandle -> pI2C -> I2C_CR1 &= ~(1 << CR1_ACK);
	}

}







uint8_t I2C_GetFlagStatus(I2C_Registers *pI2C, uint32_t FlagName)
{
	if(pI2C -> I2C_SR1 & FlagName)
	{
		return FLAG_SET;
	}else
	{
		return FLAG_RESET;
	}
}

//I2C peripheral clock control
void I2C_Peri_Clk_Enable(I2C_Registers *pI2C)
{
	if(pI2C == I2C1)
	{
		I2C1_PCLK_EN();
	}else if(pI2C == I2C2)
	{
		I2C2_PCLK_EN();
	}else if(pI2C == I2C3)
	{
		I2C3_PCLK_EN();
	}
}


void I2C_Peri_Clk_Disable(I2C_Registers *pI2C)
{
	if(pI2C == I2C1)
	{
		I2C1_PCLK_DI();
	}else if(pI2C == I2C2)
	{
		I2C2_PCLK_DI();
	}else if(pI2C == I2C3)
	{
		I2C3_PCLK_DI();
	}
}

void I2C_Init(I2C_Handle *pI2CHandle)
{
	uint32_t temp = 0;

	//Enable I2C Peripheral clock
	I2C_Peri_Clk_Enable(pI2CHandle -> pI2C);

	//1. Control ACK bit in CR1

	temp |= (pI2CHandle -> I2C_Handle.I2C_ACK << 10);
	pI2CHandle -> pI2C->I2C_CR1 = temp;

	//2. configure the FREQ field
	temp = 0;
	temp |= (RCC_PCLK1Value() / 1000000U);
	pI2CHandle -> pI2C->I2C_CR2 = (temp & 0x3F);

	//Device address
	temp = 0;
	temp |= (pI2CHandle -> I2C_Handle.I2C_DeviceAddr << 1);
	temp |= (1 << 14);											//This bit should always be 1 by software according to reference manual
	pI2CHandle -> pI2C -> I2C_OAR1 = temp;

	//CCR Calculation
	uint16_t ccr_value = 0;
	temp = 0;
	if(pI2CHandle -> I2C_Handle.I2C_SCLSpeed <= I2C_SPEED_SM)
	{
		//Standard Mode
		ccr_value = (RCC_PCLK1Value() / (2 * pI2CHandle -> I2C_Handle.I2C_SCLSpeed));
		temp |= (ccr_value & 0xFFF);
	}else
	{
		//Fast Mode
		temp |= ( 1 << 15);
		temp |= (pI2CHandle ->I2C_Handle.I2C_FMDutyCycle << 14);
		if(pI2CHandle -> I2C_Handle.I2C_FMDutyCycle == I2C_FMDUTY_MODE2)
		{
			ccr_value = (RCC_PCLK1Value() / (3 * pI2CHandle -> I2C_Handle.I2C_SCLSpeed));
		}else
		{
			ccr_value = (RCC_PCLK1Value() / (25 * pI2CHandle -> I2C_Handle.I2C_SCLSpeed));
		}
		temp |= (ccr_value & 0xFFF);
	}

	pI2CHandle -> pI2C -> I2C_CCR = temp;

	//Calculating TRISE

	if(pI2CHandle -> I2C_Handle.I2C_SCLSpeed <= I2C_SPEED_SM)
	{
		//Standard Mode
		temp = (RCC_PCLK1Value() / 1000000U) + 1;
	}else
	{
		//Fast Mode
		temp = ((RCC_PCLK1Value() * 300 )/ 1000000000U) + 1;
	}
	pI2CHandle -> pI2C -> I2C_TRISE = (temp & 0x3F);

}

void I2C_DeInit(I2C_Registers *pI2C)
{
	if(pI2C == I2C1)
	{
		I2C1_RCC_RESET();
	}else if(pI2C == I2C2)
	{
		I2C2_RCC_RESET();
	}else if(pI2C == I2C3)
	{
		I2C3_RCC_RESET();
	}
}

/* Data Send and Received API*/

void I2C_MasterSendData(I2C_Handle *pI2CHandle, uint8_t *TxBuffer , uint32_t Len, uint8_t SlaveAddress, uint8_t sr)
{
	 //1. Generate Start condition
	I2C_GetStartCondition(pI2CHandle);

	//2. Check the SB flag in the SR1 Register
	while(!I2C_GetFlagStatus(pI2CHandle -> pI2C, SR1_SB));

	//3. Sent Slave address with r/w bit
	I2C_RD_WR_SlaveAddr(pI2CHandle,SlaveAddress, WRITE);

	//4.
	while(!I2C_GetFlagStatus(pI2CHandle -> pI2C, SR1_ADDR));

	//5.Clear ADDR Flag in SR1
	I2C_ClearADDRFlag(pI2CHandle);

	//6.
	while(Len > 0)
	{
		while(!I2C_GetFlagStatus(pI2CHandle -> pI2C, SR1_TxE));
		pI2CHandle -> pI2C -> I2C_DR = *TxBuffer;
		TxBuffer++;
		Len--;
	}

	//7.
	while(!I2C_GetFlagStatus(pI2CHandle -> pI2C, SR1_TxE));
	while(!I2C_GetFlagStatus(pI2CHandle -> pI2C, SR1_BTF));

	//8.
	if(pI2CHandle -> I2C_DataStore.sr == sr)
		I2C_GetStopCondition(pI2CHandle);
}

static void I2C_GetStartCondition(I2C_Handle *pI2CHandle)
{
	pI2CHandle -> pI2C -> I2C_CR1 |= (1 << CR1_START);
}


void I2C_MasterReciveData(I2C_Handle *pI2CHandle, uint8_t *RxBuffer , uint32_t Len, uint8_t SlaveAddress, uint8_t sr)
{
	//1. Generate Start condition
	I2C_GetStartCondition(pI2CHandle);

	//2. Confirm that start generation is complete by checking the SB flag in SR1
	while(! I2C_GetFlagStatus(pI2CHandle -> pI2C , SR1_SB));
	//3. Send the address of the slave with r/nw bit set to R(1) (total 8 bit)
	I2C_RD_WR_SlaveAddr(pI2CHandle,SlaveAddress, READ);
	//4. wait until address phase is complete by checking the ADDR flag in the SR1
	while(! I2C_GetFlagStatus(pI2CHandle -> pI2C, SR1_ADDR));
	//Read data if length is 1
	if(Len == 1)
	{
		//Disable ACK
		I2C_ACK_Control(pI2CHandle, DISABLE);
		//Generate stop condition
		I2C_GetStopCondition(pI2CHandle);
		//Clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle);
		//Wait until RXNE become 1
		while(! I2C_GetFlagStatus(pI2CHandle -> pI2C, SR1_RxNE));
		//read data in to buffer
		*RxBuffer = pI2CHandle -> pI2C -> I2C_DR;

		return;
	}

	if(Len > 1)
	{
		//Clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle);
		//Read data until Length become zero
		for(uint32_t i = Len; i > 0; i--)
		{
			//Wait until RXNE become 1
			while(! I2C_GetFlagStatus(pI2CHandle -> pI2C, SR1_RxNE));
			if(Len == 2)
			{
				//Clear the ACK bit
				I2C_ACK_Control(pI2CHandle, DISABLE);
				//Generate stop condition
				I2C_GetStopCondition(pI2CHandle);
			}

			//Read the data from DR (Data Register) in to buffer
			*RxBuffer = pI2CHandle -> pI2C -> I2C_DR;
			//Increment buffer address
			RxBuffer++;
		}
	}
	//Re-enable ACK
	if(pI2CHandle -> I2C_Handle.I2C_ACK == ENABLE)
	{
		I2C_ACK_Control(pI2CHandle, ENABLE);
	}
}

void I2C_Enable(I2C_Registers *pI2C)
{
	pI2C -> I2C_CR1 |= (1 << CR1_PE);
}

void I2C_Disable(I2C_Registers *pI2C)
{
		pI2C -> I2C_CR1 &= ~(1 << CR1_PE);
}

//I2C Interrupt handling
void I2C_IRQIntr_Enable(uint16_t IRQnumber)
{
	if(IRQnumber < 32)
	{
		//Set ISER0(Interrupt Set-enable Registers)
		*NVIC_ISER0 |= (1U << IRQnumber);
	}else  if(IRQnumber >= 32 && IRQnumber < 64)
	{
		//Set ISER1(Interrupt Set-enable Registers)
		*NVIC_ISER1 |= (1U << IRQnumber % 32);
	}else if(IRQnumber >= 64 && IRQnumber < 96)
	{
		//Set ISER2(Interrupt Set-enable Registers)
		*NVIC_ISER2 |= (1U << IRQnumber % 32);
	}
}

void I2C_IRQIntr_Disable(uint16_t IRQnumber)
{
	if(IRQnumber < 32)
	{
		//Clear ICER0(Interrupt Clear-enable Registers)
		*NVIC_ICER0 |= (1U << IRQnumber);
	}else  if(IRQnumber >= 32 && IRQnumber < 64)
	{
		//Clear ICER1(Interrupt Clear-enable Registers)
		*NVIC_ICER1 |= (1U << IRQnumber % 32);
	}else if(IRQnumber >= 64 && IRQnumber < 96)
	{
		//Clear ICER2(Interrupt Clear-enable Registers)
		*NVIC_ICER2 |= (1U << IRQnumber % 32);
	}
}

void I2C_IRQPrioConfig(uint16_t IRQnumber,uint32_t IRQpriority)
{
	uint8_t prix = IRQpriority / 4;
	uint8_t prix_section = IRQpriority % 4;
	uint8_t shift = (8 * prix_section) + (8 - 4);
	*(NVIC_PR_BASE_ADDR + prix ) |=  IRQpriority << shift;
}


void I2C_StopReceiveData(I2C_Handle *pI2CHandle)
{
	//Disable ITBUFEN Bit
	pI2CHandle -> pI2C -> I2C_CR2 &= ~(1 << CR2_ITBUFEN);

	//Disable ITEVTEN Bit
	pI2CHandle -> pI2C -> I2C_CR2 &= ~(1 << CR2_ITEVTEN);

	pI2CHandle -> I2C_DataStore.Tx_Rx_State = I2C_READY;
	pI2CHandle -> I2C_DataStore.pRxBuffer = NULL;
	pI2CHandle -> I2C_DataStore.RxLen = 0;
	pI2CHandle -> I2C_DataStore.RxSize = 0;
	if(pI2CHandle -> I2C_Handle.I2C_ACK == I2C_ACK_ENABLE)
		I2C_ACK_Control(pI2CHandle, ENABLE);
}

void I2C_StopDataSent(I2C_Handle *pI2CHandle)
{
	//Disable ITBUFEN Bit
	pI2CHandle -> pI2C -> I2C_CR2 &= ~(1 << CR2_ITBUFEN);

	//Disable ITEVTEN Bit
	pI2CHandle -> pI2C -> I2C_CR2 &= ~(1 << CR2_ITEVTEN);

	pI2CHandle -> I2C_DataStore.Tx_Rx_State = I2C_READY;
	pI2CHandle -> I2C_DataStore.pTxBuffer = NULL;

	pI2CHandle -> I2C_DataStore.TxLen = 0;
}


uint8_t I2C_MasterSendData_INT(I2C_Handle *pI2CHandle, uint8_t *TxBuffer , uint32_t Len, uint8_t SlaveAddress, uint8_t sr)
{
	uint8_t I2C_State = pI2CHandle -> I2C_DataStore.Tx_Rx_State;

	if((I2C_State != I2C_BUSY_IN_TX) && (I2C_State != I2C_BUSY_IN_RX))
	{
		pI2CHandle -> I2C_DataStore.pTxBuffer = TxBuffer;
		pI2CHandle -> I2C_DataStore.TxLen = Len;
		pI2CHandle -> I2C_DataStore.Tx_Rx_State = I2C_BUSY_IN_TX;
		pI2CHandle -> I2C_DataStore.Device_Address = SlaveAddress;
		pI2CHandle -> I2C_DataStore.sr = sr;

		//Start Condition
		I2C_GetStartCondition(pI2CHandle);

		//Enable ITBUFEN control bit in CR2 register
		pI2CHandle -> pI2C-> I2C_CR2 |= (1 << CR2_ITBUFEN);

		//Enable ITEVTEN control bit in CR2 register
		pI2CHandle -> pI2C -> I2C_CR2 |= (1 << CR2_ITEVTEN);

		//Enable ITERREN control bit in CR2 register
		pI2CHandle -> pI2C -> I2C_CR2 |= (1 << CR2_ITERREN);
	}
	return I2C_State;
}

uint8_t I2C_ReceiveSendData_INT(I2C_Handle *pI2CHandle, uint8_t *RxBuffer , uint32_t Len, uint8_t SlaveAddress, uint8_t sr)
{
	uint8_t I2C_State = pI2CHandle -> I2C_DataStore.Tx_Rx_State;

	if((I2C_State != I2C_BUSY_IN_TX) && (I2C_State != I2C_BUSY_IN_RX))
	{
		pI2CHandle -> I2C_DataStore.pRxBuffer = RxBuffer;
		pI2CHandle -> I2C_DataStore.RxLen = Len;
		pI2CHandle -> I2C_DataStore.Tx_Rx_State = I2C_BUSY_IN_RX;
		pI2CHandle -> I2C_DataStore.RxSize = Len;
		pI2CHandle -> I2C_DataStore.Device_Address = SlaveAddress;
		pI2CHandle -> I2C_DataStore.sr = sr;
	}
	return I2C_State;
}

void I2C_EV_IRQHandling(I2C_Handle *pI2CHandle)
{
	//Handling Event IRQ
	uint8_t temp1, temp2, temp3;

	temp1 = pI2CHandle -> pI2C -> I2C_CR2 & (1 << CR2_ITEVTEN);
	temp2 = pI2CHandle -> pI2C -> I2C_CR2 & (1 << CR2_ITBUFEN);

	//Handle for SB Flag
	temp3 = pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_SB);

	if(temp1 && temp3)
	{
		//SB flag is set
		//Interrupt is generated because of SB event
		//Cleared by software by reading the SR1 register followed by writing the DR register, or by hardware when PE=0
		if(pI2CHandle -> I2C_DataStore.Tx_Rx_State == I2C_BUSY_IN_TX)
		{
			I2C_RD_WR_SlaveAddr(pI2CHandle, pI2CHandle -> I2C_Handle.I2C_DeviceAddr, WRITE);
		}else if(pI2CHandle -> I2C_DataStore.Tx_Rx_State == I2C_BUSY_IN_RX)
		{
			I2C_RD_WR_SlaveAddr(pI2CHandle, pI2CHandle -> I2C_Handle.I2C_DeviceAddr, READ);
		}
	}

	//Handle for ADDR Flag
	temp3 = pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_ADDR);

	if(temp1 && temp3)
	{
		//ADDR flag is set
		I2C_ClearADDRFlag(pI2CHandle);
	}

	//Handle for BTF flag
	temp3 = pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_BTF);
	if(temp1 && temp3)
	{
		//BTF flag is set
		BTF_Flag_INTR(pI2CHandle);
	}

	//Handle for STOPF Flag
	temp3 = pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_STOPF);
	if(temp1 && temp3)
	{
		//STOPF Flag is set

		//Clear STOPF Flag ( Cleared by software reading the SR1 register followed by a write in the CR1 register, )
		pI2CHandle -> pI2C -> I2C_CR1 |= 0x0000;			//Writing into CR1

		//Notify the Application about STOPF condition
		I2C_Appli_Event_CB(pI2CHandle, I2C_EVENT_STOP);
	}

	//Handle for TXE Flag
	temp3 = pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_TxE);
	if(temp1 && temp2 && temp3)
	{
		//TXE Flag is set
		I2C_TXE_Flag_INTR(pI2CHandle);
	}

	//Handle for RXNE Flag
	temp3 = pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_RxNE);
	if(temp1 && temp2 && temp3)
	{
		//RXNE Flag is set
		RXNE_FLAG_INTR_Handle(pI2CHandle);

	}


}

void I2C_ER_IRQHandling(I2C_Handle *pI2CHandle)
{
	uint32_t temp1, temp2;

	//Check the status of ITERREN control Bit
	temp1 = pI2CHandle -> pI2C -> I2C_CR2 & (1 << CR2_ITERREN);

	//Check for Bus Error in SR1 Register for Bit BERR
	temp2 = pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_BERR);

	if(temp1 && temp2)
	{
		//This is Bus Error

		//Code to Clear Bus Error
		pI2CHandle -> pI2C -> I2C_SR1 &= ~(1 << SR1_BERR);

		//Code to Notify the Bus error
		I2C_Appli_Event_CB(pI2CHandle, I2C_ERROR_BERR);

	}

	//Check for Arbitration lost

	temp2 = pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_ARLO);

	if(temp1 && temp2)
	{
		//This is Arbitration lost

		//Code to clear Arbitration lost Cleared by software writing 0
		pI2CHandle -> pI2C -> I2C_SR1 &= ~(1 << SR1_ARLO);

		//Notify the application about the Arbitration error
		I2C_Appli_Event_CB(pI2CHandle, I2C_ERROR_ARLO);
	}

	//Check for ACK failure

	temp2 = pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_AF);

	if(temp1 && temp2)
	{
		//ACK failure
		//Cleared by software writing 0 at SR1 register at AF bit
		pI2CHandle -> pI2C -> I2C_SR1 &= ~(1 << SR1_AF);

		//Notify application about ACK failure
		I2C_Appli_Event_CB(pI2CHandle, I2C_ERROR_AF);
	}

	//Check for Overrun / Underrun Error
	 temp2 = pI2CHandle -> pI2C -> I2C_SR1 & (1 << SR1_OVR);

	 if(temp1 && temp2)
	 {
		 //Overrun / Underrun error

		 //Cleared by software writing 0 at SR1 register at OVR bit
 		 pI2CHandle -> pI2C -> I2C_SR1 &= ~(1 << SR1_OVR);

 		 //Notify application about failure
 		 I2C_Appli_Event_CB(pI2CHandle, I2C_ERROR_OVR);

	 }

	 //Check for Time out error

	 temp2 = pI2CHandle -> pI2C ->I2C_SR1 & (1 << SR1_TIMEOUT);

	 if(temp1 && temp2)
	 {
		 //Timeout Error

		 //Clear by software writing 0 in SR1 register at Bit TIMEOUT
		 pI2CHandle -> pI2C ->I2C_SR1 &= ~(1 << SR1_TIMEOUT);

		 //Notify the application about TIMEOUT error
		 I2C_Appli_Event_CB(pI2CHandle, I2C_ERROR_TIMEOUT);
	 }
}



void I2C_SlaveSendData(I2C_Registers *pI2Cx, uint8_t data)
{
	pI2Cx -> I2C_DR = data;
}


uint8_t I2C_SlaveReceiveData(I2C_Registers *pI2Cx)
{
	return (uint8_t)pI2Cx -> I2C_DR;
}
