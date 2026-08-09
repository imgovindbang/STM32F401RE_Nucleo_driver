
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

/* @GPIO registers */


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

/* @RCC register */

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
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


/* @External interrupt register EXTI*/

typedef struct
{
	volatile uint32_t IMR;						/*Interrupt mask register 										   	Address offset : 0x00*/
	volatile uint32_t EMR;						/*Event mask register 		                 					   	Address offset : 0x04*/
	volatile uint32_t RTSR;						/*Rising trigger selection register 							   	Address offset : 0x08*/
	volatile uint32_t FTSR;						/*Falling trigger selection register 							   	Address offset : 0x0C*/
	volatile uint32_t SWIER;					/*Software interrupt event register 							   	Address offset : 0x10*/
	volatile uint32_t PR;						/*Pending register 							   						Address offset : 0x14*/
}EXTI_RegDef_t;

/* @SYSCFG Registers */
typedef struct {
	volatile uint32_t MEMRMP; 					/*Memory remap register 							   	Address offset : 0x00*/
	volatile uint32_t PMC;						/*Peripheral mode control register 4					Address offset : 0x04*/
	volatile uint32_t EXTICR[4];				/*External interrupt register 1, 2, 3, 4				Address offset : 0x08 , 0x0C, 0x10, 0x14*/
    volatile uint32_t RESERVED0;   				/* Reserved 											Address offset : 0x18*/
    volatile uint32_t RESERVED1;   				/* Reserved 											Address offset : 0x1C*/
	volatile uint32_t CMPCR;					/*Compensation cell control register					Address offset : 0x20*/
}SYSCFG_RegDef_t;


/* @SPI Registers*/

typedef struct
{
	volatile uint16_t SPI_CR1; 					/* SPI control Register 1  								Address offset : 0x00*/
	volatile uint16_t SPI_CR2;					/* SPI control Register 2  								Address offset : 0x04*/
	volatile uint16_t SPI_SR;					/* SPI Status Register 								    Address offset : 0x08*/
	volatile uint16_t SPI_DR;					/* SPI Data Register 								    Address offset : 0x0C*/
	volatile uint16_t SPI_CRCPR;				/* SPI CRC polynomial Register 						    Address offset : 0x10*/
	volatile uint16_t SPI_RXCRCR;				/* SPI RX CRC 											Address offset : 0x14*/
	volatile uint16_t SPI_TXCRCR;				/* SPI TX CRC 										 	Address offset : 0x18*/
	volatile uint16_t SPI_I2SCFGR;				/* SPI I2S Configuration Register 						Address offset : 0x1C*/
	volatile uint16_t SPI_I2SPR;				/* SPI I2S Pre-scaler Register 							Address offset : 0x20*/
}SPI_RegDef_t;

/*Define RCC */

#define RCC 	((RCC_RegDef_t*)RCC_BASEADDR)

/*Define EXTI*/

#define EXTI 	((EXTI_RegDef_t*)EXTI_BASEADDR)

/*Define SYSCFG */

#define SYSCFG 	((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/* Define SPI*/
#define SPI1 	((SPI_RegDef_t*)SPI1_BASEADDR)							//SPI_register Configuration for both SPI
#define SPI4 	((SPI_RegDef_t*)SPI4_BASEADDR)							//SPI_register Configuration for both SPI
#define SPI2	((SPI_RegDef_t*)SPI2_I2S2_BASEADDR) 					//SPI_register Configuration for both SPI and I2S
#define SPI3	((SPI_RegDef_t*)SPI3_I2S3_BASEADDR)						//SPI_register Configuration for both SPI and I2S

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


/* Macros to reset SPIx */

#define SPI1_RCC_RESET()				do {(RCC -> APB2RSTR |=  (1U << 12)) ; (RCC -> APB2RSTR &= ~(1U << 12)) ; }while(0)
#define SPI2_RCC_RESET()				do {(RCC -> APB1RSTR |=  (1U << 14)) ; (RCC -> APB1RSTR &= ~(1U << 14)) ; }while(0)
#define SPI3_RCC_RESET()				do {(RCC -> APB1RSTR |=  (1U << 15)) ; (RCC -> APB1RSTR &= ~(1U << 15)) ; }while(0)
#define SPI4_RCC_RESET()				do {(RCC -> APB2RSTR |=  (1U << 13)) ; (RCC -> APB2RSTR &= ~(1U << 13)) ; }while(0)


