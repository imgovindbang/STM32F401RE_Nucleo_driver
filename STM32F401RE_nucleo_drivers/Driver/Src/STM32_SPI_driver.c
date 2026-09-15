#include "STM32_SPI_Driver.h"

/* SPI peripheral clock enable */

void SPI_PClkControl(SPI_Registers *pSPIx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}else if (pSPIx == SPI4)
		{
			SPI4_PCLK_EN();
		}
	}else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}else if (pSPIx == SPI4)
		{
			SPI4_PCLK_DI();
		}
	}
}

/* SPI Initialization and De-initialization*/

void SPI_Init(SPI_Handle *pSPIHandle)
{
	uint32_t temp = 0;

	//Enable SPI Clock
	SPI_PClkControl(pSPIHandle -> pSPIx, ENABLE);

	//Configure Device mode

	//1. Device Mode
	temp |= pSPIHandle -> SPI_Config.SPI_Device_Mode << 2;

	//Configure the bus
	if(pSPIHandle -> SPI_Config.SPI_Bus_Config == SPI_FULL_DUPLEX)
	{
		//Clear BIDI Mode (Bidirectional data mode enable)
		temp &= ~(1 << 15);

	}
	else if(pSPIHandle -> SPI_Config.SPI_Bus_Config == SPI_HALF_DUPLEX)
	{
		//Set BIDI Mode (Bidirectional data mode enable)
		temp |= (1 << 15);

	}else if(pSPIHandle -> SPI_Config.SPI_Bus_Config == SPI_SIMPLEX_RXONLY)
	{
		//Clear BIDI Mode (Bidirectional data mode enable)
		temp &= ~(1 << 15);
		//Set RXONLY bit
		temp |= (1 << 10);

	}

	//Configure DFF (Data field format)
	temp |= pSPIHandle -> SPI_Config.SPI_DFF << SPI_CR1_DFF;

	//Configure CPHA (Clock Phase)

	temp |= pSPIHandle -> SPI_Config.SPI_CPHA << SPI_CR1_CPHA;

	//Configure CPOL (Clock Polarity)

	temp |= pSPIHandle -> SPI_Config.SPI_CPOL << SPI_CR1_CPOL;

	//Configure SSM (Software slave management

	temp |= pSPIHandle -> SPI_Config.SPI_SSM << SPI_CR1_SSM;

//	//configure Speed (Bade rate)
//
//	temp |= pSPIHandle -> SPI_Config.SPI_Speed << SPI_CR1_Bits; check this later


	pSPIHandle->pSPIx->SPI_CR1 = temp;
}



void SPI_DeInit(SPI_Registers *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_RCC_RESET();
	}else if(pSPIx == SPI2)
	{
		SPI2_RCC_RESET();
	}else if(pSPIx == SPI3)
	{
		SPI3_RCC_RESET();
	}else if(pSPIx == SPI4)
	{
		SPI4_RCC_RESET();
	}
}



/* @SPI Status Flag Status*/

uint8_t SPI_Flag_Status(SPI_Registers *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SPI_SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}


/* @SPI Data send */

void SPI_Data_Send(SPI_Registers *pSPIx, uint8_t *TxBuffer  ,uint32_t Size)
{
	//check the length of data and if length is 0 then exit
	while(Size > 0)
	{
		//wait until the TX buffer is empty
		while((SPI_Flag_Status(pSPIx,SPI_TXE_FLAG) == FLAG_RESET));

		// check the DFF bit for Data format

		if(pSPIx -> SPI_CR1 & (1 << SPI_CR1_DFF))
		{
			//16 Bit data transfer
			pSPIx ->SPI_DR = *((uint16_t*)TxBuffer);
			Size--;
			Size--;
			(uint16_t*)TxBuffer++;
		}else{
			//8 Bit data transfer
			pSPIx -> SPI_DR = *TxBuffer;
			Size--;
			TxBuffer++;
		}
	}
}

