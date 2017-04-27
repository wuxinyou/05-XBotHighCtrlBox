#ifndef __BATTERY_ADC_READ_H
#define __BATTERY_ADC_READ_H	
#include "stm32f10x.h"
#include "STM32_Adc.h"

#define BAT_ADC_1		0X01
#define BAT_ADC_2		0X02

#define  BatteryGetAdc1()	GetAdcAverageValue(ADC1ConvertedValue,BAT_ADC_1,STM32_ADC_CACHEL_M)
#define  BatteryGetAdc2()	GetAdcAverageValue(ADC1ConvertedValue,BAT_ADC_2,STM32_ADC_CACHEL_M)

extern uint8_t BAT1_GetValue(void);
extern uint8_t BAT2_GetValue(void);

#endif
