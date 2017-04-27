#ifndef __STM32_USART_H
#define __STM32_USART_H

#include "stm32f10x.h"
#include "STM32_UsartDriver.h"

extern void STM32_InitUsart1(u32 Baudrate);
extern void STM32_InitUsart2(u32 Baudrate);
extern void STM32_InitUsart3(u32 Baudrate);
extern void STM32_InitUsart4(u32 Baudrate);
extern void STM32_InitUsart5(u32 Baudrate);


extern USART_data_t USART_data_1;
extern USART_data_t USART_data_2;
extern USART_data_t USART_data_3;
extern USART_data_t USART_data_4;
extern USART_data_t USART_data_5;




#endif