/* @SPI Enable and disable function */

void SPI_PeriContr(SPI_Registers *pSPIx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		//Enabling SPI by Set the SPE bit
		pSPIx -> SPI_CR1 |= (1 << SPI_CR1_SPE);
	}else
	{
		//Disabling SPI by Clear the SPE bit
		pSPIx -> SPI_CR1 &= ~(1 << SPI_CR1_SPE);
	}
}


/* @SPI SSI Enable*/
//Its an Internal slave select pin which need to be high to avoid MODF: Mode fault which leads to fail in Master mode and make it to slave

void SPI_SSIEn(SPI_Registers *pSPIx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		pSPIx ->SPI_CR1 |= (1 << SPI_CR1_SSI);
	}else
	{
		pSPIx ->SPI_CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

/* @SPI Data Received*/

void SPI_Data_Received(SPI_Registers *pSPIx, uint8_t *RxBuffer  ,uint32_t Size)
{
	while(Size > 0)
	{
		while(SPI_Flag_Status(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);

		//Check the DFF register
		if(pSPIx -> SPI_CR1 & (1 << SPI_CR1_DFF))
		{
			//16 Bit Data transfer
			*((uint16_t*)RxBuffer) = pSPIx -> SPI_DR;
			Size--;
			Size--;
			(uint16_t*)RxBuffer++;
		}else
		{
			*RxBuffer = pSPIx -> SPI_DR;
			Size--;
			RxBuffer++;
		}
	}
}



/* SPI Interrupt Handle	*/
//check later for correction
void SPI_IRQIntr_Config(uint16_t IRQnumber, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(IRQnumber == IRQ_NO_SPI1)
		{
			//Set ISER0(Interrupt Set-enable Registers)
			*NVIC_ISER0 = (1U << IRQnumber % 32);
		}else if(IRQnumber == IRQ_NO_SPI2)
		{
			//Set ISER1(Interrupt Set-enable Registers)
			*NVIC_ISER1 = (1U << IRQnumber % 32);
		}else if(IRQnumber == IRQ_NO_SPI3)
		{
			//Set ISER2(Interrupt Set-enable Registers)
			*NVIC_ISER2 = (1U << IRQnumber % 32);
		}else if(IRQnumber == IRQ_NO_SPI4)
		{
			//Set ISER(Interrupt Set-enable Registers)
			*NVIC_ISER3 = (1U << IRQnumber % 32);
		}
	}
	else
	{
		if(IRQnumber == IRQ_NO_SPI1)
		{
			//Clear ICER0 (Interrupt Set-enable Registers)
			*NVIC_ICER0 |= (1U << IRQnumber % 32);
		}else if(IRQnumber == IRQ_NO_SPI2)
		{
			//Clear ICER1 (Interrupt Set-enable Registers)
			*NVIC_ICER0 |= (1U << IRQnumber % 32);
		}else if(IRQnumber == IRQ_NO_SPI3)
		{
			//Clear ICER2 (Interrupt Set-enable Registers)
			*NVIC_ICER2 |= (1U << IRQnumber % 32);
		}else if(IRQnumber == IRQ_NO_SPI4)
		{
			//Clear ICER3 (Interrupt Set-enable Registers)
			*NVIC_ICER3 |= (1U << IRQnumber % 32);
		}
	}
}



static void SPI_IntrHandle_TXE(SPI_Handle *pSPI_Handle)
{
	if(pSPI_Handle ->pSPIx -> SPI_CR1 & (1 << SPI_CR1_DFF))
	{
		//16 Bit DFF
		pSPI_Handle -> pSPIx-> SPI_DR = *((uint16_t*)pSPI_Handle->SPI_Data_Store->pTxBuffer);
		pSPI_Handle -> SPI_Data_Store -> TxLen -=2;
		(uint16_t*)pSPI_Handle->SPI_Data_Store->pTxBuffer++;

	}else
	{
		//8 Bit DFF
		pSPI_Handle -> pSPIx-> SPI_DR = *((uint8_t*)pSPI_Handle -> SPI_Data_Store -> pTxBuffer);
		pSPI_Handle -> SPI_Data_Store -> TxLen--;
		(uint8_t*)pSPI_Handle -> SPI_Data_Store -> pTxBuffer++;

		if(!pSPI_Handle ->SPI_Data_Store -> TxLen)
		{
			//Clear TXEIE bit
			pSPI_Handle -> pSPIx ->SPI_CR2 &= ~(1 << SPI_CR2_TXEIE);

			pSPI_Handle -> SPI_Data_Store -> pTxBuffer = NULL;

			pSPI_Handle -> SPI_Data_Store -> TxLen = 0;

			pSPI_Handle ->SPI_Data_Store -> TxState = SPI_READY;

			SPI_Appli_Event_CB(pSPI_Handle, SPI_EVENT_TX_COMP);
		}
	}
}

static void SPI_IntrHandle_RXNEIE(SPI_Handle *pSPI_Handle)
{
	if(pSPI_Handle -> pSPIx -> SPI_CR1 & (1 << SPI_CR1_DFF))
	{
		//16 Bit DFF
		*((uint16_t*)pSPI_Handle -> SPI_Data_Store -> pRxBuffer) = (uint16_t)pSPI_Handle ->pSPIx-> SPI_DR;
		pSPI_Handle -> SPI_Data_Store -> Rxlen -= 2;
		(uint16_t*)pSPI_Handle -> SPI_Data_Store -> pRxBuffer++;

	}else
	{
		//8 Bit DFF
		*((uint8_t*)pSPI_Handle -> SPI_Data_Store -> pRxBuffer) = (uint8_t)pSPI_Handle ->pSPIx-> SPI_DR;
		pSPI_Handle -> SPI_Data_Store -> Rxlen--;
		(uint8_t*)pSPI_Handle -> SPI_Data_Store -> pRxBuffer++;
	}

	if(!pSPI_Handle ->SPI_Data_Store -> Rxlen)
	{
		//Clear RXEIE bit
		pSPI_Handle -> pSPIx ->SPI_CR2 &= ~(1 << SPI_CR2_RXNEIE);

		pSPI_Handle -> SPI_Data_Store -> pRxBuffer = NULL;

		pSPI_Handle -> SPI_Data_Store -> Rxlen = 0;

		pSPI_Handle ->SPI_Data_Store -> RxState = SPI_READY;

		SPI_Appli_Event_CB(pSPI_Handle, SPI_EVENT_RX_COMP);
	}
}

static void SPI_IntrHandle_OVR(SPI_Handle *pSPI_Handle)
{
	uint8_t temp = 0;
	if(pSPI_Handle -> SPI_Data_Store -> TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPI_Handle -> pSPIx -> SPI_DR;
		temp = pSPI_Handle -> pSPIx -> SPI_SR;
	}
	(void)temp;
	SPI_Appli_Event_CB(pSPI_Handle, SPI_EVENT_RX_COMP);

}

void SPI_IRQPerio_Config(uint16_t IRQnumber,uint32_t IRQpriority);

void SPI_IRQHandle(SPI_Handle *pHandle)
{
	uint8_t temp1, temp2;
	temp1 = pHandle ->pSPIx -> SPI_SR & (1 << SPI_SR_TXE);
	temp2 = pHandle -> pSPIx -> SPI_CR2 & (1 << SPI_CR2_TXEIE);

	if(temp1 && temp2)
	{
		//Handle TXE Bit
		SPI_IntrHandle_TXE(pHandle);
	}

	// Check For RXE and RXENE bit
	temp1 = pHandle -> pSPIx -> SPI_SR & (1 << SPI_SR_RXNE);
	temp2 = pHandle -> pSPIx -> SPI_CR2 & (1 << SPI_CR2_RXNEIE);

	if(temp1 && temp2)
	{
		//Handle RXNEIE
		SPI_IntrHandle_RXNEIE(pHandle);
	}

	//Check for OVR Flag
	temp1 = pHandle -> pSPIx -> SPI_SR & (1 << SPI_SR_OVR);
	temp2 = pHandle -> pSPIx -> SPI_CR2 & (1 << SPI_CR2_ERRIE);

	if(temp1 && temp2)
	{
		//Handle ERRIE
		SPI_IntrHandle_OVR(pHandle);
	}

	/* Need to implement more IRQ handle by own later
	 * like CRC , master Mode Find error, TI frame format error
	 * */
}


/*Sent data and Received data in interrupt mode*/

uint8_t SPI_Data_SendIntr(SPI_Handle *pSPI_Handle ,uint8_t *TxBuffer  ,uint32_t Size)
{
	uint8_t state = pSPI_Handle -> SPI_Data_Store -> TxState;

	if(state != SPI_BUSY_IN_TX)
	{
		//1. Save TxBuffer and Size in Global Variable
		pSPI_Handle -> SPI_Data_Store -> pTxBuffer = TxBuffer;
		pSPI_Handle -> SPI_Data_Store -> TxLen = Size;

		//2 . Make SPI State Busy in Transmission so no other can disturb while transmission

		pSPI_Handle -> SPI_Data_Store -> TxState = SPI_BUSY_IN_TX;

		//3. Enable TXEIE Bit
		pSPI_Handle -> pSPIx->SPI_CR2 |= (1 << SPI_CR2_TXEIE);
	}
	return state;
}

uint8_t SPI_Data_ReceivedIntr(SPI_Handle *pSPI_Handle, uint8_t *RxBuffer  ,uint32_t Size)
{
	uint8_t state = pSPI_Handle-> SPI_Data_Store -> RxState;

	if(state != SPI_BUSY_IN_RX)
	{
		//1. Save RxBuffer and Size in some Global Variable
		pSPI_Handle -> SPI_Data_Store -> pRxBuffer = RxBuffer;
		pSPI_Handle -> SPI_Data_Store -> Rxlen = Size;

		//2. Make SPI Bus as Busy in Transmission
		pSPI_Handle ->SPI_Data_Store -> RxState = SPI_BUSY_IN_RX;

		//3. Enable RXNEIE
		pSPI_Handle -> pSPIx ->SPI_CR2 |= (1 << SPI_CR2_RXNEIE);
	}
	return state;
}



__attribute__((weak)) void SPI_Appli_Event_CB(SPI_Handle *pSPI_Handle, uint8_t SPI_EVENT_RX_COMP);

void SPI_Close_Transmit(SPI_Handle *pHandle)
{
	pHandle -> pSPIx ->SPI_CR2 &= ~(1 << SPI_CR2_TXEIE);

	pHandle -> SPI_Data_Store -> pTxBuffer = NULL;

	pHandle -> SPI_Data_Store -> TxLen = 0;

	pHandle ->SPI_Data_Store -> TxState = SPI_READY;
}
void SPI_Close_reception(SPI_Handle *pHandle)
{
	pHandle -> pSPIx ->SPI_CR2 &= ~(1 << SPI_CR2_RXNEIE);

	pHandle -> SPI_Data_Store -> pRxBuffer = NULL;

	pHandle -> SPI_Data_Store -> Rxlen = 0;

	pHandle ->SPI_Data_Store -> RxState = SPI_READY;

	SPI_Appli_Event_CB(pHandle, SPI_EVENT_RX_COMP);
}

void SPI_Clr_OVRF(SPI_Registers *pSPIx)
{
	uint8_t temp = 0;
	temp = pSPIx -> SPI_DR;
	temp = pSPIx -> SPI_SR;
	(void)temp;
}


