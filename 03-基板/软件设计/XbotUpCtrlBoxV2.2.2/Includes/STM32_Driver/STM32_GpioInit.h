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

#define __GPIO_GLED1_PIN	GPIO_Pin_8			//KeySwLed_G1	 
#define __GPIO_GLED2_PIN	GPIO_Pin_9			//KeySwLed_G2
#define __GPIO_GLED1_PORT	GPIOC							//
#define __GPIO_GLED2_PORT	GPIOC

#define __GPIO_MT1CTRL_PIN	GPIO_Pin_9			//MT1_CTRL
#define __GPIO_MT2CTRL_PIN	GPIO_Pin_2			//MT2_CTRL
#define __GPIO_MT1CTRL_PORT	GPIOE				    //
#define __GPIO_MT2CTRL_PORT	GPIOD				    //

#define __GPIO_POWCTRL_PIN	GPIO_Pin_13			//PowerCnt:电源上电软自锁控制
#define __GPIO_POWCTRL_PORT	GPIOB				    //

#define __GPIO_CORE_POWCTRL_PIN	  GPIO_Pin_12			//PowerOutCnt:核心板上电控制
#define __GPIO_CORE_POWCTRL_PORT	GPIOB				    //


#define GLED1_OFF		GPIO_ResetBits(__GPIO_GLED1_PORT, __GPIO_GLED1_PIN)
#define GLED1_ON		GPIO_SetBits(__GPIO_GLED1_PORT, __GPIO_GLED1_PIN)
#define GLED2_OFF		GPIO_ResetBits(__GPIO_GLED2_PORT, __GPIO_GLED2_PIN)
#define GLED2_ON		GPIO_SetBits(__GPIO_GLED2_PORT, __GPIO_GLED2_PIN)

#define MT1CTRL_ON		GPIO_SetBits(__GPIO_MT1CTRL_PORT, __GPIO_MT1CTRL_PIN)	
#define MT1CTRL_OFF		GPIO_ResetBits(__GPIO_MT1CTRL_PORT, __GPIO_MT1CTRL_PIN)
#define MT2CTRL_ON		GPIO_SetBits(__GPIO_MT2CTRL_PORT, __GPIO_MT2CTRL_PIN)	
#define MT2CTRL_OFF		GPIO_ResetBits(__GPIO_MT2CTRL_PORT, __GPIO_MT2CTRL_PIN)

//电源开关软自锁控制
#define POWCTRL_ON		GPIO_SetBits(__GPIO_POWCTRL_PORT, __GPIO_POWCTRL_PIN)	
#define POWCTRL_OFF		GPIO_ResetBits(__GPIO_POWCTRL_PORT, __GPIO_POWCTRL_PIN)	

//核心板上电控制
#define CORE_POWCTRL_ON		GPIO_SetBits(__GPIO_CORE_POWCTRL_PORT, __GPIO_CORE_POWCTRL_PIN)	
#define CORE_POWCTRL_OFF		GPIO_ResetBits(__GPIO_CORE_POWCTRL_PORT, __GPIO_CORE_POWCTRL_PIN)	

/******************************************************************************************/

extern void STM32_GpioInit(void);
extern void STM32_GpioOneInit(uint16_t GPIO_Pin,	GPIOSpeed_TypeDef GPIO_Speed,	
				GPIOMode_TypeDef GPIO_Mode,	GPIO_TypeDef* GPIO_PORT);


#endif




