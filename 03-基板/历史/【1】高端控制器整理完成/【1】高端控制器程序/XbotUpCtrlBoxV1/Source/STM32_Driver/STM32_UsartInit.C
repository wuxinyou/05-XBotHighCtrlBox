
/* Includes ------------------------------------------------------------------*/


#include "STM32_UsartInit.h"
#include "STM32_UsartDriver.h"
#include "STM32_IRQ_INIT.H"

//***************************适用于STM32103VC********************************
//***************************适用于STM32103VC********************************

/*! USART data struct used in example. */
USART_data_t USART_data_1;
USART_data_t USART_data_2;
USART_data_t USART_data_3;
USART_data_t USART_data_4;
USART_data_t USART_data_5;




void STM32_Usart_InitNVIC(uint8_t NVIC_IRQChannel,uint8_t NVIC_IRQChannelPreemptionPriority,
					uint8_t NVIC_IRQChannelSubPriority)
{	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the USART Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel 	= NVIC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/* USART1 configured as follow:*/
//115200,8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
void STM32_Usart_InitConfig(USART_TypeDef *USART_x, u32 Baudrate,uint16_t USART_Mode)
{
	USART_InitTypeDef USART_InitStructure;

	//将结构体设置为缺省状态
   	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = Baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode;

	/* Configure USART1 */
	USART_Init(USART_x, &USART_InitStructure);
}

/*****************************************************************************/

/*****************************STM32 USART1 初始化****************************/
void STM32_InitUsart1(u32 Baudrate)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InterruptDriver_Initialize(&USART_data_1,USART1);

	USART_Cmd(USART1, DISABLE);

	/* System Clocks Configuration */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  

	/* Configure the GPIO ports */
	/*the USART Pins Software Remapping */
	GPIO_PinRemapConfig(GPIO_Remap_USART1, DISABLE);	
	STM32_GpioOneInit(GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,	GPIOA);
	STM32_GpioOneInit(GPIO_Pin_9,  GPIO_Speed_50MHz, GPIO_Mode_AF_PP,		GPIOA);
#ifdef USART1_RS485
	STM32_GpioOneInit(__GPIO_UART1E_PIN, GPIO_Speed_50MHz,GPIO_Mode_Out_PP,__GPIO_UART1E_PORT);
#endif

//	/* USART configured as follow:*/
//	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
//	STM32_Usart_InitConfig(USART1, Baudrate, USART_Mode_Tx|USART_Mode_Rx);

		

	//将结构体设置为缺省状态
   	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = Baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;

	/* Configure USART1 */
	USART_Init(USART1, &USART_InitStructure);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(USART1_IRQn,STM32_NVIC_USART1_PrePriority,
				STM32_NVIC_USART1_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_TC, ENABLE);

	/* Enable the USARTy */
	USART_Cmd(USART1, ENABLE);

}

/*****************************************************************************/

/*****************************STM32 USART2 初始化****************************/
void STM32_InitUsart2(u32 Baudrate)
{
	USART_InterruptDriver_Initialize(&USART_data_2,USART2);

	USART_Cmd(USART2, DISABLE);

	/* System Clocks Configuration */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  

	/* Configure the GPIO ports */
	/*the USART Pins Software Remapping */
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);	
	STM32_GpioOneInit(GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,	GPIOD);
	STM32_GpioOneInit(GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_AF_PP,		GPIOD);
#ifdef USART2_RS485
	STM32_GpioOneInit(__GPIO_UART2E_PIN, GPIO_Speed_50MHz,GPIO_Mode_Out_PP,__GPIO_UART2E_PORT);
#endif

	/* USART configured as follow:*/
	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
	STM32_Usart_InitConfig(USART2, Baudrate, USART_Mode_Tx|USART_Mode_Rx);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(USART2_IRQn,STM32_NVIC_USART2_PrePriority,
				STM32_NVIC_USART2_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_TC, ENABLE);

	/* Enable the USARTy */
	USART_Cmd(USART2, ENABLE);

}

/*****************************************************************************/

/*****************************STM32 USART3 初始化****************************/
void STM32_InitUsart3(u32 Baudrate)
{
	USART_InterruptDriver_Initialize(&USART_data_3,USART3);

	USART_Cmd(USART3, DISABLE);

	/* System Clocks Configuration */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  

	/* Configure the GPIO ports */
	/*the USART Pins Software Remapping */
	GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);	
	STM32_GpioOneInit(GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,	GPIOD);
	STM32_GpioOneInit(GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_AF_PP,		GPIOD);
#ifdef USART3_RS485
	STM32_GpioOneInit(__GPIO_UART3E_PIN, GPIO_Speed_50MHz,GPIO_Mode_Out_PP,__GPIO_UART3E_PORT);
#endif
 

	/* USART configured as follow:*/
	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
	STM32_Usart_InitConfig(USART3, Baudrate, USART_Mode_Tx|USART_Mode_Rx);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(USART3_IRQn,STM32_NVIC_USART3_PrePriority,
				STM32_NVIC_USART3_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART3, USART_IT_TC, ENABLE);

	/* Enable the USARTy */
	USART_Cmd(USART3, ENABLE);

}

/*****************************************************************************/

