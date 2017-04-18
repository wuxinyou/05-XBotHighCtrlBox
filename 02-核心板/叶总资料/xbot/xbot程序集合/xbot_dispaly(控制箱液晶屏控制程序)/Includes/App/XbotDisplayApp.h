/**
  ******************************************************************************
	*文件：XbotApp.h
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：控制Xbot的主类的头文件
	*备注：类成员中有很多静态成员变量，为的是回调函数使用，如果有必要的话，可以修改调用方式设为普通的成员
	*
  ******************************************************************************  
	*/ 
	
/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _XBOT_DISPLAY_APP_H
#define _XBOT_DISPLAY_APP_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "SerialPort.h"
#include "LCDdisplay.h"
#include "TerminalControl.h"
#include "Timer.h"
#include "LEDLighter.h"
#include "Key.h"
#include "STM32_SysTick.h"

/* 类型定义 --------------------------------------------------------------------*/

/* 宏定义-----------------------------------------------------------------------*/ 


class XbotDisplayApp
{
public:
	XbotDisplayApp();
	~XbotDisplayApp();
	void runOnTime2();												//运行在定时器TIM2中的函数
	void runOnTime3();												//运行在定时器TIM3中的函数
	void runOnTime4();												//运行在定时器TIM4中的函数
	void initLCD();

private:
	LCDdisplay *LCDManager;										//控制液晶屏
	TerminalControl *terminalManager; 				//和XBOT控制箱交互
	SerialPort *terminalPort;									//和终端（XBOT控制箱）通信的串口
	SerialPort *lcdPort;											//和LCD液晶屏通信的串口
	Timer *t1;																//定时器1
	Timer *t2;																//定时器2
	Timer *t3;															//定时器3
	LEDLighter *led_1;
	LEDLighter *led_2;
	Key *key_M;
	Key *key_A;
	Key *key_B;
	Key *key_C;
	Key *key_D;
	int8_t keysValue;													//按键的值
	uint8_t maskKeysValue;										//发送到终端的按键值
	uint8_t workMode;													//工作模式
	uint8_t debugMode;												//调试模式
	int8_t interfaceIndex;										//界面编号
	uint8_t *error;														//错误代号
	uint8_t errorStatus;											//错误状态
	uint8_t pageID;														//界面图片的ID
	uint8_t languagePosition;									//语言的图片偏移位置 
	bool enabledShowError;										//信息报告显示与否的标志
private:
	bool updateLCDdata();
	uint8_t checkError();											//检测错误信息
	void disOneError(uint8_t,uint8_t,uint8_t);//显示具体的信息
	void disErrorIcon();											//显示错误图标
	bool disError(bool);											//显示错误信息

	void setWorkMode(uint8_t);

	void setMainButtonPress(uint8_t button);	//设置主界面按键按下
	void setMainButtonNormal(uint8_t button);	//设置主界面按键正常（弹起状态）
	void setButtonPress(uint8_t button);			//设置普通界面按键按下
	void setButtonChecked(uint8_t button);		//设置普通界面按键选中
	void setButtonNormal(uint8_t button);			//设置普通界面按键正常（弹起状态）
	void disSwingArmWorkMode(bool);						//设置摆臂模式的图片
	void disArmWorkMode(bool);								//设置手臂模式的图片
	void disOtherWorkMode(bool);							//设置其他模式的图片

	void disPageStart();											//显示启动界面
	void disPageMain(int8_t,int8_t,bool);			//显示主菜单界面
  void disPageAngle(int8_t,int8_t,bool);		//显示角度界面
	void disPageSwingArmCtrl(int8_t,int8_t);	//显示摆臂控制界面
	void disPageArmCtrl(int8_t,int8_t);				//显示手臂控制界面
	void disPageOtherCtrl(int8_t,int8_t);			//显示其他控制界面
	void disPageDubugCtrl(int8_t,int8_t);			//显示应急控制界面
	bool disPageWeaponCtrl();									//显示武器控制界面
// 	void disPageWarning();										//显示信息报告界面

};
#endif /* _XBOT_APP_H */









