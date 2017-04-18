
//定时器函数

//TIM2 
//TIM3
//TIM4


#include "STM32F4_IRQ_INIT.H"
#include "XbotCtrlDriver.h"
#include "XbotSysCtrl.h"

#include "STM32F4_DriverInit.h"
// #include "STM32F4_SysTick.h"

// SerialPort *s1;
// SerialPort *s2;
//1ms 触发一次
/******************************  TIM2_IRQHandler *************************************/
void TIM2_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
		STM32_DISABLE_TIM2; 
//		Sw0_OpTask();															//关机按键检测
		
// 		if(ssss.XbotCtrlDrvRXD(&ssss))
// 			LED1_TGL;
// 		while(s1->putChar(0x12));
// 		while(s2->putChar(0x22));
// 			while(USART_TXBuffer_PutByte(&USART_data_4,0x12));
// 			ssss.XbotCtrlDrvTXD(&ssss);
// 		XbotCtrlDrvISO(&USART_data_4,&USART_data_3,&XBOT_CTRLBUS_DEV_BUF);
// 		XbotSysRcDealAllTask(&USART_RC_WIRE, &USART_RC_WIRELESS,	
// 						&XBOT_CTRLBUS_DEV_BUF, &XBOT_SYS_CTRL_PARA);	 		//接收和处理无线或有线信息 并反馈数据到终端

// 		XbotMotorDrvDealRxdData(&USART_ARM18_CTRL, &XBOT_ARM18_DEV_BUF,			//处理机械臂数据
// 							XBOT_ARM18_DEV_PARA);

// 		XbotMotorDrvDealRxdData(&USART_MOTION_CTRL, &XBOT_MOTION_DEV_BUF,		//处理运动底盘数据
// 							XBOT_MOTION_DEV_PARA);

		STM32_ENABLE_TIM2;		
	}
}

// 	uint8_t aaa[32];
// 	uint8_t index=0;
// void TIM2_IRQHandler(void)
// { 	
// 	uint8_t i;
// 	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
// 	{
// 		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
// 		STM32_DISABLE_TIM2;
// 		while(USART_RXBufferData_Available(&USART_data_4))
// 		{
// 			aaa[index]=USART_RXBuffer_GetByte(&USART_data_4);
// 			if(aaa[index]==0x80)
// 			{
// 				for(i=0;i<=index;i++)
// 				{
// 					while (!USART_TXBuffer_PutByte(&USART_data_4,aaa[i]));
// 				}
// 				index=0;
// 			}
// 			else
// 				index++;
// 		}
// 		STM32_ENABLE_TIM2;		
// 	}
// }

//  #define MOTOR3TIME 2

//10ms触发一次
/******************************  TIM3_IRQHandler *************************************/
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{ 
		TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);

		STM32_DISABLE_TIM3;
		
// 		XbotMotorDrvTxAllCmd(&USART_ARM18_CTRL, &XBOT_ARM18_DEV_BUF,XBOT_ARM18_DEV_PARA);			//发送机械臂数据
		////////////////////////////////////////////发送底盘3个电机控制指令/////////////////////////////////
// 		XbotMotorDrvTxAllCmd(&USART_MOTION_CTRL, &XBOT_MOTION_DEV_BUF,			//发送运动底盘数据
// 							XBOT_MOTION_DEV_PARA);

// 		AngtronAbsEncDealRxdData(&USART_ENCODE_CTRL,&XBOT_ENCODE_DEV_DATA);		//处理位置编码器数据

		STM32_ENABLE_TIM3;
	}
 
}

//100ms触发一次
/******************************  TIM4_IRQHandler *************************************/
// void TIM4_IRQHandler(void)
// {
// 	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
// 	{
// 		TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);

// 		STM32_DISABLE_TIM4; 	
// 		////////////////////////////////////////////发送机械与电源控制板指令/////////////////////////////////

// 		AngtronAbsEncTXD(&USART_ENCODE_CTRL,&XBOT_ENCODE_DEV_DATA);			//发送位置编码器数据
// 				

// 		
// 		STM32_ENABLE_TIM4;
// 		
// 	}
//  
// }
void TIM4_IRQHandler(void)
{


	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);
		STM32_DISABLE_TIM4;
// 		if(index!=0)
// 		{
// 			for(i=0;i<index;i++)
// 			{
// 					while (!USART_TXBuffer_PutByte(&USART_data_4, aaa[i]));
// 			}
// 			index=0;
// 		}
// 		USART_TXBuffer_PutByte(&USART_data_4, 0x32);
// 		while (!USART_TXBuffer_PutByte(&USART_data_4, 0x32));	
// 		SysTick_DelayMs(1000);
// 		while (!USART_TXBuffer_PutByte(&USART_data_4, 0x31));	
// 		SysTick_DelayMs(1000);
		
// 		while (!USART_TXBuffer_PutByte(&USART_data_4, 0x12));	SysTick_DelayMs(1);
// 		while (!USART_TXBuffer_PutByte(&USART_data_4, 0x22));	SysTick_DelayMs(1);
// 		while (!USART_TXBuffer_PutByte(&USART_data_4, 0x32));	SysTick_DelayMs(1);
// 		while (!USART_TXBuffer_PutByte(&USART_data_4, 0x42));	SysTick_DelayMs(1);
// 		while (!USART_TXBuffer_PutByte(&USART_data_4, 0x52));	SysTick_DelayMs(1);
// 		while (!USART_TXBuffer_PutByte(&USART_data_4, 0x62));	SysTick_DelayMs(1);
// 		while (!USART_TXBuffer_PutByte(&USART_data_4, 0x72));	SysTick_DelayMs(1);

		STM32_ENABLE_TIM4;
	}	
}	
