#ifndef __JOY_STICK_ADC_READ_H
#define __JOY_STICK_ADC_READ_H	
#include "stm32f10x.h"
#include "STM32_Adc.h"
#include "MySysdefine.h"
#include "STM32_SysTick.h"

#define JOYSTICK_LEFT_X		0X02
#define JOYSTICK_LEFT_Y		0X03
#define JOYSTICK_RIGHT_X	0X04
#define JOYSTICK_RIGHT_Y	0X05

#define  JoyStickGetLeftAdcX()	GetAdcAverageValue(ADC1ConvertedValue,JOYSTICK_LEFT_X,STM32_ADC_CACHEL_M)
#define  JoyStickGetLeftAdcY()	GetAdcAverageValue(ADC1ConvertedValue,JOYSTICK_LEFT_Y,STM32_ADC_CACHEL_M)
#define  JoyStickGetRightAdcX()	GetAdcAverageValue(ADC1ConvertedValue,JOYSTICK_RIGHT_Y,STM32_ADC_CACHEL_M)
#define  JoyStickGetRightAdcY()	(0x0FFF-GetAdcAverageValue(ADC1ConvertedValue,JOYSTICK_RIGHT_X,STM32_ADC_CACHEL_M))

//上下为Y轴，左右为X轴										   
//上为最大，0X0FFF;下为最小0X0000
//左为最小，0X0000;右为最大0X0FFF

extern uint16_t  JK_ADC_ZERO_LX,JK_ADC_ZERO_LY;
extern uint16_t  JK_ADC_ZERO_RX,JK_ADC_ZERO_RY;

extern bool JoyStickAdcReadInit(void);
extern int8_t JK_GetValue(uint16_t AdcValue,uint16_t AdcZero);

#define JK_GetValue_LX()  JK_GetValue(JoyStickGetLeftAdcX(),JK_ADC_ZERO_LX)
#define JK_GetValue_LY()  JK_GetValue(JoyStickGetLeftAdcY(),JK_ADC_ZERO_LY)
#define JK_GetValue_RX()  JK_GetValue(JoyStickGetRightAdcX(),JK_ADC_ZERO_RX)
#define JK_GetValue_RY()  JK_GetValue(JoyStickGetRightAdcY(),JK_ADC_ZERO_RY)



#endif
