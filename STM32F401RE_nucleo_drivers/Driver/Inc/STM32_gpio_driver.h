/*This is for */
#ifndef INC_STM32_GPIO_DRIVER_H_
#define INC_STM32_GPIO_DRIVER_H_


#include "stm32f401re.h"

typedef struct
{
	uint8_t GPIO_PinNum;				/*GPIO pin number   < @GPIO PIN MODES > */
	uint8_t	GPIO_PinMode;				//GPIO pin mode
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinOTY;
	uint8_t GPIO_PLPD_Control;			//GPIO Pull-up And Pull-down control pin
	uint8_t GPIO_AltFun;

}GPIO_PeriConfig_t;

//To handle the GPIO

typedef struct
{
	GPIO_RegDef_t *pGPIO;                      //This holds the base address for GPIO which the port belong
	GPIO_PeriConfig_t GPIO_PinConfig;		   //This holds the GPIO pin setting
}GPIO_Handle_t;


//GPIO port mode register

typedef enum
{
	GPIO_IN_MODE,
	GPIO_OUT_MODE,
	GPIO_ALTFUN_MODE,
	GPIO_AN_MODE,
	GPIO_MODE_IT_FT,         //Interrupt on falling edge
	GPIO_MODE_IT_RT,		 //Interrupt on rising edge
	GPIO_MODE_IT_RFT		 //Interrupt on rising and falling edge
}GPIO_ModeReg_t;


//GPIO port output type register

typedef enum
{
	GPIO_OT_PP,                               //GPIO output push-pull
	GPIO_OT_OD                                //GPIO output open-drain
}GPIO_Oty_reg_t;



//GPIO port output speed register

typedef enum
{
	GPIO_LOW_SPEED,
	GPIO_MEDIUM_SPEED,
	GPIO_HIGH_SPEED,
	GPIO_VHIGH_SPEED
}GPIO_Ot_speed_reg_t;


//GPIO port pull-up / pull-down register

typedef enum
{
	GPIO_NOPUPD,
	GPIO_PU,
	GPIO_PD
}GPIO_PUPD_Reg_t;


//GPIO Alternate function register low and high

typedef enum
{
	AF0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}GPIO_AltrFun_Reg_t;


/* < @GPIO PIN MODES > */

typedef enum
{
	GPIO_PIN_NO_0,
	GPIO_PIN_NO_1,
	GPIO_PIN_NO_2,
	GPIO_PIN_NO_3,
	GPIO_PIN_NO_4,
	GPIO_PIN_NO_5,
	GPIO_PIN_NO_6,
	GPIO_PIN_NO_7,
	GPIO_PIN_NO_8,
	GPIO_PIN_NO_9,
	GPIO_PIN_NO_10,
	GPIO_PIN_NO_11,
	GPIO_PIN_NO_12,
	GPIO_PIN_NO_13,
	GPIO_PIN_NO_14,
	GPIO_PIN_NO_15,
}GPIO_PinNum_t;


/***********************************************************************************************************************/

//GPIO function API to handle the task
/*
@fn							- GPIO_PeriClkControl

@brief 						- This function enables or disables peripheral clock for the given GPIO port


@param[in]				   -
@param[in]
@param[in] 				   - base address of the gpio peripheral - ENABLE or DISABLE macros

@return                    - none

@Note                      - none
*/


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
		if(pGPIO_Handle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
			//1. Configure FTSR
			EXTI ->
		}else if(pGPIO_Handle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){

		}else if(pGPIO_Handle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT){

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

//GPIO Alternate function
void GPIO_Altfun(GPIO_RegDef_t *pGPIOx, uint8_t Pinnumber);

//GPIO Interrupt handling
void GPIO_IRQConfig(uint16_t IRQnumber,uint16_t IRQpriority, uint8_t ENorDI);
void GPIO_IRQHandle(uint16_t Pinnumber);










#endif /* INC_STM32_GPIO_DRIVER_H_ */
