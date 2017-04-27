#ifndef __STM32_SYSTICK_H
#define __STM32_SYSTICK_H

#include "stm32f10x.h"

extern void SysTick_Init(void); 

extern void SysTick_Delay(__IO uint32_t nTime);
extern void SysTick_TimingDelay_Decrement(void);
extern void SysTick_DelayUs(unsigned int time);
extern void SysTick_DelayMs(unsigned int time);


#endif

