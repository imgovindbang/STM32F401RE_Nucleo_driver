#include "STM32_driver.h"

uint32_t AHB_PreSclar[8] = {2, 4, 8, 16, 64, 128, 256, 512};
uint8_t APB1_PreSclar[4] = {2, 4, 8, 16};

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

uint32_t RCC_PCLK2Value(void)
{
	uint32_t pclk2, sysclk;
	uint8_t temp, ahb, apb2;
	uint8_t clksrc = ((RCC -> CFGR >> 2) & 0x3);

	if(clksrc == 0)
	{
		sysclk = 16000000;
	}else
	{
		sysclk = 8000000;
	}

	temp = ((RCC -> CFGR >> 4) & 0xF);

	if(temp < 8)
	{
		ahb = 1;
	}else
	{
		ahb = AHB_PreSclar[temp - 8];
	}

	temp = ((RCC -> CFGR >> 13) & 0x7);

	if(temp < 4)
	{
		apb2 = 1;
	}else
	{
		apb2 = APB1_PreSclar[temp - 4];
	}

	pclk2 = (sysclk / ahb) / apb2;

	return pclk2;
}

uint32_t RCC_PLLOutClk(void)
{
	return 0; //Need to implement later
}



