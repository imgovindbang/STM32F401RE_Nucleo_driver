#include "STM32_driver.h"

//Functions for Peripheral clock enable for USART

#define APPEV 	0    //Need to change later

static void IntrDuetoTC(USART_Handle *pHandle)
{
	//Interrupt is cause by TC

	if(pHandle -> USART_Data.Tx_State == USART_BUSY_TX)
	{
		//check the TXLen if its zero then close transmission
		if(! pHandle -> USART_Data.TxLen)
		{
			//Clear TC flag
			pHandle -> pUSART -> USART_SR &= ~(1 << USART_SR_TC);

			//Clear TCIE control bit
			pHandle -> pUSART -> USART_CR1 &= ~(1 << USART_CR1_TCIE);

			//Reset the application state
			pHandle -> USART_Data.Tx_State = USART_READY;

			//Buffer address to NULL
			pHandle -> USART_Data.pTxBuffer = NULL;

			//Length to zero
			pHandle -> USART_Data.TxLen = 0;

			USART_ApplicationEventCallback(pHandle, APPEV); // need to correct later
		}
	}
}

static void IntrDueToTXE(USART_Handle *pHandle)
{
	uint16_t *pData;
	//Interrupt due to TXE
	if(pHandle -> USART_Data.Tx_State == USART_BUSY_TX)
	{
		//Keep sending data until TXlen become zero
		if(pHandle -> USART_Data.TxLen > 0)
		{
			//Check the frame is 8bit or 9bit
			if(pHandle -> USART_Config.USART_WordLength == USART_9BIT)
			{
				pData = ((uint16_t*)pHandle -> USART_Data.pTxBuffer);

				//Mask the data so only 9 bit can use
				*(pHandle -> USART_Data.pTxBuffer) = (*pData & (uint16_t)0x01FF);

				//Check for Parity control
				if(pHandle -> USART_Config.USART_ParityControl == DISABLE_PARITY)
				{
					//no parity is used
					pHandle -> USART_Data.pTxBuffer++;
					pHandle -> USART_Data.pTxBuffer++;

					//decrement the length
					pHandle -> USART_Data.TxLen--; //Re check this later
				}else
				{
					//parity bit is used so 8 bit is transfered and 9th bit is replace to parity bit by hardware
					pHandle -> USART_Data.pTxBuffer++;

					//decrement the length
					pHandle -> USART_Data.TxLen--;
				}

			}else
			{
				//8 bit data is transfer
				(pHandle -> pUSART -> USART_DR) = (*pData & (uint8_t)0xFF); //checkout later

				//Increment buffer address
				pHandle -> USART_Data.pTxBuffer++;

				//decrease length
				pHandle -> USART_Data.TxLen--;
			}
		}
	}
	if(pHandle -> USART_Data.TxLen == 0)
	{
		//TX Length is zero
		//Disable TXEIE bit
		pHandle -> pUSART -> USART_CR1 &= ~(1 << USART_CR1_TXEIE);
}

}

static void InrtDueToRXNE(USART_Handle *pHandle)
{
	//This interrupt is because of RXNE

	if(pHandle -> USART_Data.Rx_State == USART_BUSY_RX)
	{
		//TXE is set so send data
		if(pHandle -> USART_Data.RxLen > 0)
		{
			//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
			if(pHandle -> USART_Config.USART_WordLength == USART_9BIT)
			{
				//We are going to receive 9bit data in a frame

				//Now, check are we using USART_ParityControl control or not
				if(pHandle -> USART_Config.USART_ParityControl == DISABLE_PARITY)
				{
					//No parity is used. so, all 9bits will be of user data

					//read only first 9 bits so mask the DR with 0x01FF
					*((uint16_t*) pHandle -> USART_Data.pRxBuffer) = (pHandle -> pUSART -> USART_DR  & (uint16_t)0x01FF);

					//Increment the pRxBuffer two times
					pHandle -> USART_Data.pRxBuffer++;
					pHandle -> USART_Data.pRxBuffer++;

					//decrement the length
					pHandle -> USART_Data.RxLen--;
				}
				else
				{
					//Parity is used. so, 8bits will be of user data and 1 bit is parity
					 *(pHandle -> USART_Data.pRxBuffer) = (pHandle -> pUSART -> USART_DR  & (uint8_t)0xFF);

					 //Increment the pRxBuffer
					 pHandle -> USART_Data.pRxBuffer++;

					 //decrement the length
					 pHandle -> USART_Data.RxLen--;
				}
			}
			else
			{
				//We are going to receive 8bit data in a frame

				//Now, check are we using USART_ParityControl control or not
				if(pHandle -> USART_Config.USART_ParityControl == DISABLE_PARITY)
				{
					//No parity is used , so all 8bits will be of user data

					//read 8 bits from DR
					 *(pHandle -> USART_Data.pRxBuffer) = (uint8_t) (pHandle -> pUSART -> USART_DR & (uint8_t)0xFF);
				}
				else
				{
					//Parity is used, so , 7 bits will be of user data and 1 bit is parity

					//read only 7 bits , hence mask the DR with 0X7F
					 *(pHandle -> USART_Data.pRxBuffer) = (uint8_t) (pHandle -> pUSART -> USART_DR  & (uint8_t)0x7F);

				}

				//Increment the pRxBuffer
				pHandle -> USART_Data.pRxBuffer++;

				//Decrement the length
				pHandle -> USART_Data.RxLen--;
			}


		}//if of > 0

		if(! pHandle -> USART_Data.RxLen)
		{
			//Disable the rxne
			pHandle -> pUSART -> USART_CR1 &= ~( 1 << USART_CR1_RXNEIE);
			pHandle -> USART_Data.Rx_State = USART_READY;
			USART_ApplicationEventCallback(pHandle,APPEV);
		}
	}
}

