

#include "STM32_TimInit.h"
#include "STM32_IRQ_INIT.H"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

#define SYS_FREQ_TIM2_7	72000000
#define SYS_FREQ_1MHz 	1000000
#define SYS_FREQ_100KHz 100000
#define SYS_FREQ_10KHz 	10000
#define SYS_FREQ_1KHz 	1000

//定时器1ms一次
//

/**************************** TIM2 定时器 *************************************/
void STM32_Tim2Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	/* System Clocks Configuration */
	{		
		/* TIM2 clock enable */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
  	/* NVIC Configuration */
	{	
		/* Enable the TIM2 global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = STM32_NVIC_TIM2_PrePriority;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = STM32_NVIC_TIM2_SubPriority;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
		NVIC_Init(&NVIC_InitStructure);
	}

	/* ---------------------------------------------------------------
	TIM2 Configuration: Output Compare Timing Mode:
	Frequency=(SYSCLK/(Prescaler+1)) /(Period+1)
	APB1 = 72/4=18MHz
	TIM2 counter clock at 100 KHz
	CC1 update rate = TIM2 counter clock / CCR1_Val = 1000 Hz
	
	--------------------------------------------------------------- */
	TIM_TimeBaseStructure.TIM_Period = 100;
	TIM_TimeBaseStructure.TIM_Prescaler = (SYS_FREQ_TIM2_7/SYS_FREQ_100KHz)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

 	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	
	
	STM32_DISABLE_TIM2;
}

/**************************** TIM3 定时器 *************************************/
void STM32_Tim3Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	/* System Clocks Configuration */
	{		
		/* TIM2 clock enable */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
  	/* NVIC Configuration */
	{	
		/* Enable the TIM2 global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = STM32_NVIC_TIM3_PrePriority;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = STM32_NVIC_TIM3_SubPriority;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
		NVIC_Init(&NVIC_InitStructure);
	}

	/* ---------------------------------------------------------------
	TIM2 Configuration: Output Compare Timing Mode:
	Frequency=(SYSCLK/(Prescaler+1)) /(Period+1)
	APB1 = 72/4=18MHz
	TIM2 counter clock at 100 KHz
	CC1 update rate = TIM2 counter clock / CCR1_Val = 100 Hz
	
	--------------------------------------------------------------- */
	TIM_TimeBaseStructure.TIM_Period = 1000;
	TIM_TimeBaseStructure.TIM_Prescaler = (SYS_FREQ_TIM2_7/SYS_FREQ_100KHz)-1;
	//TIM_TimeBaseStructure.TIM_Prescaler = (SYS_FREQ_TIM2_7/SYS_FREQ_10KHz)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

 	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);	
	
	STM32_DISABLE_TIM3;

}

/**************************** TIM4 定时器 *************************************/
void STM32_Tim4Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	/* System Clocks Configuration */
	{		
		/* TIM2 clock enable */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}
  	/* NVIC Configuration */
	{	
		/* Enable the TIM2 global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = STM32_NVIC_TIM4_PrePriority;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = STM32_NVIC_TIM4_SubPriority;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
		NVIC_Init(&NVIC_InitStructure);
	}

	/* ---------------------------------------------------------------
	TIM2 Configuration: Output Compare Timing Mode:
	Frequency=(SYSCLK/(Prescaler+1)) /(Period+1)
	APB1 = 72/4=18MHz
	TIM2 counter clock at 10 KHz
	CC1 update rate = TIM2 counter clock / CCR1_Val = 100 Hz
	
	--------------------------------------------------------------- */
	TIM_TimeBaseStructure.TIM_Period = 1000;
	TIM_TimeBaseStructure.TIM_Prescaler = (SYS_FREQ_TIM2_7/SYS_FREQ_10KHz)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

 	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);	
	
	STM32_DISABLE_TIM4;
}







