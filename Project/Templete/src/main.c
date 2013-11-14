
#include "sys.h"
#include "gpio.h"
#include "uart.h"
#include "delay.h"
#include "led.h"
#include "dma.h"
#include "spi.h"
#include "pit.h"
#include "adc.h"
#include "mag3110.h"
#include "at24cxx.h"


int main(void)
{
  //Clock Setup Internal Clock , CoreClock = 24M
	SystemClockSetup(ClockSource_IRC,CoreClock_24M);
	//DelayInit
	DelayInit();
	//LED Init
	LED_Init();
	
  //Init a debug UART prot
//	UART_DebugPortInit(UART1_RX_PC03_TX_PC04,115200);
	UART_DebugPortInit(UART0_RX_PB16_TX_PB17,115200);
	DisplayCPUInfo();



	
	GPIO_Test();
	MAG3110_Test();
	
	AT24Cxx_Test();
	SPIFLASH_Test();
	ADC_Test();
       WDOG_Init();
	while(1);

}


void assert_failed(uint8_t* file, uint32_t line)
{
	//UART_printf("assert_failed:line:%d %s\r\n",line,file);
	while(1);
}


