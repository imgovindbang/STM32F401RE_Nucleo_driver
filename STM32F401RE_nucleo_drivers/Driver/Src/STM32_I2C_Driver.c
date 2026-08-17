//

#include "STM32_driver.h"

uint32_t AHB_PreSclar[8] = {2, 4, 8, 16, 64, 128, 256, 512};
uint8_t APB1_PreSclar[4] = {2, 4, 8, 16};

static void I2C_GetStartCondition(I2C_Handle_t *pI2CHandle);

static void I2C_SendSlaveAddress(I2C_Handle_t *pI2CHandle, uint8_t SlaveAddress);

static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle);
static void I2C_GetStopCondition(I2C_Handle_t *pI2CHandle);




static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle)
{
	uint32_t falseRead = pI2CHandle -> pI2C ->I2C_SR1;
	falseRead = pI2CHandle -> pI2C ->I2C_SR2;
	(void)falseRead;
}

static void I2C_SendSlaveAddress(I2C_Handle_t *pI2CHandle, uint8_t SlaveAddress)
{
	SlaveAddress = SlaveAddress << 1;
	SlaveAddress &= ~(1);
	pI2CHandle -> pI2C ->I2C_DR = SlaveAddress;
}

static void I2C_GetStopCondition(I2C_Handle_t *pI2CHandle)
{
	pI2CHandle -> pI2C -> I2C_CR1 |= (1 << CR1_STOP);
}

uint32_t RCC_PLLOutClk(void)
{
	return 0; //Need to implement later
}


uint32_t RCC_PCLK1Value(void)
{
	uint32_t pclk1, sysclk;

	uint8_t clksrc, temp, ahb, apb1;

	//clock source

	clksrc = ((RCC -> CFGR >> 2) & 0x3);

	if(clksrc == 0)
	{
		sysclk = 16000000;
	}else if(clksrc == 1)
	{
		sysclk = 8000000;
	}else if(clksrc == 2)
	{
		sysclk = RCC_PLLOutClk();
	}


	//AHB PreSclar
	temp = ((RCC -> CFGR >> 4) &  0XF);

	if(temp < 8)
	{
		ahb = 1;
	}else
	{
		ahb = AHB_PreSclar[temp - 8];
	}


	//APB1 PreSclar

	temp = ((RCC -> CFGR >> 10) & 0x7);

	if(temp < 4)
	{
		apb1 = 1;
	}else
	{
		apb1 = APB1_PreSclar[temp - 4];
	}

	pclk1 = (sysclk / ahb) / apb1;

	return pclk1;
}


uint8_t I2C_GetFlagStatsu(I2C_RegDef_t *pI2C, uint32_t FlagName)
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
void I2C_PClkControl(I2C_RegDef_t *pI2C, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
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
	}else
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
}


void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t temp = 0;

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
	if(pI2CHandle -> I2C_Handle.I2C_SCLSpeed == I2C_SPEED_SM)
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


}

void I2C_DeInit(I2C_RegDef_t *pI2C)
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

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *TxBuffer , uint32_t Len, uint8_t SlaveAddress)
{
	 //1. Generate Start condition
	I2C_GetStartCondition(pI2CHandle);

	//2. Check the SB flag in the SR1 Register
	while(!I2C_GetFlagStatus(pI2CHandle -> pI2C, SR1_SB));

	//3. Sent Slave address with r/w bit
	I2C_SendSlaveAddress(pI2CHandle,SlaveAddress);

	//4. Clear ADDR Flag in SR1
	while(!I2C_GetFlagStatus(pI2CHandle -> pI2C, SR1_ADDR));

	//5.
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
	I2C_GetStopCondition(pI2CHandle);

}

static void I2C_GetStartCondition(I2C_Handle_t *pI2CHandle)
{
	pI2CHandle -> pI2C -> I2C_CR1 |= (1 << CR1_START);
}


void I2C_PeriContr(I2C_RegDef_t *pI2C, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		pI2C -> I2C_CR1 |= (1 << CR1_PE);
	}else
	{
		pI2C -> I2C_CR1 &= ~(1 << CR1_PE);
	}
}


//I2C Interrupt handling
void I2C_IRQIntrConfig(uint16_t IRQnumber, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
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
	}else{
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
}

void I2C_IRQPrioConfig(uint16_t IRQnumber,uint32_t IRQpriority)
{
	uint8_t prix = IRQpriority / 4;
	uint8_t prix_section = IRQpriority % 4;
	uint8_t shift = (8 * prix_section) + (8 - 4);
	*(NVIC_PR_BASE_ADDR + prix ) |=  IRQpriority << shift;
}
