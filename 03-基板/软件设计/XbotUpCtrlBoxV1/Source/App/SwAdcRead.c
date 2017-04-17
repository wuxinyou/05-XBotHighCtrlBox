
/**************************************************************************
说明：采集电源开关，电源开关是自复位开关。所以需要添加一个GPIO用来保存开关状态
作者：吴新有
日期：20170417
备注：按下第一次开机，按下第二次关机，
	长按开机，长按关机

**************************************************************************/

#include "SwAdcRead.h"

#define BAT_ADC_BUF_LEN	 30

#define BAT_VALUE_MAX	255
#define BAT_VALUE_MIN	1
#define BAT_ADC_RANGE	0x400
#define BAT_VALUE_RANGE	255

uint8_t SW_GetValue(void)
{
	uint8_t SWAdcValue=0;

	SWAdcValue=SWGetAdc()*33>>12;   //这里理论最大0.65V，也就是6.5=6
	return SWAdcValue;
}

void SW_DealAdcValue(void)
{
	static uint8_t SW_PreValue=0xff;   //保存上一次SW的值
	static uint8_t SW_PressCount=0; //SW按下计数
	static uint8_t SW_PowerOffFlag=0;
	
	uint8_t SW_ValueTemp=SW_GetValue();
	
	if(SW_PreValue>SW_ValueTemp+2 || SW_PreValue<SW_ValueTemp-2) 
  //if(SW_PreValue != SW_ValueTemp) 
	{
		SW_PreValue=SW_ValueTemp;
		if(SW_PreValue>2)      //说明SW按下
		{
			SW_PressCount++;
			if(SW_PressCount>=2)  //第二次按下SW
			{
				SW_PowerOffFlag=1;
				//POWCTRL_OFF;        //关闭电源，关机
				LED2_ON;
			}
			else if(SW_PressCount>=1)  //第一次按下SW
			{
				POWCTRL_ON;         //打开电源，开机
			}
		}
		
	}
	
	// 长按关机
	if(SW_ValueTemp>2 && SW_PowerOffFlag>0)
	{
			SW_PowerOffFlag++;
		if(SW_PowerOffFlag>10)
		{
			POWCTRL_OFF;        //关闭电源，关机
		}
	}
	else
	{
		SW_PowerOffFlag=0;
	}
	
}