void ClearOREFlag(USART_Handle *pHandle)
{
	uint32_t dummyread = pHandle -> pUSART -> USART_SR;
	dummyread = pHandle -> pUSART -> USART_DR;
	(void)dummyread;
}

void USART_Peri_Clk_Enable(USART_Registers *pUSART)
{
	if(pUSART == USART1)
	{
		USART1_PCLK_EN();
	}else if(pUSART == USART2)
	{
		USART2_PCLK_EN();
	}else if(pUSART == USART6)
	{
		USART6_PCLK_EN();
	}
}

void USART_Peri_Clk_Disable(USART_Registers *pUSART)
{
	if(pUSART == USART1)
		{
			USART1_PCLK_DI();
		}else if(pUSART == USART2)
		{
			USART2_PCLK_DI();
		}else if(pUSART == USART6)
		{
			USART6_PCLK_DI();
		}
}

//USART Initialization API
void USART_Init(USART_Handle *pHandle)
{
	uint8_t temp = 0;

	//Enable the USART peripheral clock
	USART_Peri_Clk_Enable(pHandle -> pUSART);

	//Configuring CR1 Register

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	if(pHandle -> USART_Config.USART_Mode == USART_RX)
	{
		//Enable Receive bit
		temp |= (1 << USART_CR1_RE);
	}else if(pHandle -> USART_Config.USART_Mode == USART_TX)
	{
		//Enable transmit bit
		temp |= (1 << USART_CR1_TE);
	}else if(pHandle -> USART_Config.USART_Mode == USART_TXRX)
	{
		//Enable both transmission and reception
		temp |= (1 << USART_CR1_RE);
		temp |= (1 << USART_CR1_TE);
	}

	//Configure the Word length
	temp |= pHandle -> USART_Config.USART_WordLength << USART_CR1_M;

	//Configure Parity
	if(pHandle -> USART_Config.USART_ParityControl == EVEN_PARITY)
	{
		//Enable the parity control
		temp |= (1 << USART_CR1_PCE);

		//no need to code for even parity bit because it selected by default
	}else if(pHandle -> USART_Config.USART_ParityControl == ODD_PARITY)
	{
		//Enable the parity control
		temp |= (1 << USART_CR1_PCE);

		//Code for odd parity enable
		temp |= (1 << USART_CR1_PS);

	}

	pHandle -> pUSART -> USART_CR1 = temp;

	//Configuring CR2 Register

	temp = 0;

	//Code for number of stop bit for USART transmission

	temp |= pHandle -> USART_Config.USART_StopBits << USART_CR2_STOP;

	pHandle -> pUSART -> USART_CR2 = temp;


	//Configuring CR3

	temp = 0;

	if ( pHandle -> USART_Config.USART_HWFlowControl == USART_CTSE)
		{
			//Code to enable CTS flow control
			temp |= ( 1 << USART_CR3_CTSE);


		}else if (pHandle -> USART_Config.USART_HWFlowControl == USART_RTSE)
		{
			//Code to enable RTS flow control
			temp |= (1 << USART_CR3_RTSE);

		}else if (pHandle -> USART_Config.USART_HWFlowControl == USART_CTSE_RTSE)
		{
			//Code to enable both CTS and RTS Flow control
			temp |= ((1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE));
		}

	pHandle -> pUSART -> USART_CR3 = temp;

	//Calculation for BRR
	USART_BaudRate(pHandle -> pUSART, pHandle -> USART_Config.USART_Baudrate);
}

