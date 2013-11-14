/**
  ******************************************************************************
  * @file    led.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核原子核核心板 BSP构件 LED驱动
  ******************************************************************************
  */
#include "led.h"

/***********************************************************************************************
 功能：LED初始化
 形参：0
 返回：0
 详解：初始化板子上的LED 调用GPIO构件
************************************************************************************************/
void LED_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStruct1;
	
	GPIO_InitStruct1.GPIO_Pin = LED1_PIN;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = LED1_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = LED2_PIN;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = LED2_PORT;
	GPIO_Init(&GPIO_InitStruct1);
}


void LED_Set(uint8_t LEDNum, uint8_t OnOff)
{
	switch(LEDNum)
	{
		case 0:
			GPIO_WriteBit(LED1_PORT,LED1_PIN,OnOff);
			break;
		case 1:
			GPIO_WriteBit(LED2_PORT,LED2_PIN,OnOff);
			break;	
		default:break;
	}
}

void LED_Toggle(uint8_t LEDNum)
{
	switch(LEDNum)
	{
		case 0:
			GPIO_ToggleBit(LED1_PORT,LED1_PIN);
			break;
		case 1:
			GPIO_ToggleBit(LED2_PORT,LED2_PIN);
			break;
		default:break;
	}
}
