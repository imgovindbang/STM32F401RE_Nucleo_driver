/*This is a general STM32F401RE_Nucleo driver*/

#ifndef INC_STM32_DRIVER_H_
#define INC_STM32_DRIVER_H_

#include<stdint.h>

/*Addresses for memory*/

#define FLASD_BASEADDR 				0x08000000U 				/*This is the base address for flash memory*/
#define SRAM1_BASEADDR 				0x20000000U					/*This is the base address for SRAM1 memory*/
#define ROM_BASEADDR				0x1FFF0000U					/*This is the base address for system memory(ROM)*/
#define SRAM						SRAM1_BASEADDR

/*
base address of peripherals and buses
 */

#define PERIPH_BASEADDR 			0x40000000U
#define APB1_BASEADDR				PERIPH_BASEADDR
#define APB2_BASEADDR 				0x40010000U
#define AHB1_BASEADDR				0x40020000U
#define AHB2_BASEADDR				0x50000000U

/*
Defining each peripheral base address of ABH1 bus
*/

#define GPIOA_BASEADDR 				(AHB1_BASEADDR + 0x0000)
#define GPIOB_BASEADDR				(AHB1_BASEADDR + 0x0400)
#define GPIOC_BASEADDR				(AHB1_BASEADDR + 0x0800)
#define GPIOD_BASEADDR 				(AHB1_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR				(AHB1_BASEADDR + 0x1000)
#define GPIOH_BASEADDR				(AHB1_BASEADDR + 0x1C00)
#define CRC_BASEADDR				(AHB1_BASEADDR + 0x3000)
#define RCC_BASEADDR 				(AHB1_BASEADDR + 0x3800)
#define FLASH_INTRREG_BASEADDR 		(AHB1_BASEADDR + 0x3C00)
#define DMA1_BASEADDR 				(AHB1_BASEADDR + 0x6000)
#define DMA2_BASEADDR 				(AHB1_BASEADDR + 0x6400)


/*Base addresses of peripherals of bus ABH2*/

#define USB_OTG_FS_BASEADDR 		(AHB2_BASEADDR + 0x0000)

/*Base address of peripherals of bus APB2*/

#define TIM1_BASEADDR 				(APB2_BASEADDR + 0x0000)
#define TIM9_BASEADDR 				(APB2_BASEADDR + 0x4000)
#define TIM10_BASEADDR 				(APB2_BASEADDR + 0x4400)
#define TIM11_BASEADDR 				(APB2_BASEADDR + 0x4800)

#define USART1_BASEADDR 			(APB2_BASEADDR + 0x1000)
#define USART6_BASEADDR 			(APB2_BASEADDR + 0x1400)

#define ADC1_BASEADDR 				(APB2_BASEADDR + 0x2000)
#define SDIO_BASEADDR 				(APB2_BASEADDR + 0x2C00)

#define SPI1_BASEADDR 				(APB2_BASEADDR + 0x3000)
#define SPI4_BASEADDR 				(APB2_BASEADDR + 0x3400)

#define SYSCFG_BASEADDR 			(APB2_BASEADDR + 0x3800)

#define EXTI_BASEADDR 				(APB2_BASEADDR + 0x3C00)

/*Base address of peripherals of bus APB1*/

#define TIM2_BASEADDR 				(APB1_BASEADDR + 0x0000)
#define TIM3_BASEADDR 				(APB1_BASEADDR + 0x0400)
#define TIM4_BASEADDR 				(APB1_BASEADDR + 0x0800)
#define TIM5_BASEADDR 				(APB1_BASEADDR + 0x0C00)

#define RTC_BKP_BASEADDR 			(APB1_BASEADDR + 0x2800)

#define WWDG_BASEADDR 				(APB1_BASEADDR + 0x2C00)
#define IWDG_BASEADDR 				(APB1_BASEADDR + 0x3000)

#define I2S2EXT_BASEADDR 			(APB1_BASEADDR + 0x3400)
#define I2S3EXT_BASEADDR 			(APB1_BASEADDR + 0x4000)

#define SPI2_I2S2_BASEADDR 			(APB1_BASEADDR + 0x3800)
#define SPI3_I2S3_BASEADDR 			(APB1_BASEADDR + 0x3C00)