//USART DeInitialization API
void USART_DeInit(USART_Registers *pUSART)
{
	if(pUSART == USART1)
	{
		USART1_RCC_RESET();
	}else if(pUSART == USART2)
	{
		USART2_RCC_RESET();
	}else if(pUSART == USART6)
	{
		USART6_RCC_RESET();
	}
}

//USART Send data API
void USART_SendData(USART_Handle *pHandle, uint8_t *pTxBuffer, uint32_t Length)
{
	uint16_t *pData;

	for(uint32_t i = 0; i < Length; i++)
	{
		//Code to wait until TXE flag is set in the SR regsiter
		while(! USART_GetFlagStatus(pHandle -> pUSART, USART_SR_TXE));

		//Check the USART word length is * bit or 9 bit
		if(pHandle -> USART_Config.USART_WordLength == USART_9BIT)
		{
			//If data is 9-bit then we need to mask the value into 9 bit
			pData = (uint16_t*)pTxBuffer;
			pHandle -> pUSART -> USART_DR = (*pData & (uint16_t)0x01FF);

			if(pHandle -> USART_Config.USART_ParityControl == DISABLE_PARITY)
			{
				//No parity is used in this so 9 bit is transfer
				pTxBuffer++;
				pTxBuffer++;
			}else
			{
				//Parity is used in this , so 9th bit is replaced by the parity bit by hardware
				pTxBuffer++;
			}
		}else
		{
			//8 bit data transfer
			pHandle -> pUSART -> USART_DR = (*pData & (uint16_t)0xFF);

			pTxBuffer++;
		}
	}

	//Wait till TC (Transmission complete) flag is set in SR register
	while(! USART_GetFlagStatus(pHandle -> pUSART, USART_SR_TC));
}


//USART Receive data API
void USART_ReceiveData(USART_Handle *pHandle, uint8_t *pRxBuffer, uint32_t Length)
{
	for(uint32_t i = 0; i < Length; i++)
	{
		//Wait till RXNE flag set in SR register
		while(! USART_GetFlagStatus(pHandle -> pUSART, USART_SR_RXNE));

		//Check for the if the word length is 9 Bit or 8 Bit
		if(pHandle -> USART_Config.USART_WordLength == USART_9BIT)
		{
			//Receive 9 Bit data

			if(pHandle -> USART_Config.USART_ParityControl == DISABLE_PARITY)
			{
				//No parity is used in this, so send 9 bit

				*((uint16_t*)pRxBuffer) = pHandle -> pUSART -> USART_DR & (uint16_t)0x1FF;

				pRxBuffer++;
				pRxBuffer++;
			}else
			{
				//parity is used in this , so 8 bit data and 1 bit is for parity

				*pRxBuffer = pHandle -> pUSART -> USART_DR & (uint16_t)0xFF;

				pRxBuffer++;
			}

		}else
		{
			//8 Bit data
			if(pHandle -> USART_Config.USART_ParityControl == DISABLE_PARITY)
			{
				//No parity is used in this, so all 8 bit is send to data
				*pRxBuffer = pHandle -> pUSART -> USART_DR;

			}else
			{
				//Here parity bit is enable so 7 bit data is receive
				*pRxBuffer = pHandle -> pUSART -> USART_DR & (uint8_t)0x7F;
			}

			pRxBuffer++;
		}

	}
}

//Send and Receive data in interrupt mode
uint8_t USART_SendDataIT(USART_Handle *pHandle,uint8_t *pTxBuffer, uint32_t Length)
{
	uint8_t txState = pHandle -> USART_Data.Tx_State;

	if(txState != USART_BUSY_TX)
	{
		pHandle -> USART_Data.TxLen = Length;
		pHandle -> USART_Data.pTxBuffer = pTxBuffer;
		pHandle -> USART_Data.Tx_State = USART_BUSY_TX;


		//Enable the TXE
		pHandle -> pUSART -> USART_SR |= (1 << USART_SR_TXE);

		//Enable the TC
		pHandle -> pUSART -> USART_SR |= (1 << USART_SR_TC);
	}
	return txState;
}
uint8_t USART_ReceiveDataIT(USART_Handle *pHandle, uint8_t *pRxBuffer, uint32_t Length)
{
	uint8_t rxState = pHandle -> USART_Data.Rx_State;

	if(rxState != USART_BUSY_RX)
	{
		pHandle -> USART_Data.RxLen = Length;
		pHandle -> USART_Data.pRxBuffer = pRxBuffer;
		pHandle -> USART_Data.Rx_State = USART_BUSY_RX;

		//Enable RXNE
		pHandle -> pUSART -> USART_SR |= (1 << USART_SR_RXNE);
	}
	return rxState;
}

