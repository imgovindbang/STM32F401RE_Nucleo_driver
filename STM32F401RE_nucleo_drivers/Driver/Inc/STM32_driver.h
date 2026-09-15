
#ifndef INC_STM32_DRIVER_H_
#define INC_STM32_DRIVER_H_


#include<stdint.h>
#include <stddef.h>


/*Addresses for memory*/

#define FLASD_BASEADDR 				0x08000000U 				/*This is the base address for flash memory*/
#define SRAM1_BASEADDR 				0x20000000U					/*This is the base address for SRAM1 memory*/
#define ROM_BASEADDR				0x1FFF0000U					/*This is the base address for system memory(ROM)*/
#define SRAM						SRAM1_BASEADDR

/*
base address of peripherals and buses
 */

#define PERIPH_BASEADDR 			0x40000000U                 		/* Peripheral Base address to access the peripheral */
#define APB1_BASEADDR				PERIPH_BASEADDR						/* APB1 Bus base address */
#define APB2_BASEADDR 				0x40010000U							/* APB2 Bus base address */
#define AHB1_BASEADDR				0x40020000U							/* AHB1 Bus base address */
#define AHB2_BASEADDR				0x50000000U							/* AHB2 Bus base address */

/*
Defining each peripheral base address of ABH1 bus (0x40020000)
*/

#define GPIOA_BASEADDR 				(AHB1_BASEADDR + 0x0000)			/* GPIOA Base address 0x40020000 */
#define GPIOB_BASEADDR				(AHB1_BASEADDR + 0x0400)			/* GPIOB Base address 0x40020400 */
#define GPIOC_BASEADDR				(AHB1_BASEADDR + 0x0800)			/* GPIOC Base address 0x40020800 */
#define GPIOD_BASEADDR 				(AHB1_BASEADDR + 0x0C00)			/* GPIOD Base address 0x40020C00 */
#define GPIOE_BASEADDR				(AHB1_BASEADDR + 0x1000)			/* GPIOE Base address 0x40021000 */
#define GPIOH_BASEADDR				(AHB1_BASEADDR + 0x1C00)			/* GPIOH Base address 0x40021C00 */
#define CRC_BASEADDR				(AHB1_BASEADDR + 0x3000)			/* Cyclic redundancy check Base address 0x40023000 */
#define RCC_BASEADDR 				(AHB1_BASEADDR + 0x3800)			/* Reset and clock control (RCC) Base address 0x40023800 */
#define FLASH_INTRREG_BASEADDR 		(AHB1_BASEADDR + 0x3C00)			/* Flash interface register Base address 0x40023C00 */
#define DMA1_BASEADDR 				(AHB1_BASEADDR + 0x6000)			/* Direct memory access (DMA1) Base address 0x40026000 */
#define DMA2_BASEADDR 				(AHB1_BASEADDR + 0x6400)			/* Direct memory access (DMA2) Base address 0x40026400 */


/*Base addresses of peripherals of bus ABH2 (0x50000000)*/

#define USB_OTG_FS_BASEADDR 		(AHB2_BASEADDR + 0x0000)			/* Universal Serial Bus (USB) OTG Base address 0x50000000 */

/*Base address of peripherals of bus APB2 (0x40010000)*/

#define TIM1_BASEADDR 				(APB2_BASEADDR + 0x0000)			/*	TIMER_1 base address  0x40010000 */
#define TIM9_BASEADDR 				(APB2_BASEADDR + 0x4000)			/*	TIMER_9 base address  0x40014000 */
#define TIM10_BASEADDR 				(APB2_BASEADDR + 0x4400)			/*	TIMER_10 base address 0x40014400 */
#define TIM11_BASEADDR 				(APB2_BASEADDR + 0x4800)			/*	TIMER_11 base address 0x40014800 */

#define USART1_BASEADDR 			(APB2_BASEADDR + 0x1000)			/*	Universal synchronous asynchronous receiver transmitter (USART1) 0x40011000 */
#define USART6_BASEADDR 			(APB2_BASEADDR + 0x1400)			/*	Universal synchronous asynchronous receiver transmitter (USART9) 0x40011400 */

#define ADC1_BASEADDR 				(APB2_BASEADDR + 0x2000)			/*	Analog-To-Digital converter(ADC1) 0x40012000 */
#define SDIO_BASEADDR 				(APB2_BASEADDR + 0x2C00)            /*	Secure digital input/output interface (SDIO) 0x40012C00 */

#define SPI1_BASEADDR 				(APB2_BASEADDR + 0x3000)			/* Serial Peripheral Interface (SPI1) 0x40013000 */
#define SPI4_BASEADDR 				(APB2_BASEADDR + 0x3400)			/* Serial Peripheral Interface (SPI4) 0x40013400 */

#define SYSCFG_BASEADDR 			(APB2_BASEADDR + 0x3800)			/* System configuration controller (SYSCFG)    0x40013800*/

