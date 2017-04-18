#ifndef __GPIO_INIT_H
#define __GPIO_INIT_H	
#include "stm32f10x.h"


//	GLED1		PC8
//	GLED2		PC9
//	UART2_E		PD10
//	UART3_E		PA8
//	UART4_E		PC12
//	MT1_CTRL	PE9
//	MT2_CTRL	PD2

#define __GPIO_GLED1_PIN	GPIO_Pin_8			//	 
#define __GPIO_GLED2_PIN	GPIO_Pin_9			// 
#define __GPIO_GLED1_PORT	GPIOC							//
#define __GPIO_GLED2_PORT	GPIOC

#define __GPIO_MT1CTRL_PIN	GPIO_Pin_9			//
#define __GPIO_MT2CTRL_PIN	GPIO_Pin_2			//

#define __GPIO_MT1CTRL_PORT	GPIOE				//
#define __GPIO_MT2CTRL_PORT	GPIOD				//

#define GLED1_OFF		GPIO_ResetBits(__GPIO_GLED1_PORT, __GPIO_GLED1_PIN)
#define GLED1_ON		GPIO_SetBits(__GPIO_GLED1_PORT, __GPIO_GLED1_PIN)
#define GLED2_OFF		GPIO_ResetBits(__GPIO_GLED2_PORT, __GPIO_GLED2_PIN)
#define GLED2_ON		GPIO_SetBits(__GPIO_GLED2_PORT, __GPIO_GLED2_PIN)



#define MT1CTRL_ON		GPIO_SetBits(__GPIO_MT1CTRL_PORT, __GPIO_MT1CTRL_PIN)	
#define MT1CTRL_OFF		GPIO_ResetBits(__GPIO_MT1CTRL_PORT, __GPIO_MT1CTRL_PIN)
#define MT2CTRL_ON		GPIO_SetBits(__GPIO_MT2CTRL_PORT, __GPIO_MT2CTRL_PIN)	
#define MT2CTRL_OFF		GPIO_ResetBits(__GPIO_MT2CTRL_PORT, __GPIO_MT2CTRL_PIN)


/******************************************************************************************/

extern void STM32_GpioInit(void);
extern void STM32_GpioOneInit(uint16_t GPIO_Pin,	GPIOSpeed_TypeDef GPIO_Speed,	
				GPIOMode_TypeDef GPIO_Mode,	GPIO_TypeDef* GPIO_PORT);


#endif