#define USART2_BASEADDR 			(APB1_BASEADDR + 0x4400)

#define I2C1_BASEADDR 			    (APB1_BASEADDR + 0x5400)
#define I2C2_BASEADDR 			    (APB1_BASEADDR + 0x5800)
#define I2C3_BASEADDR 			    (APB1_BASEADDR + 0x5C00)

#define PWR_BASEADDR 			    (APB1_BASEADDR + 0x7000)

/********************************************************************************************************/

/* GPIO registers configuration */


typedef struct
{
	volatile uint32_t MODER;    		//GPIO port mode register   				  //Address offset : 0x00
	volatile uint32_t OTYPER;			//GPIO port output type register			  //Address offset : 0x04
	volatile uint32_t OSPEEDR;			//GPIO port output speed register	 		  //Address offset : 0x08
	volatile uint32_t PUPDR;			//GPIO port pull-up / pull-down register	  //Address offset : 0x0C
	volatile uint32_t IDR;				//GPIO port input data register			 	  //Address offset : 0x10
	volatile uint32_t ODR;				//GPIO port output data register 			  //Address offset : 0x14
	volatile uint32_t BSRR;				//GPIO port bit set/reset register 			  //Address offset : 0x18
	volatile uint32_t LCKR;				//GPIO port configuration clock register 	  //Address offset : 0x1C
	volatile uint32_t AFRL;				//GPIO port Alternate function low register   //Address offset : 0x20
	volatile uint32_t AFRH;				//GPIO port Alternate function high register  //Address offset : 0x24
}GPIO_RegDef_t;

#define GPIOA 		((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB 		((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC 		((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD 		((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE 		((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH 		((GPIO_RegDef_t*)GPIOH_BASEADDR)



typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;                       //change RCC only prefer the name like CR and CFGR
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t RESERVED0;
	volatile uint32_t RESERVED1;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVED2;
	volatile uint32_t RESERVED3;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t RESERVED4;
	volatile uint32_t RESERVED5;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVED6;
	volatile uint32_t RESERVED7;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t RESERVED8;
	volatile uint32_t RESERVED9;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED10;
	volatile uint32_t RESERVED11;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED12;
	volatile uint32_t RESERVED13;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t RESERVED14;
	volatile uint32_t DCKCFGR;
}RCC_RegDef_t;


typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RSTR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef_t;

/*Define RCC base address*/

#define RCC 	((RCC_RegDef_t*)RCC_BASEADDR)

/*Define EXTI base address*/

#define EXTI 	((EXTI_RegDef_t*)EXTI_BASEADDR)


//Clock enable macros for GPIOx peripherals

#define GPIOA_PCLK_EN() 				(RCC -> AHB1ENR |= (1U << 0))
#define GPIOB_PCLK_EN()				    (RCC -> AHB1ENR |= (1U << 1))
#define GPIOC_PCLK_EN()	     			(RCC -> AHB1ENR |= (1U << 2))
#define GPIOD_PCLK_EN()					(RCC -> AHB1ENR |= (1U << 3))
#define GPIOE_PCLK_EN()					(RCC -> AHB1ENR |= (1U << 4))
#define GPIOH_PCLK_EN()					(RCC -> AHB1ENR |= (1U << 7))


//Clock Enable macros for  I2Cx peripherals

#define I2C1_PCLK_EN() 				   (RCC -> APB1ENR |= (1U << 21))
#define I2C2_PCLK_EN()				   (RCC -> APB1ENR |= (1U << 22))
#define I2C3_PCLK_EN()				   (RCC -> APB1ENR |= (1U << 23))


//Clock enable macros for SPIx peripherals

#define SPI1_PCLK_EN()				  (RCC -> APB2ENR |= (1U << 12))
#define SPI4_PCLK_EN()				  (RCC -> APB2ENR |= (1U << 13))
#define SPI2_PCLK_EN()				  (RCC -> APB1ENR |= (1U << 14))
#define SPI3_PCLK_EN()				  (RCC -> APB1ENR |= (1U << 15))

