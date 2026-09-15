/*This is for */
#ifndef INC_STM32_GPIO_DRIVER_H_
#define INC_STM32_GPIO_DRIVER_H_


#include "STM32_driver.h"


//GPIO to IRQ code
#define GPIOBASEADDR_TO_CODE(x)  \
											((x == GPIOA) ? 0 : \
											 (x == GPIOB) ? 1 : \
											 (x == GPIOC) ? 2 : \
											 (x == GPIOD) ? 3 : \
											 (x == GPIOE) ? 4 : \
											 (x == GPIOH) ? 7 : 0)

typedef struct
{
	uint8_t GPIO_PinNum;				/*GPIO pin number   < @GPIO PIN MODES > */
	uint8_t	GPIO_PinMode;				//GPIO pin mode
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinOTY;
	uint8_t GPIO_PLPD_Control;			//GPIO Pull-up And Pull-down control pin
	uint8_t GPIO_AltFun;

}GPIO_PeriConfig;

//To handle the GPIO

typedef struct
{
	GPIO_Registers *pGPIO;                      //This holds the base address for GPIO which the port belong
	GPIO_PeriConfig GPIO_PinConfig;		   //This holds the GPIO pin setting
}GPIO_Handle;


//GPIO port mode register

enum
{
	GPIO_IN_MODE,
	GPIO_OUT_MODE,
	GPIO_ALTFUN_MODE,
	GPIO_AN_MODE,
	GPIO_MODE_IT_FT,         //Interrupt on falling edge
	GPIO_MODE_IT_RT,		 //Interrupt on rising edge
	GPIO_MODE_IT_RFT		 //Interrupt on rising and falling edge
};


//GPIO port output type register

enum
{
	GPIO_OT_PP,                               //GPIO output push-pull
	GPIO_OT_OD                                //GPIO output open-drain
};



//GPIO port output speed register

enum
{
	GPIO_LOW_SPEED,
	GPIO_MEDIUM_SPEED,
	GPIO_HIGH_SPEED,
	GPIO_VHIGH_SPEED
};


//GPIO port pull-up / pull-down register

enum
{
	GPIO_NOPUPD,
	GPIO_PU,
	GPIO_PD
};


//GPIO Alternate function register low and high
enum
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
};


/* < @GPIO PIN MODES > */

enum
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
};


/***********************************************************************************************************************
 * 										APIs for GPIOS driver																					   *
**********************************************************************************************************************/

//GPIO function API to handle the task


//GPIO enable and disable control clock for peripherals
void GPIO_PeriClockControl(GPIO_Registers *pGPIOx, uint8_t ENorDI);

//GPIO Initialization and Deinitialization



void GPIO_Init(GPIO_Handle *pGPIO_Handle);


void GPIO_DeInit(GPIO_Registers *pGPIOx);





uint8_t GPIO_PinRead(GPIO_Registers *pGPIOx, uint8_t Pin_Number);

uint16_t GPIO_PortRead(GPIO_Registers *pGPIOx);
void GPIO_PinWrite(GPIO_Registers *pGPIOx, uint8_t Pin_Number, uint8_t Value);
void GPIO_PortWrite(GPIO_Registers *pGPIOx, uint16_t Value);
void GPIO_TogglePin(GPIO_Registers *pGPIOx, uint8_t Pin_Number);

//GPIO Alternate function
void GPIO_Altfun(GPIO_Registers *pGPIOx, uint8_t Pinnumber);

//GPIO Interrupt handling
void GPIO_IRQConfig(uint16_t IRQnumber,uint16_t IRQpriority, uint8_t ENorDI);
void GPIO_IRQHandle(uint16_t Pinnumber);










#endif /* INC_STM32_GPIO_DRIVER_H_ */