/*****************************STM32 USART4 初始化****************************/
void STM32_InitUsart4(u32 Baudrate)
{
	USART_InterruptDriver_Initialize(&USART_data_4,UART4);

	USART_Cmd(UART4, DISABLE);

	/* System Clocks Configuration */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);    

	/* Configure the GPIO ports */
	/*the USART Pins Software Remapping */
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);	
	STM32_GpioOneInit(GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,	GPIOC);
	STM32_GpioOneInit(GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_AF_PP,		GPIOC);
#ifdef USART4_RS485
	STM32_GpioOneInit(__GPIO_UART4E_PIN, GPIO_Speed_50MHz,GPIO_Mode_Out_PP,__GPIO_UART4E_PORT);
#endif

	/* USART configured as follow:*/
	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
	STM32_Usart_InitConfig(UART4, Baudrate, USART_Mode_Tx|USART_Mode_Rx);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(UART4_IRQn,STM32_NVIC_USART4_PrePriority,
				STM32_NVIC_USART4_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	USART_ITConfig(UART4, USART_IT_TC, ENABLE);

	/* Enable the USARTy */
	USART_Cmd(UART4, ENABLE);

}

/*****************************************************************************/

/*****************************STM32 USART5 初始化****************************/
void STM32_InitUsart5(u32 Baudrate)
{
	USART_InterruptDriver_Initialize(&USART_data_5,UART5);

	USART_Cmd(UART5, DISABLE);

	/* System Clocks Configuration */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);     

	/* Configure the GPIO ports */
	/*the USART Pins Software Remapping */
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);	
	STM32_GpioOneInit(GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,	GPIOD);
	STM32_GpioOneInit(GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_AF_PP,		GPIOC);
#ifdef USART5_RS485
	STM32_GpioOneInit(__GPIO_UART5E_PIN, GPIO_Speed_50MHz,GPIO_Mode_Out_PP,__GPIO_UART5E_PORT);
#endif

	/* USART configured as follow:*/
	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
	STM32_Usart_InitConfig(UART5, Baudrate, USART_Mode_Tx|USART_Mode_Rx);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(UART5_IRQn,STM32_NVIC_USART5_PrePriority,
				STM32_NVIC_USART5_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	USART_ITConfig(UART5, USART_IT_TC, ENABLE);

	/* Enable the USARTy */
	USART_Cmd(UART5, ENABLE);

}





/**************************** USART1 IRQHandler ********************************/
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    /* Read one byte from the receive data register */
	USART_RXComplete(&USART_data_1);
  
  }
  
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  { 
  	USART_ClearITPendingBit(USART1,USART_IT_TXE);  
    /* Write one byte to the transmit data register */
	USART1_DataRegEmpty(&USART_data_1);
   
  }

  if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)
  { 
  	USART_ClearITPendingBit(USART1,USART_IT_TC); 
	#ifdef USART1_RS485
		USART1_RS485_TX_DIS;
	#endif 
	
  }
}

/**************************** USART2 IRQHandler ********************************/
void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    /* Read one byte from the receive data register */
	USART_RXComplete(&USART_data_2);
  
  }
  
  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {   
  	USART_ClearITPendingBit(USART2,USART_IT_TXE);
	/* Write one byte to the transmit data register */
	USART2_DataRegEmpty(&USART_data_2); 
  }

   if(USART_GetITStatus(USART2, USART_IT_TC) != RESET)
  { 
  	USART_ClearITPendingBit(USART2,USART_IT_TC);  
	#ifdef USART2_RS485
		USART2_RS485_TX_DIS;
	#endif  
  }
}

/**************************** USART3 IRQHandler ********************************/
void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    /* Read one byte from the receive data register */
	USART_RXComplete(&USART_data_3);
  
  }
  
  if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  { 
  	USART_ClearITPendingBit(USART3,USART_IT_TXE);  
    /* Write one byte to the transmit data register */
	USART3_DataRegEmpty(&USART_data_3);
   
  }

   if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
  { 
  	USART_ClearITPendingBit(USART3,USART_IT_TC);  
	#ifdef USART3_RS485
		USART3_RS485_TX_DIS;
	#endif 
  }
}

/**************************** USART4 IRQHandler ********************************/
void UART4_IRQHandler(void)
{
  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(UART4, USART_IT_RXNE);
    /* Read one byte from the receive data register */
	USART_RXComplete(&USART_data_4);
  
  }
  
  if(USART_GetITStatus(UART4, USART_IT_TXE) != RESET)
  {  
  	USART_ClearITPendingBit(UART4,USART_IT_TXE); 
    /* Write one byte to the transmit data register */
	USART4_DataRegEmpty(&USART_data_4);
   
  }

   if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)
  { 
  	USART_ClearITPendingBit(UART4,USART_IT_TC);  
	#ifdef USART4_RS485
		USART4_RS485_TX_DIS;
	#endif 
  }
}


/**************************** USART5 IRQHandler ********************************/
void UART5_IRQHandler(void)
{
  if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(UART5, USART_IT_RXNE);
    /* Read one byte from the receive data register */
	USART_RXComplete(&USART_data_5);
  
  }
  
  if(USART_GetITStatus(UART5, USART_IT_TXE) != RESET)
  {  
  	USART_ClearITPendingBit(UART5,USART_IT_TXE); 
    /* Write one byte to the transmit data register */
	USART5_DataRegEmpty(&USART_data_5);
   
  }

   if(USART_GetITStatus(UART5, USART_IT_TC) != RESET)
  { 
  	USART_ClearITPendingBit(UART5,USART_IT_TC);  
	#ifdef USART5_RS485
		USART5_RS485_TX_DIS;
	#endif 
  }
}



