#ifndef __LEDDISP_H
#define __LEDDISP_H

extern void LedDisp_Init(void);

#define __LED1_PIN	GPIO_Pin_14
#define __LED2_PIN	GPIO_Pin_15
//#define __LED3_PIN	GPIO_Pin_14
//#define __LED4_PIN	GPIO_Pin_15
//#define __LED5_PIN 	GPIO_Pin_6

#define __LED1_PORT	GPIOB
#define __LED2_PORT	GPIOB
//#define __LED3_PORT	GPIOB
//#define __LED4_PORT	GPIOB
//#define __LED5_PORT	GPIOA


#ifdef __LED1_PIN
#define LED1_ON		GPIO_ResetBits(__LED1_PORT, __LED1_PIN)
#define LED1_OFF	GPIO_SetBits(__LED1_PORT, __LED1_PIN)
#define LED1_TGL    GPIO_WriteBit(__LED1_PORT, __LED1_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(__LED1_PORT, __LED1_PIN)))
#endif


#ifdef __LED2_PIN
#define LED2_ON		GPIO_ResetBits(__LED2_PORT, __LED2_PIN)
#define LED2_OFF	GPIO_SetBits(__LED2_PORT, __LED2_PIN)
#define LED2_TGL    GPIO_WriteBit(__LED2_PORT, __LED2_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(__LED2_PORT, __LED2_PIN)))
#endif

#ifdef __LED3_PIN
#define LED3_ON		GPIO_ResetBits(__LED3_PORT, __LED3_PIN)
#define LED3_OFF	GPIO_SetBits(__LED3_PORT, __LED3_PIN)
#define LED3_TGL    GPIO_WriteBit(__LED3_PORT, __LED3_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(__LED3_PORT, __LED3_PIN)))
#endif

#ifdef __LED4_PIN
#define LED4_ON		GPIO_ResetBits(__LED4_PORT, __LED4_PIN)
#define LED4_OFF	GPIO_SetBits(__LED4_PORT, __LED4_PIN)
#define LED4_TGL    GPIO_WriteBit(__LED4_PORT, __LED4_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(__LED4_PORT, __LED4_PIN)))
#endif

#ifdef __LED5_PIN
#define LED5_ON		GPIO_ResetBits(__LED5_PORT, __LED5_PIN)
#define LED5_OFF	GPIO_SetBits(__LED5_PORT, __LED5_PIN)
#define LED5_TGL    GPIO_WriteBit(__LED5_PORT, __LED5_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(__LED5_PORT, __LED5_PIN)))
#endif


#endif