#define EXTI_BASEADDR 				(APB2_BASEADDR + 0x3C00)			/* External interrupt/event controller (EXTI)  0x40013C00 */

/*Base address of peripherals of bus APB1 (0x4000 0000) */

#define TIM2_BASEADDR 				(APB1_BASEADDR + 0x0000)			/* TIMER_2 base address 0x0x40000000 */
#define TIM3_BASEADDR 				(APB1_BASEADDR + 0x0400)			/* TIMER_3 base address 0x0x40000400 */
#define TIM4_BASEADDR 				(APB1_BASEADDR + 0x0800)			/* TIMER_4 base address 0x0x40000800 */
#define TIM5_BASEADDR 				(APB1_BASEADDR + 0x0C00)			/* TIMER_5 base address 0x0x40000C00 */

#define RTC_BKP_BASEADDR 			(APB1_BASEADDR + 0x2800)			/* Real-time clock (RTC) base address 0x0x40002800 */

#define WWDG_BASEADDR 				(APB1_BASEADDR + 0x2C00)			/* Window watchdog (WWDG) base address 		0x40002C00 */
#define IWDG_BASEADDR 				(APB1_BASEADDR + 0x3000)			/* Independent watchdog (IWDG) base address 0x40003000 */

#define I2S2EXT_BASEADDR 			(APB1_BASEADDR + 0x3400)			/*	I2S2_EXT base address 0x40003400 */
#define I2S3EXT_BASEADDR 			(APB1_BASEADDR + 0x4000)			/*	I2S3_EXT base address 0x40004000 */

#define SPI2_I2S2_BASEADDR 			(APB1_BASEADDR + 0x3800)			/* Serial Peripheral Interface (SPI2) base address 0x40003800 */
#define SPI3_I2S3_BASEADDR 			(APB1_BASEADDR + 0x3C00)			/* Serial Peripheral Interface (SPI2) base address 0x40003C00 */

#define USART2_BASEADDR 			(APB1_BASEADDR + 0x4400)			/* Universal synchronous asynchronous receiver transmitter (USART2) base address 0x40004400 */

#define I2C1_BASEADDR 			    (APB1_BASEADDR + 0x5400)			/* Inter-integrated circuit (I2C1) interface base address 0x40005400 */
#define I2C2_BASEADDR 			    (APB1_BASEADDR + 0x5800)			/* Inter-integrated circuit (I2C2) interface base address 0x40005800 */
#define I2C3_BASEADDR 			    (APB1_BASEADDR + 0x5C00)			/* Inter-integrated circuit (I2C1) interface base address 0x40005C00 */

#define PWR_BASEADDR 			    (APB1_BASEADDR + 0x7000)			/* Power controller (PWR) base address 0x40007000 */

/********************************************************************************************************/

/* @GPIO registers */


typedef struct
{
	volatile uint32_t MODER;    		/* GPIO port mode register   				  		Address offset : 0x00 */
	volatile uint32_t OTYPER;			/* GPIO port output type register			  		Address offset : 0x04 */
	volatile uint32_t OSPEEDR;			/* GPIO port output speed register	 		  		Address offset : 0x08 */
	volatile uint32_t PUPDR;			/* GPIO port pull-up / pull-down register	  		Address offset : 0x0C */
	volatile uint32_t IDR;				/* GPIO port input data register			  		Address offset : 0x10 */
	volatile uint32_t ODR;				/* GPIO port output data register 			  		Address offset : 0x14 */
	volatile uint32_t BSRR;				/* GPIO port bit set/reset register 		  		Address offset : 0x18 */
	volatile uint32_t LCKR;				/* GPIO port configuration clock register 	  		Address offset : 0x1C */
	volatile uint32_t AFRL;				/* GPIO port Alternate function low register  		Address offset : 0x20 */
	volatile uint32_t AFRH;				/* GPIO port Alternate function high register 		Address offset : 0x24 */
}GPIO_Registers;

#define GPIOA 		((GPIO_Registers*)GPIOA_BASEADDR)
#define GPIOB 		((GPIO_Registers*)GPIOB_BASEADDR)
#define GPIOC 		((GPIO_Registers*)GPIOC_BASEADDR)
#define GPIOD 		((GPIO_Registers*)GPIOD_BASEADDR)
#define GPIOE 		((GPIO_Registers*)GPIOE_BASEADDR)
#define GPIOH 		((GPIO_Registers*)GPIOH_BASEADDR)

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
}RCC_Registers;

/*Define RCC */

#define RCC 	((RCC_Registers*)RCC_BASEADDR)

/* @External interrupt register EXTI*/

