/* 	版本信息：	V1.01
	创建时间：	2012－08－01
	最后修改：	2012－09－10

	备注：端口配置函数

*/

#ifndef __GPIO_INIT_H
#define __GPIO_INIT_H	
#include "stm32f4xx.h"
#define __GPIO_5VCT_PIN		GPIO_Pin_4							//
#define __GPIO_5VCT_PORT	GPIOC										//
#define __GPIO_LIGHT_PIN	GPIO_Pin_5							//
#define __GPIO_LIGHT_PORT	GPIOC										//

#define __GPIO_TURNOFF_PIN		GPIO_Pin_2							//
#define __GPIO_TURNOFF_PORT		GPIOC										//
#define __GPIO_IN1_PIN		__GPIO_TURNOFF_PIN		
#define __GPIO_IN1_PORT		__GPIO_TURNOFF_PORT				//

#define POW_ON		GPIO_SetBits(__GPIO_5VCT_PORT, __GPIO_5VCT_PIN)	
#define POW_OFF		GPIO_ResetBits(__GPIO_5VCT_PORT, __GPIO_5VCT_PIN)
#define LIGHT_ON		GPIO_SetBits(__GPIO_LIGHT_PORT, __GPIO_LIGHT_PIN)	
#define LIGHT_OFF		GPIO_ResetBits(__GPIO_LIGHT_PORT, __GPIO_LIGHT_PIN) 
/******************************************************************************************/

extern void STM32_GpioOneInit(uint16_t GPIO_Pin,	GPIOSpeed_TypeDef GPIO_Speed,	
				GPIOMode_TypeDef GPIO_Mode,	GPIOOType_TypeDef GPIO_OType,
				GPIOPuPd_TypeDef GPIO_PuPd,	GPIO_TypeDef* GPIO_PORT);

extern void STM32_GpioInit(void);
#endif




