/*********************************************************************
说明：采集电源开关，电源开关是自复位开关。所以需要添加一个GPIO用来保存开关状态
作者：吴新有
日期：20170417
备注：按下第一次开机，按下第二次关机，目前没有添加长按操作，可能会出现误触的情况

**********************************************************************/

#ifndef __SW_ADC_READ_H
#define __SW_ADC_READ_H	
#include "stm32f10x.h"
#include "STM32_Adc.h"

#include "STM32_GpioInit.h"  
#include "STM32_LedDisp.h"

#define SW_ADC		0X06


#define  SWGetAdc()	GetAdcAverageValue(ADC1ConvertedValue,SW_ADC,STM32_ADC_CACHEL_M)


extern uint8_t SW_GetValue(void);
extern void SW_DealAdcValue(void);  //处理SWAdc数据值

#endif