typedef struct
{
	volatile uint32_t IMR;						/*Interrupt mask register 										   	Address offset : 0x00*/
	volatile uint32_t EMR;						/*Event mask register 		                 					   	Address offset : 0x04*/
	volatile uint32_t RTSR;						/*Rising trigger selection register 							   	Address offset : 0x08*/
	volatile uint32_t FTSR;						/*Falling trigger selection register 							   	Address offset : 0x0C*/
	volatile uint32_t SWIER;					/*Software interrupt event register 							   	Address offset : 0x10*/
	volatile uint32_t PR;						/*Pending register 							   						Address offset : 0x14*/
}EXTI_Registers;

/*Define EXTI*/

#define EXTI 	((EXTI_Registers*)EXTI_BASEADDR)


/* @SYSCFG Registers */
typedef struct {
	volatile uint32_t MEMRMP; 					/*Memory remap register 							   	Address offset : 0x00*/
	volatile uint32_t PMC;						/*Peripheral mode control register 4					Address offset : 0x04*/
	volatile uint32_t EXTICR[4];				/*External interrupt register 1, 2, 3, 4				Address offset : 0x08 , 0x0C, 0x10, 0x14*/
    volatile uint32_t RESERVED0;   				/* Reserved 											Address offset : 0x18*/
    volatile uint32_t RESERVED1;   				/* Reserved 											Address offset : 0x1C*/
	volatile uint32_t CMPCR;					/*Compensation cell control register					Address offset : 0x20*/
}SYSCFG_Registers;

/*Define SYSCFG */

#define SYSCFG 	((SYSCFG_Registers*)SYSCFG_BASEADDR)

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
}SPI_Registers;

/* Define SPI*/
#define SPI1 	((SPI_Registers*)SPI1_BASEADDR)							//SPI_register Configuration for both SPI
#define SPI4 	((SPI_Registers*)SPI4_BASEADDR)							//SPI_register Configuration for both SPI
#define SPI2	((SPI_Registers*)SPI2_I2S2_BASEADDR) 					//SPI_register Configuration for both SPI and I2S
#define SPI3	((SPI_Registers*)SPI3_I2S3_BASEADDR)						//SPI_register Configuration for both SPI and I2S


/* @I2C Registers*/

typedef struct
{
	volatile uint32_t I2C_CR1;
	volatile uint32_t I2C_CR2;
	volatile uint32_t I2C_OAR1;
	volatile uint32_t I2C_OAR2;
	volatile uint32_t I2C_DR;
	volatile uint32_t I2C_SR1;
	volatile uint32_t I2C_SR2;
	volatile uint32_t I2C_CCR;
	volatile uint32_t I2C_TRISE;
	volatile uint32_t I2C_FLTR;
}I2C_Registers;

/* Macros for I2C Definition */
#define I2C1 		((I2C_Registers*)I2C1_BASEADDR)
#define I2C2 		((I2C_Registers*)I2C2_BASEADDR)
#define I2C3 		((I2C_Registers*)I2C3_BASEADDR)

/* @USART Registers */
typedef struct
{
	volatile uint32_t USART_SR;
	volatile uint32_t USART_DR;
	volatile uint32_t USART_BRR;
	volatile uint32_t USART_CR1;
	volatile uint32_t USART_CR2;
	volatile uint32_t USART_CR3;
	volatile uint32_t USART_GTPR;
}USART_Registers;

/* Macros for USART */
#define USART1   ((USART_Registers*)USART1_BASEADDR)
#define USART2	 ((USART_Registers*)USART2_BASEADDR)
#define USART6	 ((USART_Registers*)USART6_BASEADDR)


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

/* Macros to reset I2Cx */

#define I2C1_RCC_RESET()				do{RCC -> APB1RSTR |= (1U << 21) ; (RCC -> APB1RSTR &= ~(1U << 21)) ; }while(0);
#define I2C2_RCC_RESET()				do{RCC -> APB1RSTR |= (1U << 22) ; (RCC -> APB1RSTR &= ~(1U << 22)) ; }while(0);
#define I2C3_RCC_RESET()				do{RCC -> APB1RSTR |= (1U << 23) ; (RCC -> APB1RSTR &= ~(1U << 23)) ; }while(0);

/* Macros to reset USARTx */
#define USART1_RCC_RESET()				do{RCC -> APB2RSTR |= (1U << 4) ;  (RCC -> APB2RSTR &= ~(1U << 4)) ; }while(0);
#define USART2_RCC_RESET()				do{RCC -> APB1RSTR |= (1U << 17);  (RCC -> APB1RSTR &= ~(1U << 17)); }while(0);
#define USART6_RCC_RESET()				do{RCC -> APB2RSTR |= (1U << 5) ;  (RCC -> APB2RSTR &= ~(1U << 5)) ; }while(0);


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




//GPIO Driver header file
#include "STM32_GPIO_driver.h"

//RCC Driver Header file
#include "STM32_RCC_Driver.h"

//SPI Driver header file
#include "STM32_SPI_driver.h"

//I2C Driver header file
#include "STM32_I2C_Driver.h"

//USART Driver Header file
#include "STM32_USART_Driver.h"

#endif /* INC_STM32_DRIVER_H_ */
