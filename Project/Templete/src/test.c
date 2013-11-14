#include "gpio.h"
#include "delay.h"
#include "mag3110.h"
#include "at24cxx.h"
#include "spiflash.h"
#include "adc.h"

void GPIO_Test(void)
{
	uint32_t i = 0;
	GPIO_InitTypeDef GPIO_InitStruct1;
	GPIO_InitStruct1.GPIO_Pin = 6;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = PTA;
	GPIO_Init(&GPIO_InitStruct1);
	GPIO_InitStruct1.GPIO_Pin = 5;
	GPIO_Init(&GPIO_InitStruct1);
	for(i=0;i<10;i++)
	{
		GPIO_ToggleBit(PTA,6);
		GPIO_ToggleBit(PTA,5);
		DelayMs(100);
	}
}

void MAG3110_Test(void)
{
	uint8_t ret;
	MAG3110_XYZDataTypeDef MAG3110_XYZDataStruct1;
	ret = MAG3110_Init();
	if(ret == TRUE)
	{
		UART_printf("MAG3110 Succ\r\n");
	}
	else
	{
		UART_printf("MAG3110 Err\r\n");
	}
	ret = 0;
	while(ret < 30)
	if(MAG3110_GetXYZData(&MAG3110_XYZDataStruct1) == TRUE)
	{
		UART_printf("x:%d\r\n",abs(MAG3110_XYZDataStruct1.m_XData));
		ret++;
	}
}


#define AT24CXX_TEST_ADDR   1234
#define AT24CXX_TEST_DATASIZE 64
void AT24Cxx_Test(void)
{
	uint16_t i = 0;
	uint8_t buffer[AT24CXX_TEST_DATASIZE];
	UART_printf("beigin AT24Cxx Test\r\n");
	AT24Cxx_Init();
	for(i=0;i<sizeof(buffer);i++)
	{
		buffer[i] = i;
	}
	AT24Cxx_Write(buffer, AT24CXX_TEST_ADDR, sizeof(buffer));
	for(i=0;i<sizeof(buffer);i++)
	{
		buffer[i] = 0;
	}
	AT24Cxx_Read(buffer,AT24CXX_TEST_ADDR,sizeof(buffer));
	for(i=0;i<sizeof(buffer);i++)
	{
		if(buffer[i] != i)
		{
			UART_printf("AT24Cxx Test:Err:buffer[%d] = %d\r\n",i,buffer[i]);
		}
	}
	UART_printf("AR24CXX Test complete\r\n");
}


void SPIFLASH_Test(void)
{
	uint8_t ret;
	ret = SPIFLASH_Init();
	if(ret == TRUE)
	{
		UART_printf("spiflash init succ.\r\n");
		UART_printf("begin self test\r\n");
		ret = SPI_FLASH_SelfTest();
		if(ret == TRUE)
		{
			UART_printf("spiflash test succ\r\n");
		}
		else
		{
			UART_printf("spiflash test err\r\n");
		}
	}
	else
	{
		UART_printf("spiflash init err\r\n");
	}
}

void ADC_Test(void)
{
	uint8_t i = 0;
	uint16_t res = 0;
	ADC_InitTypeDef ADC_InitStruct1;
	UART_printf("Begin ADC test\r\n");
	ADC_InitStruct1.ADCxMap = ADC0_SE3A_PE22;
	ADC_InitStruct1.ADC_Precision = ADC_PRECISION_12BIT;
	ADC_InitStruct1.ADC_TriggerSelect = ADC_TRIGGER_SW;
	ADC_Init(&ADC_InitStruct1);
	while(i<10)
	{
		res = ADC_GetConversionValue(ADC0_SE3A_PE22);
		UART_printf("ADRest:%d\r\n",res);
		DelayMs(200);
		i++;
	}
	UART_printf("ADC test complete\r\n");
}