void USART_BaudRate(USART_Registers *pUSART, uint32_t Baudrate)
{
	uint32_t PCLK;
	uint32_t USART_div;

	uint32_t mentissa;
	uint32_t fraction;

	uint32_t temp = 0;

	//Select the proper RCC clock according to the USARTx
	if(pUSART == USART1 || pUSART == USART6)
	{
		PCLK = RCC_PCLK1Value();
	}else
	{
		PCLK = RCC_PCLK2Value();
	}

	//Checking OVR8
	if(pUSART -> USART_CR1 & (1 << USART_CR1_OVER8))
	{
		//OVR8 = 1, so the sampling is 8
		USART_div = ((25 * PCLK) / (2 * Baudrate));
	}else
	{
		//OVR8 = 0, so sampling id 16
		USART_div = ((25 * PCLK) / (4 * Baudrate));
	}

	mentissa = USART_div / 100;

	temp |= mentissa;

	fraction = (USART_div - (USART_div * 100));

	if(pUSART -> USART_CR1 & (1 << USART_CR1_OVER8))
	{
		//OVR8 = 1, so over sampling at 8
		fraction = ((( fraction * 8)+ 50) / 100)& ((uint8_t)0x07);
	}else
	{
		//over sampling at 16
		fraction = ((( fraction * 16)+ 50) / 100) & ((uint8_t)0x0F);
	}

	temp |= fraction;

	pUSART -> USART_BRR = temp;
}

//IRQ Configuration and ISR handling
void USART_IRQInterrupt_Enable(uint8_t IRQNumber)
{
		if(IRQNumber < 32)
		{
			//Set ISER0(Interrupt Set-enable Registers)
			*NVIC_ISER0 |= (1U << IRQNumber);
		}else  if(IRQNumber >= 32 && IRQNumber < 64)
		{
			//Set ISER1(Interrupt Set-enable Registers)
			*NVIC_ISER1 |= (1U << IRQNumber % 32);
		}else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			//Set ISER2(Interrupt Set-enable Registers)
			*NVIC_ISER2 |= (1U << IRQNumber % 32);
		}
}

void USART_IRQInterrupt_Disable(uint8_t IRQNumber){
	if(IRQNumber < 32)
		{
			//Clear ICER0(Interrupt Clear-enable Registers)
			*NVIC_ICER0 |= (1U << IRQNumber);
		}else  if(IRQNumber >= 32 && IRQNumber < 64)
		{
			//Clear ICER1(Interrupt Clear-enable Registers)
			*NVIC_ICER1 |= (1U << IRQNumber % 32);
		}else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			//Clear ICER2(Interrupt Clear-enable Registers)
			*NVIC_ICER2 |= (1U << IRQNumber % 32);
		}
}

void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	uint8_t prix = IRQPriority / 4;
	uint8_t prix_section = IRQPriority % 4;
	uint8_t shift = (8 * prix_section) + (8 - 4);
	*(NVIC_PR_BASE_ADDR + prix ) |=  IRQPriority << shift;
}



