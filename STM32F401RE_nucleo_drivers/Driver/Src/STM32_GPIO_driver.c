
//Source file for GPIO drivers

#include "STM32_driver.h"


//GPIO function API to handle the task


//GPIO enable and disable control clock for peripherals
void GPIO_PClkControl(GPIO_RegDef_t *pGPIOx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE){
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_EN();
		}else if(pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
		}else if(pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
		}else if(pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
		}else if(pGPIOx == GPIOE){
			GPIOE_PCLK_EN();
		}else if(pGPIOx == GPIOH){
			GPIOH_PCLK_EN();
		}
	}
	if(ENorDI == DISABLE){
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_DI();
		}else if(pGPIOx == GPIOB){
			GPIOB_PCLK_DI();
		}else if(pGPIOx == GPIOC){
			GPIOC_PCLK_DI();
		}else if(pGPIOx == GPIOD){
			GPIOD_PCLK_DI();
		}else if(pGPIOx == GPIOE){
			GPIOE_PCLK_DI();
		}else if(pGPIOx == GPIOH){
			GPIOH_PCLK_DI();
		}
	}
}


//GPIO Initialization and Deinitialization


/*
@fn							- GPIO_Init

@brief 						- This function is to GPIO Initialization


@param[in]				   - base address of GPIOx
@param[in]
@param[in] 				   -

@return                    - none

@Note                      - none
*/


void GPIO_Init(GPIO_Handle_t *pGPIO_Handle)
{
	uint32_t temp = 0;

	//Configure the mode of GPIO pin
	if(pGPIO_Handle -> GPIO_PinConfig.GPIO_PinMode <= GPIO_AN_MODE)
	{
		//The Non Interrupt mode
		temp = (pGPIO_Handle -> GPIO_PinConfig.GPIO_PinMode << (2 * pGPIO_Handle -> GPIO_PinConfig.GPIO_PinNum));
		pGPIO_Handle -> pGPIO -> MODER &= ~(0x3 << (2 * pGPIO_Handle -> GPIO_PinConfig.GPIO_PinNum));
		pGPIO_Handle -> pGPIO -> MODER |= temp;
	}else{
		if(pGPIO_Handle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//1. Configure FTSR
			EXTI -> FTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum);
			//2. Clear RSTR
			EXTI -> RTSR &= ~(1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum);
		}else if(pGPIO_Handle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//1. configure RSTR
			EXTI -> RTSR |= (1 <<  pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum);
			//2. Clear FSTR
			EXTI -> FTSR &= ~(1 <<  pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum);
		}else if(pGPIO_Handle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//Configure both RSTR and FSTR
			EXTI -> RTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum);
			EXTI -> FTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum);
		}

		//2. Configure the GPIO port selection in SYSCFG_EXTICR
			uint8_t temp1 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum / 4;
			uint8_t temp2 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum % 4;
			uint8_t portcode = GPIOBASEADDR_TO_CODE(pGPIO_Handle -> pGPIO);
			SYSCFG_PCLK_EN();
			SYSCFG -> EXTICR[temp1] &= ~(0xF << (4 * temp2));
			SYSCFG -> EXTICR[temp1] |= (portcode << (4 * temp2));

		//3. Enable the EXTI interrupt delivery using IMR
			EXTI -> IMR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum);
		}

	temp = 0;

	//Configure the speed
	temp = (pGPIO_Handle -> GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum));
	pGPIO_Handle ->pGPIO->OSPEEDR &= ~(0x3 << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum));
	pGPIO_Handle -> pGPIO->OSPEEDR |= temp;

	temp = 0;

	//Configure the Pull-up / Pull-down setting

	temp = (pGPIO_Handle -> GPIO_PinConfig.GPIO_PLPD_Control << (2 * pGPIO_Handle -> GPIO_PinConfig.GPIO_PinNum));
	pGPIO_Handle -> pGPIO -> PUPDR &= ~(0x3 << (2 * pGPIO_Handle -> GPIO_PinConfig.GPIO_PinNum));
	pGPIO_Handle -> pGPIO -> PUPDR |= temp;

	temp = 0;

	//Configure output type register

	temp = (pGPIO_Handle -> GPIO_PinConfig.GPIO_PinOTY << (pGPIO_Handle -> GPIO_PinConfig.GPIO_PinNum));
	pGPIO_Handle ->pGPIO -> OTYPER &= ~(0x1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNum);
	pGPIO_Handle -> pGPIO -> OTYPER |= temp;

	temp = 0;

	//Configure alternate function

	if(pGPIO_Handle -> GPIO_PinConfig.GPIO_PinMode == GPIO_ALTFUN_MODE){
		uint8_t temp1 = pGPIO_Handle -> GPIO_PinConfig.GPIO_PinNum / 8;    //Checking for AFRL or AFRH
		uint8_t temp2 = pGPIO_Handle -> GPIO_PinConfig.GPIO_PinNum % 8;	   //Checking pin position
		if(temp1 == 0){
			pGPIO_Handle ->pGPIO->AFRL &= ~(0xF << (4 * temp2));
			pGPIO_Handle -> pGPIO->AFRL |= pGPIO_Handle -> GPIO_PinConfig.GPIO_AltFun << (4 * temp2);
		}
		if(temp1 == 1){
			pGPIO_Handle ->pGPIO-> AFRH &= ~(0xF << (4 * temp2));
			pGPIO_Handle -> pGPIO->AFRH |= pGPIO_Handle -> GPIO_PinConfig.GPIO_AltFun << (4 * temp2);
		}
	}

}


