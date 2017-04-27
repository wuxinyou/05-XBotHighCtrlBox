#ifndef __STM32_ADC_H
#define __STM32_ADC_H	

#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"

#define STM32_ADC_CHANNEL_N	6		   
#define STM32_ADC_CACHEL_M	50

#define STM32_ADC_HB100	2
#define STM32_ADC_ACC_X	1
#define STM32_ADC_ACC_Y	0
	   
extern void Adc1Dma_Init(void);
extern uint16_t ADC1ConvertedValue[STM32_ADC_CACHEL_M][STM32_ADC_CHANNEL_N];  
extern uint16_t GetAdcAverageValue(uint16_t (*pAdcVaule)[STM32_ADC_CHANNEL_N],uint8_t AdcIndex,uint8_t DataLen);

	  
#endif 