void USART_IRQHandling(USART_Handle *pHandle)
{
	uint32_t temp1, temp2, temp3;

	//Check for TC bit in SR register
	temp1 = pHandle -> pUSART -> USART_SR & (1 << USART_SR_TC);

	//check for TCEIE bit
	temp2 = pHandle -> pUSART -> USART_SR & (1 << USART_CR1_TCIE);

	if(temp1 && temp2)
	{
		//Interrupt due to TC flag and TCIE
		IntrDuetoTC(pHandle);
	}


	//Check for TXE flag

	//check for TXE bit in SR register
	temp1 = pHandle -> pUSART -> USART_SR & (1 << USART_SR_TXE);

	//Check for TXEIE bit
	temp2 = pHandle -> pUSART -> USART_CR1 & (1 << USART_CR1_TXEIE);

	if(temp1 && temp2)
	{
		//Interrupt due to TC flag and TCIE
		IntrDueToTXE(pHandle);
	}


	//Check for RXNE flag

	temp1 = pHandle -> pUSART -> USART_SR & (1 << USART_SR_RXNE);

	temp2 = pHandle -> pUSART -> USART_CR1 & (1 << USART_CR1_RXNEIE);

	if(temp1 && temp2)
	{
		InrtDueToRXNE(pHandle);
	}

	//Check the status of CTS bit in the SR
	temp1 = pHandle -> pUSART -> USART_SR & (1 << USART_SR_CTS);

	//Check the state of CTSE bit in CR3
	temp2 = pHandle -> pUSART -> USART_CR3 & ( 1 << USART_CR3_CTSE);

	//Check the state of CTSIE bit in CR3
	temp3 = pHandle -> pUSART -> USART_CR3 & ( 1 << USART_CR3_CTSIE);


	//Check for CTS flag

	if(temp1  && temp2 )
	{
		//Clear the CTS flag in SR
		pHandle -> pUSART -> USART_SR &= ~(1 << USART_SR_CTS);

		//Interrupt is because of CTS
		USART_ApplicationEventCallback(pHandle,APPEV);
	}

	//Check for IDLE flag

	//Check the status of IDLE flag bit in the SR
	temp1 = pHandle -> pUSART -> USART_SR & (1 << USART_SR_IDLE);

	//Check the state of IDLEIE bit in CR1
	temp2 = pHandle -> pUSART -> USART_CR1 & ( 1 << USART_CR1_IDLEIE);


	if(temp1 && temp2)
	{
		//Clear the IDLE flag
		pHandle -> pUSART -> USART_SR &= ~(1 << USART_SR_IDLE);

		//Interrupt is because of IDLE
		USART_ApplicationEventCallback(pHandle,APPEV);
	}

	//Check Overrun flag

	//Check the status of ORE flag  in the SR
	temp1 = pHandle -> pUSART -> USART_SR & (1 << USART_SR_ORE);

	//Check the status of RXNEIE  bit in the CR1
	temp2 = pHandle-> pUSART-> USART_CR1 & (1 << USART_CR1_RXNEIE);


	if(temp1  && temp2 )
	{
		//Clear the ORE flag
		ClearOREFlag(pHandle);
		//this interrupt is because of Overrun error
		USART_ApplicationEventCallback(pHandle,APPEV);
	}

	//Check for Error flag

	//Noise Flag, Overrun error and Framing Error in multibuffer communication

	temp2 =  pHandle -> pUSART-> USART_CR3 & ( 1 << USART_CR3_EIE) ;

	if(temp2 )
	{
		temp1 = pHandle -> pUSART-> USART_SR;
		if(temp1 & ( 1 << USART_SR_FE))
		{
			/*
				This bit is set by hardware when a de-synchronization, excessive noise or a break character
				is detected. It is cleared by a software sequence (an read to the USART_SR register
				followed by a read to the USART_DR register).
			*/
			ClearOREFlag(pHandle);
			USART_ApplicationEventCallback(pHandle,APPEV);
		}

		if(temp1 & ( 1 << USART_SR_NF) )
		{
			/*
				This bit is set by hardware when noise is detected on a received frame. It is cleared by a
				software sequence (an read to the USART_SR register followed by a read to the
				USART_DR register).
			*/
			ClearOREFlag(pHandle);
			USART_ApplicationEventCallback(pHandle,APPEV);
		}

		if(temp1 & ( 1 << USART_SR_ORE) )
		{
			USART_ApplicationEventCallback(pHandle,APPEV);
		}
	}
}


//Supporting APIs to control peripheral
void USART_Enable(USART_Registers *pUSART)
{
	pUSART -> USART_CR1 |= (1 << USART_CR1_UE);
}

void USART_Disable(USART_Registers *pUSART)
{
	pUSART -> USART_CR1 &= ~(1 << USART_CR1_UE);
}

uint8_t USART_GetFlagStatus(USART_Registers *pUSART , uint32_t FlagName)
{
	if(pUSART -> USART_SR &  FlagName)
	{
		return FLAG_SET;
	}else
	{
		return FLAG_RESET;
	}
}


//Application callback
__attribute__((weak)) void USART_ApplicationEventCallback(USART_Handle *pHandle,uint8_t AppEv);

