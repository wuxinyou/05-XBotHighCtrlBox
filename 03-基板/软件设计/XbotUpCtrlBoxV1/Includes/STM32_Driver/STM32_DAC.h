#ifndef __STM32_DAC_H
#define __STM32_DAC_H	

#include "stm32f10x.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_gpio.h"


#define __GPIO_DAC1_PIN		GPIO_Pin_4	
#define __GPIO_DAC2_PIN		GPIO_Pin_5
#define __GPIO_DAC1_PORT	GPIOA	
#define __GPIO_DAC2_PORT	GPIOA		
	   
extern void STM32_DacInit(void);
extern void STM32_DacSetValue(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);

	  
#endif 


