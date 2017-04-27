#ifndef __TIM_UINIT_H
#define __TIM_UINIT_H

#include "stm32f10x.h"
#include "STM32_LedDisp.h"


#define STM32_ENABLE_TIM2		TIM_Cmd(TIM2, ENABLE);	
#define STM32_DISABLE_TIM2	   	TIM_Cmd(TIM2, DISABLE);
#define STM32_ENABLE_TIM3		TIM_Cmd(TIM3, ENABLE);	
#define STM32_DISABLE_TIM3	   	TIM_Cmd(TIM3, DISABLE);
#define STM32_ENABLE_TIM4		TIM_Cmd(TIM4, ENABLE);	
#define STM32_DISABLE_TIM4	   	TIM_Cmd(TIM4, DISABLE);


extern void STM32_Tim2Init(void);
extern void STM32_Tim3Init(void);
extern void STM32_Tim4Init(void);


#endif		