/*
@fn							- GPIO_DeInit

@brief 						- This function is to GPIO Deinitialization


@param[in]				   - base address of GPIOx
@param[in]
@param[in] 				   -

@return                    - none

@Note                      - none
*/


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA){
		GPIOA_RCC_RESET();
	}else if(pGPIOx == GPIOB){
		GPIOB_RCC_RESET();
	}else if(pGPIOx == GPIOC){
		GPIOC_RCC_RESET();
	}else if(pGPIOx == GPIOD){
		GPIOD_RCC_RESET();
	}else if(pGPIOx == GPIOE){
		GPIOE_RCC_RESET();
	}else if(pGPIOx == GPIOH){
		GPIOH_RCC_RESET();
	}
}



//Read/Write from GPIO

/*
@fn							- GPIO_PinRead

@brief 						- To take a input of pin


@param[in]				   - base address of GPIOx
@param[in]			       - Pin number
@param[in] 				   -

@return                    - 0 or 1

@Note                      - None
*/

uint8_t GPIO_PinRead(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number)
{
	 uint8_t value;
	 value = (uint8_t)((pGPIOx->IDR >> Pin_Number)  & 0x00000001);
	 return value;
}

uint16_t GPIO_PortRead(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR ;
	return value;
}
void GPIO_PinWrite(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number, uint8_t Value)
{
	if(Value == GPIO_SET)
	{
		//Write 1 if GPIO is set
		pGPIOx -> ODR |= (1 << Pin_Number);
	}else
	{
		//Write 0 if GPIO is not set
		pGPIOx -> ODR &= ~(1 << Pin_Number);
	}
}
void GPIO_PortWrite(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx -> ODR = Value;
}
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number)
{
	pGPIOx -> ODR ^= (1 << Pin_Number);
}


//GPIO Interrupt handling
void GPIO_IRQIntrConfig(uint16_t IRQnumber, uint8_t ENorDI)
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

void GPIO_IRQPrioConfig(uint16_t IRQnumber,uint32_t IRQpriority)
{
	uint8_t prix = IRQpriority / 4;
	uint8_t prix_section = IRQpriority % 4;
	uint8_t shift = (8 * prix_section) + (8 - 4);
	*(NVIC_PR_BASE_ADDR + prix ) |=  IRQpriority << shift;
}

void GPIO_IRQHandle(uint16_t Pinnumber)
{
	if(EXTI-> PR & (1 << Pinnumber))
	{
		//Clear by set the bit
		EXTI -> PR |= 1 << Pinnumber;
	}
}