//Clock enable macros for USARTx peripherals

#define USART1_PCLK_EN()				(RCC -> APB2ENR |= (1U << 4))
#define USART6_PCLK_EN() 				(RCC -> APB2ENR |= (1U << 5))
#define USART2_PCLK_EN() 				(RCC -> APB1ENR |= (1U << 17))


//CLock enable macros for SYSCFG peripheral

#define SYSCFG_PCLK_EN()				(RCC -> APB2ENR |= (1U << 14))


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//Clock Disable macros for GPIOx peripheral

#define GPIOA_PCLK_DI() 				(RCC -> AHB1ENR &= ~(1U << 0))
#define GPIOB_PCLK_DI()				    (RCC -> AHB1ENR &= ~(1U << 1))
#define GPIOC_PCLK_DI()	     			(RCC -> AHB1ENR &= ~(1U << 2))
#define GPIOD_PCLK_DI()					(RCC -> AHB1ENR &= ~(1U << 3))
#define GPIOE_PCLK_DI()					(RCC -> AHB1ENR &= ~(1U << 4))
#define GPIOH_PCLK_DI()					(RCC -> AHB1ENR &= ~(1U << 7))



//Clock disable macros for I2Cx peripheral

#define I2C1_PCLK_DI() 				   (RCC -> APB1ENR &= ~(1U << 21))
#define I2C2_PCLK_DI()				   (RCC -> APB1ENR &= ~(1U << 22))
#define I2C3_PCLK_DI()				   (RCC -> APB1ENR &= ~(1U << 23))

//Clock disable macros for SPIx peripheral

#define SPI1_PCLK_DI()				  (RCC -> APB2ENR &= ~(1U << 12))
#define SPI4_PCLK_DI()				  (RCC -> APB2ENR &= ~(1U << 13))
#define SPI2_PCLK_DI()				  (RCC -> APB1ENR &= ~(1U << 14))
#define SPI3_PCLK_DI()				  (RCC -> APB1ENR &= ~(1U << 15))


//Clock disable macros for USARTx peripheral

#define USART1_PCLK_DI()				(RCC -> APB2ENR &= ~(1U << 4))
#define USART6_PCLK_DI() 				(RCC -> APB2ENR &= ~(1U << 5))
#define USART2_PCLK_DI() 				(RCC -> APB1ENR &= ~(1U << 17))


//CLock disable macros for SYSCFG peripheral

#define SYSCFG_PCLK_DI()				(RCC -> APB2ENR &= ~(1U << 14))


/*Macros to reset GPIOx Peripherals   */

#define GPIOA_RCC_RESET()				do {(RCC -> AHB1RSTR |=  (1U << 0)) ; (RCC -> AHB1RSTR &= ~(1U << 0)) ; }while(0)
#define GPIOB_RCC_RESET()				do {(RCC -> AHB1RSTR |=  (1U << 1)) ; (RCC -> AHB1RSTR &= ~(1U << 1)) ; }while(0)
#define GPIOC_RCC_RESET()				do {(RCC -> AHB1RSTR |=  (1U << 2)) ; (RCC -> AHB1RSTR &= ~(1U << 2)) ; }while(0)
#define GPIOD_RCC_RESET()				do {(RCC -> AHB1RSTR |=  (1U << 3)) ; (RCC -> AHB1RSTR &= ~(1U << 3)) ; }while(0)
#define GPIOE_RCC_RESET()				do {(RCC -> AHB1RSTR |=  (1U << 4)) ; (RCC -> AHB1RSTR &= ~(1U << 4)) ; }while(0)
#define GPIOH_RCC_RESET()				do {(RCC -> AHB1RSTR |=  (1U << 7)) ; (RCC -> AHB1RSTR &= ~(1U << 7)) ; }while(0)


//General macros

#define ENABLE 		1
#define DISABLE 	0
#define SET 		ENABLE
#define RESET 		DISABLE
#define GPIO_SET	ENABLE
#define GPIO_RESET	DISABLE
#define LOW			0
#define HIGH 		1

//GPIO header file
#include "stm32f401re_gpio_driver.h"

#endif /* INC_STM32_DRIVER_H_ */
