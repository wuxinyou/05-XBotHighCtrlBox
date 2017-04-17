
#include "STM32_GpioInit.h"
	 
void STM32_GpioOneInit(uint16_t GPIO_Pin,	GPIOSpeed_TypeDef GPIO_Speed,	
				GPIOMode_TypeDef GPIO_Mode,	GPIO_TypeDef* GPIO_PORT)	
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin ;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode; 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;
  	GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
}

void STM32_GpioInit(void)
{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);

	STM32_GpioOneInit(__GPIO_GLED1_PIN,GPIO_Speed_2MHz,GPIO_Mode_Out_PP,__GPIO_GLED1_PORT);
	STM32_GpioOneInit(__GPIO_GLED2_PIN,GPIO_Speed_2MHz,GPIO_Mode_Out_PP,__GPIO_GLED2_PORT);

	STM32_GpioOneInit(__GPIO_MT1CTRL_PIN,GPIO_Speed_2MHz,GPIO_Mode_Out_PP,__GPIO_MT1CTRL_PORT);
	STM32_GpioOneInit(__GPIO_MT2CTRL_PIN,GPIO_Speed_2MHz,GPIO_Mode_Out_PP,__GPIO_MT2CTRL_PORT);
	
	STM32_GpioOneInit(__GPIO_POWCTRL_PIN,GPIO_Speed_2MHz,GPIO_Mode_Out_PP,__GPIO_POWCTRL_PORT);
	
	

	  
}