//General macros

#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define GPIO_SET		ENABLE
#define GPIO_RESET		DISABLE
#define LOW				0
#define HIGH 			1
#define FLAG_SET    	SET
#define FLAG_RESET		RESET

/* @IRQ Numbers*/

/* EXTI IRQ Numbers */

#define IRQ_NO_EXTI0          6
#define IRQ_NO_EXTI1          7
#define IRQ_NO_EXTI2          8
#define IRQ_NO_EXTI3          9
#define IRQ_NO_EXTI4          10
#define IRQ_NO_EXTI9_5        23
#define IRQ_NO_EXTI15_10      40

/* SPI IRQ Numbers */

#define IRQ_NO_SPI1           35
#define IRQ_NO_SPI2           36
#define IRQ_NO_SPI3           51
#define IRQ_NO_SPI4           84

/* I2C IRQ Numbers */

#define IRQ_NO_I2C1_EV        31
#define IRQ_NO_I2C1_ER        32
#define IRQ_NO_I2C2_EV        33
#define IRQ_NO_I2C2_ER        34
#define IRQ_NO_I2C3_EV        72
#define IRQ_NO_I2C3_ER        73

/* USART IRQ Numbers */

#define IRQ_NO_USART1         37
#define IRQ_NO_USART2         38
#define IRQ_NO_USART6         71

/* Timer IRQ Numbers */

#define IRQ_NO_TIM1_BRK_TIM9      24
#define IRQ_NO_TIM1_UP_TIM10      25
#define IRQ_NO_TIM1_TRG_COM_TIM11 26
#define IRQ_NO_TIM1_CC            27
#define IRQ_NO_TIM2               28
#define IRQ_NO_TIM3               29
#define IRQ_NO_TIM4               30
#define IRQ_NO_TIM5               50

/*NVIC_ISER Register base_addresses*/
#define NVIC_ISER0	((volatile uint32_t*)0xE000E100)
#define NVIC_ISER1	((volatile uint32_t*)0xE000E104)
#define NVIC_ISER2	((volatile uint32_t*)0xE000E108)
#define NVIC_ISER3	((volatile uint32_t*)0xE000E10C)

/*NVIC_ICER Register base address*/
#define NVIC_ICER0 	((volatile uint32_t*)0XE000E180)
#define NVIC_ICER1	((volatile uint32_t*)0XE000E184)
#define NVIC_ICER2	((volatile uint32_t*)0XE000E188)
#define NVIC_ICER3	((volatile uint32_t*)0XE000E18C)

/*NVIC_PR_BASE address*/

#define NVIC_PR_BASE_ADDR 	((volatile uint32_t*)0xE000E400)


/*GPIO IRQ Priority number */
#define NVIC_IRQ_PRIO0  	0
#define NVIC_IRQ_PRIO1  	1
#define NVIC_IRQ_PRIO2  	2
#define NVIC_IRQ_PRIO3  	3
#define NVIC_IRQ_PRIO4  	4
#define NVIC_IRQ_PRIO5  	5
#define NVIC_IRQ_PRIO6  	6
#define NVIC_IRQ_PRIO7  	7
#define NVIC_IRQ_PRIO8  	8
#define NVIC_IRQ_PRIO9  	9
#define NVIC_IRQ_PRIO10 	10
#define NVIC_IRQ_PRIO11 	11
#define NVIC_IRQ_PRIO12 	12
#define NVIC_IRQ_PRIO13 	13
#define NVIC_IRQ_PRIO14 	14
#define NVIC_IRQ_PRIO15 	15


//GPIO header file
#include "STM32_GPIO_driver.h"

//SPI header file
#include "STM32_SPI_driver.h"


#endif /* INC_STM32_DRIVER_H_ */
