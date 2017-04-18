/**
  ******************************************************************************
	*文件：XbotDisPlayApp.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：控制Xbot的主类的实现文件
	*备注：
	*
  ******************************************************************************  
	*/ 

/* 头文件包含 ------------------------------------------------------------------*/
#include "XbotDisplayApp.h"
#ifdef __cplusplus
 extern "C" {
#endif
#include <stdlib.h>
// #include <math.h>								//数学函数库
#ifdef __cplusplus
 }
#endif

/* 类型定义 --------------------------------------------------------------------*/

/* 宏定义-----------------------------------------------------------------------*/ 

//绝对值宏
// #define ABS(X)			((X)>0?(X):(-(X)))
// //二者绝对值谁大谁小宏
// #define MAX(X,Y)		((ABS(X))>(ABS(Y))?(ABS(X)):(ABS(Y)))
// #define MIN(X,Y)		((ABS(X))<(ABS(Y))?(ABS(X)):(ABS(Y)))

#define LCD_PORT_NUM 					2
#define LCD_PORT_BAUD					38400

#define TERMINAL_PORT_NUM     1
#define TERMINAL_PORT_BAUD    19200

#define KM 		0
#define KA 		1
#define KB 		2
#define KC 		3
#define KD 		4
#define KABD 	5
#define KNULL -1

#define KEYINDEX_MAX 3
#define KEYINDEX_ABD_MAX 150

#define MODE_NULL						0x00//空模式
#define MODE_SHOULDER_A 		0X20//支臂抬起
#define MODE_SHOULDER_B			0X40//支臂支地
#define MODE_SHOULDER_C			0X60//支臂收起
#define MODE_SHOULDER_D 		0X80//支臂水平
#define MODE_ARM_CA					0XA4//机械臂半展开
#define MODE_ARM_CB					0XA8//机械臂前抓取
#define MODE_ARM_CC					0X6C//机械臂完全收起
#define MODE_ARM_DC					0XB0//机械臂前观测
#define MODE_ARM_DD					0XB4//机械臂全展开
#define MODE_ARM_3D					0X18//机械臂进入3D控制

#define MODE_CAMERA_A       0X02//放线
#define MODE_CAMERA_B				0X01//收线

#define DEBUF_NULL					0X00//无调试
#define DEBUF_CANCEL				0X8A//取消限位
#define DEBUF_RESET					0X8B//重设零位

#define STARTPAGENUM 							(1+languagePosition)
#define MAINPAGENUM 							(2+languagePosition)
#define ANGLEPAGENUM							(3+languagePosition)
#define SWINGARMCTRLPAGENUM				(4+languagePosition)
#define ARMCTRLPAGENUM						(5+languagePosition)
#define OTHERCTRLPAGENUM1					(6+languagePosition)
#define DEBUGCTRLPAGENUM					(7+languagePosition)


#define MAINPAGENUM_1							(8+languagePosition)
#define OTHERCTRLPAGENUM					(9+languagePosition)

#define SWINGARMCTRLPAGENUM_1			(10+languagePosition)
#define ARMCTRLPAGENUM_1					(11+languagePosition)
#define OTHERCTRLPAGENUM_1				(12+languagePosition)
#define OTHERCTRLPAGENUM1_1				(13+languagePosition)
#define DEBUGCTRLPAGENUM_1				(14+languagePosition)

#define MAINBACKPAGENUM						(15+languagePosition)
#define BACKPAGENUM								(16+languagePosition)
#define BACKPAGENUM_1							(10+languagePosition)

#define ERRORBACKPAGENUM					(17+languagePosition)
#define ERRORBACKPAGENUM_1				(18+languagePosition)
#define WEAPONCTRLPAGENUM					(19+languagePosition)
#define WEAPONCTRLPAGENUM_1				(20+languagePosition)
#define ERRORSTRAT								(21+languagePosition)

#define MAINBUTTON_M 0
#define MAINBUTTON_A 1
#define MAINBUTTON_B 2
#define MAINBUTTON_C 3
#define MAINBUTTON_D 4

#define BUTTON_M 		 0
#define BUTTON_A 		 1
#define BUTTON_B 		 2
#define BUTTON_C 		 3
#define BUTTON_D 		 4


#define ENGLISH 37
#define CHINESE 0

//版本控制 如果定义了ABROAD，则使用国外版本，默认语言为英文，并且语言区不保存;否则为国内版本，默认语言为中文，并且保存语言区
// #define ABROAD

#ifdef ABROAD
#define DEFAULTLANGUGE ENGLISH
#else
#define DEFAULTLANGUGE CHINESE
#endif

//构造函数
XbotDisplayApp::XbotDisplayApp()
{
	workMode=MODE_NULL;
	debugMode=DEBUF_NULL;
	keysValue=-1;
	maskKeysValue=0;
	interfaceIndex=-1;
	error = new uint8_t[4];
	error[0]=0;
	error[1]=0;
	error[2]=0;
	error[3]=0;
	errorStatus=0;																															//错误状态
	pageID=0;
	enabledShowError=true;																											//默认显示信息报告
	languagePosition=DEFAULTLANGUGE;
	led_1=new LEDLighter(GPIOB,GPIO_Pin_13);
	terminalPort=new SerialPort(TERMINAL_PORT_NUM,TERMINAL_PORT_BAUD);					//和终端（XBOT控制箱）通信的串口
	lcdPort=new SerialPort(LCD_PORT_NUM,LCD_PORT_BAUD);													//和LCD液晶屏通信的串口
	
	key_M=new Key(GPIOB,GPIO_Pin_0);
	key_A=new Key(GPIOA,GPIO_Pin_7);
	key_B=new Key(GPIOA,GPIO_Pin_6);
	key_C=new Key(GPIOA,GPIO_Pin_5);
	key_D=new Key(GPIOA,GPIO_Pin_4);

	LCDManager=new LCDdisplay(lcdPort);															//控制液晶屏
	terminalManager=new TerminalControl(terminalPort);							//和XBOT控制箱交互

	led_1->setLightOn();
	t1=new Timer(TIM2);
	t2=new Timer(TIM3);
	t3=new Timer(TIM4);
	
	
	t1->setTimeOut(20);
	t1->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM2_SubPriority);

	t2->setTimeOut(2);
	t2->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM3_SubPriority);
	

	t3->setTimeOut(10);
	t3->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM4_SubPriority);
}

XbotDisplayApp::~XbotDisplayApp()
{
	t1->stop();
	t2->stop();
	t3->stop();
	terminalPort->close();
	lcdPort->close();
	delete terminalPort;					//和终端（XBOT控制箱）通信的串口
	delete lcdPort;							//和LCD液晶屏通信的串口
	delete t1;												//定时器1
	delete t2;												//定时器2
	delete t3;												//定时器3
	delete led_1;
// 	delete led_2;
	delete key_M;
	delete key_A;
	delete key_B;
	delete key_C;
	delete key_D;
}
void XbotDisplayApp::initLCD()
{
	lcdPort->open();
	LCDManager-> SetColor(0x07E0,0x00);
	SysTick_DelayMs(80);
	LCDManager->ShowPic(0);
// 	disPageStart();											//显示启动界面
	SysTick_DelayMs(80);
	terminalPort->open();
//打开定时器	
#ifndef ABROAD	
	t3->start();
	LCDManager->readLanguageBuf();//读取语言
#endif	
	SysTick_DelayMs(1500);
	t1->start();
	t2->start();
#ifndef ABROAD
	t3->stop();
#endif	
}
void XbotDisplayApp::setWorkMode(uint8_t value)
{
	if(workMode==value)
		workMode=MODE_NULL;
	else
		workMode=value;
}

void XbotDisplayApp::setMainButtonPress(uint8_t button)		//设置主界面按键按下
{
	int position=34+button*38;
	LCDManager->CutPicAndShow(MAINBACKPAGENUM,4,position,30,25,4,position);
}
void XbotDisplayApp::setMainButtonNormal(uint8_t button)	//设置主界面按键正常（弹起状态）
{
	int position=34+button*38;
	LCDManager->CutPicAndShow(MAINPAGENUM,4,position,30,25,4,position);
}


void XbotDisplayApp::setButtonPress(uint8_t button)				//设置普通界面按键按下
{
	int position=31+button*38;
	LCDManager->CutPicAndShow(BACKPAGENUM,1,position,46,31,1,position);
}
void XbotDisplayApp::setButtonChecked(uint8_t button)			//设置普通界面按键选中
{
	int position=33+button*38;
	LCDManager->CutPicAndShow(BACKPAGENUM_1,1,position,46,31,1,position);
}
void XbotDisplayApp::setButtonNormal(uint8_t button)			//设置普通界面按键正常（弹起状态）
{
	int position=33+button*38;
	LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,1,position,46,31,1,position);
}

// 		case 2:

// 			break;
// 		case 3:
// 			if(workMode==MODE_ARM_CA)
// 			{
// 					LCDManager->updateKeyPic(1);
// 			}
// 			else if(workMode==MODE_ARM_CB)
// 			{
// 					LCDManager->updateKeyPic(2);
// 			}
// 			else if(workMode==MODE_ARM_CC)
// 			{
// 					LCDManager->updateKeyPic(3);
// 			}
// 			else if(workMode==MODE_ARM_3D)
// 			{
// 					LCDManager->updateKeyPic(4);
// 			}
// 			else
// 			{
// 					LCDManager->updateKeyPic(0);
// 			}
// 			break;
// 		case 4:
// 			if(workMode==MODE_CAMERA_A)
// 			{
// 					LCDManager->updateKeyPic(1);
// 			}
// 			else if(workMode==MODE_CAMERA_B)
// 			{
// 					LCDManager->updateKeyPic(2);
// 			}
// 			else if(workMode==MODE_ARM_DC)
// 			{
// 					LCDManager->updateKeyPic(3);
// 			}
// 			else if(workMode==MODE_ARM_DD)
// 			{
// 					LCDManager->updateKeyPic(4);
// 			}
// 			else
// 			{
// 					LCDManager->updateKeyPic(0);
// 			}
// 			break;


void XbotDisplayApp::disSwingArmWorkMode(bool staflag)															//设置摆臂模式的图片
{
	static uint8_t backWorkMode=0;
	if(staflag)//强制显示
	{
		if(workMode==MODE_SHOULDER_A)
		{
			LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,62,33,116,38,62,33);
		}
		else if(workMode==MODE_SHOULDER_B)
		{
			LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,191,33,116,38,191,33);
		}
		else if(workMode==MODE_SHOULDER_C)
		{
			LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,62,130,116,38,62,130);
		}
		else if(workMode==MODE_SHOULDER_D)
		{
			LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,191,130,116,38,191,130);
		}
		backWorkMode=workMode;
	}
	else
	{
		if(backWorkMode!=workMode)//模式有变化
		{
			//
			if(backWorkMode==MODE_SHOULDER_A)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,62,33,116,38,62,33);
			}
			else if(backWorkMode==MODE_SHOULDER_B)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,191,33,116,38,191,33);
			}
			else if(backWorkMode==MODE_SHOULDER_C)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,62,130,116,38,62,130);
			}
			else if(backWorkMode==MODE_SHOULDER_D)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,191,130,116,38,191,130);
			}
			if(workMode==MODE_SHOULDER_A)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,62,33,116,38,62,33);
			}
			else if(workMode==MODE_SHOULDER_B)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,191,33,116,38,191,33);
			}
			else if(workMode==MODE_SHOULDER_C)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,62,130,116,38,62,130);
			}
			else if(workMode==MODE_SHOULDER_D)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,191,130,116,38,191,130);
			}
			backWorkMode=workMode;
		}
	}
}

void XbotDisplayApp::disArmWorkMode(bool staflag)								//设置手臂模式的图片
{
	static uint8_t backWorkMode=0;
	if(staflag)//强制显示
	{
		if(workMode==MODE_ARM_CA)
		{
			LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,56,32,127,21,56,32);
		}
		else if(workMode==MODE_ARM_CB)
		{
			LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,185,32,127,21,185,32);
		}
		else if(workMode==MODE_ARM_CC)
		{
			LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,56,131,127,21,56,131);
		}
		else if(workMode==MODE_ARM_3D)
		{
			LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,185,131,127,21,185,131);
		}
		backWorkMode=workMode;
	}
	else
	{
		if(backWorkMode!=workMode)//模式有变化
		{
			//
			if(backWorkMode==MODE_ARM_CA)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,56,32,127,21,56,32);
			}
			else if(backWorkMode==MODE_ARM_CB)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,185,32,127,21,185,32);
			}
			else if(backWorkMode==MODE_ARM_CC)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,56,131,127,21,56,131);
			}
			else if(backWorkMode==MODE_ARM_3D)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,185,131,127,21,185,131);
			}
			
			if(workMode==MODE_ARM_CA)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,56,32,127,21,56,32);
			}
			else if(workMode==MODE_ARM_CB)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,185,32,127,21,185,32);
			}
			else if(workMode==MODE_ARM_CC)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,56,131,127,21,56,131);
			}
			else if(workMode==MODE_ARM_3D)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,185,131,127,21,185,131);
			}
			backWorkMode=workMode;
		}
	}
}

void XbotDisplayApp::disOtherWorkMode(bool staflag)							//设置其他模式的图片
{
	static uint8_t backWorkMode=0;
	if(staflag)//强制显示
	{
		if(workMode==MODE_CAMERA_A)
		{
			if(LCDManager->WireLength==0)
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,56,32,127,21,56,32);
			else
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1_1,56,32,127,21,56,32);
		}
		else if(workMode==MODE_CAMERA_B)
		{
			if(LCDManager->WireLength==0)
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,185,32,127,21,185,32);
			else
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1_1,185,32,127,21,185,32);
		}
		else if(workMode==MODE_ARM_DC)
		{
			LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,57,108,143,23,57,108);
		}
		else if(workMode==MODE_ARM_DD)
		{
			LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,207,108,102,23,207,108);
		}
		backWorkMode=workMode;
	}
	else
	{
		if(backWorkMode!=workMode)//模式有变化
		{
			//
			if(backWorkMode==MODE_CAMERA_A)
			{
				if(LCDManager->WireLength==0)
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM,56,32,127,21,56,32);
				else
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1,56,32,127,21,56,32);
			}
			else if(backWorkMode==MODE_CAMERA_B)
			{
				if(LCDManager->WireLength==0)
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM,185,32,127,21,185,32);
				else
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1,185,32,127,21,185,32);
			}
			else if(backWorkMode==MODE_ARM_DC)
			{
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM,57,108,143,23,57,108);
			}
			else if(backWorkMode==MODE_ARM_DD)
			{
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM,207,108,102,23,207,108);
			}
			///////////////////////////
			if(workMode==MODE_CAMERA_A)
			{
				if(LCDManager->WireLength==0)
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,56,32,127,21,56,32);
				else
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1_1,56,32,127,21,56,32);
			}
			else if(workMode==MODE_CAMERA_B)
			{
				if(LCDManager->WireLength==0)
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,185,32,127,21,185,32);
				else
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1_1,185,32,127,21,185,32);
			}
			else if(workMode==MODE_ARM_DC)
			{
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,57,108,143,23,57,108);
			}
			else if(workMode==MODE_ARM_DD)
			{
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,207,108,102,23,207,108);
			}
			backWorkMode=workMode;
		}
	}
}

/**
  * 功  能：更新LCD显示的数据
  * 参  数：无
  * 返回值：无
  * 备  注：	错误状态注释
	*				XBOT_LcdData[16] 电源控制板 20
	*				XBOT_LcdData[17] 灯摄像头等 21
	*				XBOT_LcdData[18]	大臂旋转  22
	*				XBOT_LcdData[19] 大臂俯仰		23
	*				XBOT_LcdData[20] 线缆盘			24
	*				XBOT_LcdData[21] 支臂码盘		25
	*				XBOT_LcdData[22] 小臂俯仰		26
	*				XBOT_LcdData[23] 手腕俯仰		27
	*				XBOT_LcdData[24] 左电机			28
	*				XBOT_LcdData[25] 右电机			29
	*				XBOT_LcdData[26] 手腕旋转		30
	*				XBOT_LcdData[27] 云台俯仰		31
	*				XBOT_LcdData[28] 支臂电机		32
	*				XBOT_LcdData[29] 底座相机		33
	*				XBOT_LcdData[30] 云台旋转		34
	*				XBOT_LcdData[31] 手抓夹持		35
	*/
bool XbotDisplayApp::updateLCDdata()
{
	uint8_t *temReciveData=terminalManager->getReciveData();
	uint8_t index=temReciveData[1]&0x03;
	
	LCDManager->LeftCtrlSpeed =(int)((signed char)temReciveData[2]);
	LCDManager->RightCtrlSpeed=(int)((signed char)temReciveData[3]);
	LCDManager->XBOT_LcdData[index*4]=temReciveData[4];
	LCDManager->XBOT_LcdData[index*4+1]=temReciveData[5];
	LCDManager->XBOT_LcdData[index*4+2]=temReciveData[6];
	LCDManager->XBOT_LcdData[index*4+3]=temReciveData[7];//电池电压 3 7 11 15
	LCDManager->XBOT_LcdData[16+index*4]=(temReciveData[8]>>4)&0x0f;
	LCDManager->XBOT_LcdData[17+index*4]=temReciveData[8]&0x0f;
	LCDManager->XBOT_LcdData[18+index*4]=(temReciveData[9]>>4)&0x0f;
	LCDManager->XBOT_LcdData[19+index*4]=temReciveData[9]&0x0f;
	
	
	if(LCDManager->XBOT_LcdData[3]>125)//电池电量满
		LCDManager->battery_1=15;
	else if(LCDManager->XBOT_LcdData[3]>110)//电池电压在22伏以上
		LCDManager->battery_1=LCDManager->XBOT_LcdData[3]-110;
	else
		LCDManager->battery_1=0;
	
	if(LCDManager->XBOT_LcdData[7]>125)//电池电量满
		LCDManager->battery_2=15;
	else if(LCDManager->XBOT_LcdData[7]>110)//电池电压在22伏以上
		LCDManager->battery_2=LCDManager->XBOT_LcdData[7]-110;
	else
		LCDManager->battery_2=0;
	
	if(LCDManager->XBOT_LcdData[11]>125)//电池电量满
		LCDManager->battery_3=15;
	else if(LCDManager->XBOT_LcdData[11]>110)//电池电压在22伏以上
		LCDManager->battery_3=LCDManager->XBOT_LcdData[11]-110;
	else
		LCDManager->battery_3=0;
	
	if(LCDManager->XBOT_LcdData[15]>125)//电池电量满
		LCDManager->battery_4=15;
	else if(LCDManager->XBOT_LcdData[15]>110)//电池电压在22伏以上
		LCDManager->battery_4=LCDManager->XBOT_LcdData[15]-110;
	else
		LCDManager->battery_4=0;
	
	if(index==0x00)	
		LCDManager->WireLength=temReciveData[10];			  			//线缆盘剩余线长
	else if(index==0x01)	
		LCDManager->signal=(temReciveData[10]&0x07);			  					//信号强度
	else if(index==0x02)	
		LCDManager->LeftMotorSpeed=(int)((signed char)temReciveData[10]);				//真实的速度
	else if(index==0x03)	
		LCDManager->RightMotorSpeed=-(int)((signed char)temReciveData[10]);				//真实的速度
	
	LCDManager->fireFlag=temReciveData[11];									//水炮状态
	if(index==3)//检测到一个完整的周期400MS
		return true;
	else
		return false;
}

/**
  * 功  能：检测错误信息
  * 参  数：无
  * 返回值：
  * 		0：上次无，当次无
  *  		1：上次有，当次无
  *  		bit0-bit1=2：上次无，当次有 bit6-bit7:信息个数
  *  		bit0-bit1=3：上次有，当次有 bit6-bit7:信息个数 bit5-bit2：变化的位置
  */
uint8_t XbotDisplayApp::checkError()											//检测错误信息
{
	static bool backErrorFlag=false;
	static uint8_t backError[4]={0,0,0,0};
	bool errorFlag=false;	
	uint8_t index=0;	
	uint8_t backErrorStatus=0;																					//错误状态
	error[0]=0;
	error[1]=0;
	error[2]=0;
	error[3]=0;
	if(!enabledShowError)//不显示信息报告
	{
		errorFlag=false;
	}
	else
	{
		for(int i=16;i<32;i++)//检测有无信息
		{
			if(LCDManager->XBOT_LcdData[i]!=0)
			{
				errorFlag=true;
				break;
			}
		}
	}
	if(errorFlag)//检测错误号
	{
		for(int i=16;i<32;i++)//检测错误信息 0x05 0x06 0x07 //堵转和温度过高
		{
			if(index>3)
				break;
			if(LCDManager->XBOT_LcdData[i]>0x0a)
			{
				error[index]=((i-16)<<4)|((LCDManager->XBOT_LcdData[i]-0x06)&0x0f);
				index++;
			}
		}
		for(int i=16;i<32;i++)//检测警告信息 0X02 0x03 0x04
		{
			if(index>3)
				break;
			if(LCDManager->XBOT_LcdData[i]==0x08||LCDManager->XBOT_LcdData[i]==0x09||LCDManager->XBOT_LcdData[i]==0x0a)
			{
				error[index]=((i-16)<<4)|((LCDManager->XBOT_LcdData[i]-0x06)&0x0f);
				index++;
			}
		}
		for(int i=16;i<32;i++)//检测提示信息 关节干涉 0X01 
		{
			if(index>3)
				break;
			if(LCDManager->XBOT_LcdData[i]>0x00&&LCDManager->XBOT_LcdData[i]<0x08)
			{
				error[index]=((i-16)<<4)|0x01;
				index++;
			}
		}
	}
	if(backErrorFlag==false&&errorFlag==false)				//上次无，当次无
	{
		backError[0]=0;
		backError[1]=0;
		backError[2]=0;
		backError[3]=0;
		backErrorStatus=0;
	}
	else if(backErrorFlag==true&&errorFlag==false)		//上次有，当次无
	{
		backErrorFlag=false;
		backError[0]=0;
		backError[1]=0;
		backError[2]=0;
		backError[3]=0;
		backErrorStatus=1;
	}
	else if(backErrorFlag==false&&errorFlag==true)		//上次无，当次有
	{
		backErrorFlag=true;
		backError[0]=error[0];
		backError[1]=error[1];
		backError[2]=error[2];
		backError[3]=error[3];
		backErrorStatus=2;
		backErrorStatus|=((index-1)<<6);								//显示的个数
	}
	else if(backErrorFlag==true&&errorFlag==true)			//上次有，当次有
	{
		if(backError[0]!=error[0])
			backErrorStatus|=(0x20);
		if(backError[1]!=error[1])
			backErrorStatus|=(0x10);
		if(backError[2]!=error[2])
			backErrorStatus|=(0x08);
		if(backError[3]!=error[3])
			backErrorStatus|=(0x04);
		
		backErrorStatus|=0x03;
		backErrorStatus|=((index-1)<<6); 								//显示的个数
		backError[0]=error[0];
		backError[1]=error[1];
		backError[2]=error[2];
		backError[3]=error[3];
	}
	return backErrorStatus;
}
/**
  * 功  能：显示单条错误信息
  * 参  数：
  * 	amount:		错误总数
  * 	position:	显示的位置
  * 	error:		错误信息
  * 返回值：无
  */

void XbotDisplayApp::disOneError(uint8_t amount,uint8_t position,uint8_t error)						//显示具体的信息
{
	if(error==0)
	{
		return;
	}
	int8_t errorID=((error&0xf0)>>4)+ERRORSTRAT; 				//错误所在的设备图片ID 20-35 

	int8_t errorType=error&0x0f;												//错误所在的位置 1 2 3 4 5 6 7共七种类型
	if(errorType>7)																			//错误的编号 类型不合法
	{
		errorID=36;
		errorType=1;
	}
	if(amount==1)
		LCDManager->CutPicAndShow(errorID,71,19+27*errorType,234,22,71,105);
	else if(amount==2)
		LCDManager->CutPicAndShow(errorID,71,19+27*errorType,234,22,71,88+53*position);
	else if(amount==3)
		LCDManager->CutPicAndShow(errorID,71,19+27*errorType,234,22,71,73+41*position);
	else if(amount==4)
		LCDManager->CutPicAndShow(errorID,71,19+27*errorType,234,22,71,73+27*position);
}
/**
  * 功  能：闪烁显示错误图标
  * 参  数：无
  * 返回值：无
  */
void XbotDisplayApp::disErrorIcon()											//显示错误图标
{
	static uint16_t Timer=0;
	if(Timer==0)
	{
		LCDManager->CutPicAndShow(ERRORBACKPAGENUM,112,33,158,28,112,33);
		LCDManager->CutPicAndShow(ERRORBACKPAGENUM,171,193,136,25,171,193);
	}
	else if(Timer==0xff)
	{
		LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,112,33,158,28,112,33);
		LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,171,193,136,25,171,193);
	}
	Timer++;
	Timer&=0x01ff;
}


/**
  * 功  能：显示错误信息
  * 参  数：
  * 	true:强制显示
  * 	false:非强制显示
  * 返回值：
  * 	true:		有显示
  * 	false:	无显示
  */
bool XbotDisplayApp::disError(bool staflag)							//显示错误信息
{
	static uint8_t backErrorStatus=0;
	errorStatus=checkError();
	//先查看有无信息显示
	int8_t errorNum=0;	//错误个数
	if(errorStatus==0)	//上次无，当次无
	{
		backErrorStatus=errorStatus;
		return false;
	}
	if(staflag)//强制显示
	{
		//先切割显示背景
		backErrorStatus=errorStatus;
		if(errorStatus>1)//当次有
		{
			if(interfaceIndex==1)			//角度显示界面中
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,252,195,62,27); //显示背景
			else if(interfaceIndex==0)//主菜单中
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,257,195,62,27); //显示背景
			else 											//其他界面中
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,50,27,268,195,50,27); //显示背景
			errorNum=((errorStatus&0xc0)>>6)+1;//错误个数  1 2 3 4 
			for(int i=0;i<errorNum;i++)
			{
				disOneError(errorNum,i,error[i]);//显示具体的信息
			}
			return true;
		}
		else
			return false;
	}
	else //不强制刷新，根据上次的结果显示当次的内容
	{
		if(errorStatus==1)//上次有，当次无 ,还原图形
		{
			backErrorStatus=errorStatus;
			if(interfaceIndex==1)			//角度显示界面中
				LCDManager->CutPicAndShow(pageID,62,27,252,195,62,27); //显示背景
			else if(interfaceIndex==0)//主菜单中
				LCDManager->CutPicAndShow(pageID,62,27,257,195,62,27); //显示背景
			else 											//其他界面中
				LCDManager->CutPicAndShow(pageID,50,27,268,195,50,27); //显示背景
			return false;
		}
		else if((errorStatus&0x03)==2)//上次无，当次有
		{
			backErrorStatus=errorStatus;
			if(interfaceIndex==1)			//角度显示界面中
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,252,195,62,27); //显示背景
			else if(interfaceIndex==0)//主菜单中
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,257,195,62,27); //显示背景
			else 											//其他界面中
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,50,27,268,195,50,27); //显示背景
			errorNum=((errorStatus&0xc0)>>6)+1;//错误个数
			for(int i=0;i<errorNum;i++)
			{
				disOneError(errorNum,i,error[i]);//显示具体的信息
			}
			disErrorIcon();//闪烁图标
			return true;
		}
		else //上次有，当次有
		{
// 			if(((errorStatus&0x10)&&(error[1]==0))||((errorStatus&0x08)&&(error[2]==0))||((errorStatus&0x04)&&(error[3]==0)))//检测到显示个数有变化,只能检测到由多变少
			if((errorStatus&0xc0)!=(backErrorStatus&0xc0))	//检测个数有变化
			{
			if(interfaceIndex==1)			//角度显示界面中
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,252,195,62,27); //显示背景
			else if(interfaceIndex==0)//主菜单中
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,257,195,62,27); //显示背景
			else 											//其他界面中
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,50,27,268,195,50,27); //显示背景
				errorNum=((errorStatus&0xc0)>>6)+1;//错误个数
				for(int i=0;i<errorNum;i++)
				{
					disOneError(errorNum,i,error[i]);//显示具体的信息
				}
				disErrorIcon();//闪烁图标
				backErrorStatus=errorStatus;
				return true;
			}
			else//个数没有变化
			{
				if(errorStatus!=backErrorStatus)
				{
					errorNum=((errorStatus&0xc0)>>6)+1;//错误个数
					for(int i=0;i<errorNum;i++)
					{
						if((errorStatus&(0x20>>i))!=0)					 //检测错误类型有无变化
							disOneError(errorNum,i,error[i]);//显示具体的信息
					}
				}
// 				errorNum=((errorStatus&0xc0)>>6)+1;//错误个数
// 				for(int i=0;i<errorNum;i++)
// 				{
// 					if((errorStatus&(0x20>>i))!=0)					 //检测错误类型有无变化
// 						disOneError(errorNum,i,error[i]);//显示具体的信息
// 				}
				disErrorIcon();//闪烁图标
				backErrorStatus=errorStatus;
				return true;
			}
		}
	}
}
/**
  * 功  能：显示启动界面
  * 参  数：无
  * 返回值：无
  */
void XbotDisplayApp::disPageStart()											//显示启动界面
{
	static uint16_t timer=0;
	//检测语言
	
	if(LCDManager->fireFlag!=0x00&&timer<800)
	{
		timer++;
		return;
	}
	if(timer==0)
	{
		LCDManager->ShowPic(STARTPAGENUM);									
		timer++;
	}
	else if(timer<500)																		//延时1.5秒 等待信息收集完成
	{
		timer++;
		LCDManager->movePic(0x61,38,144,279,148,1);
	}
	else if(timer<800)
	{
		timer++;
	}		
	else if(timer==800)
	{
		interfaceIndex=0;																		//显示主菜单界面
		timer++;
	}
}

/**
  * 功  能：显示主菜单界面
  * 参  数：
	* key:			本次按键的值
	* backKey:	上次按键的值
  * 返回值：无
  */
void XbotDisplayApp::disPageMain(int8_t key,int8_t backKey,bool updateFlag)					//显示主菜单界面
{
	static bool firstDis=false;
	static uint8_t backWireLength=0;
	if(interfaceIndex!=0)
		return;
	//信息报告处理
	if(!firstDis)//第一次显示
	{
		firstDis=true;
		if(LCDManager->WireLength==0)//无线或者普通线缆控制
		{
			pageID=MAINPAGENUM;
			LCDManager->ShowPic(pageID);
			if(!disError(true))//强制显示错误信息，返回fasle代表物错误内容
			{
				LCDManager->showVoltageAndSpeed();
				LCDManager->ShowCtrlSpeed(true);
			}
		}
		else 
		{
			pageID=MAINPAGENUM_1;
			LCDManager->ShowPic(pageID);
			if(!disError(true))//强制显示错误信息，返回fasle代表物错误内容
			{
				LCDManager->ShowCtrlSpeed_1(true);
				LCDManager->showVoltageAndSpeed_1();
			}
		}
		LCDManager->ShowBattery(true);				//显示电池电量
		LCDManager->ShowSignal(true);					//显示信号强度
		backWireLength=LCDManager->WireLength;
// 		return;
	}
	switch(keysValue) //检测按键
	{
		case -1://按键复位
			if(backKey==0)//M键弹起
			{
				workMode=MODE_NULL;	//取消状态
				setMainButtonNormal(MAINBUTTON_M);
			}
			else if(backKey==1)//A键弹起
			{
				interfaceIndex=1;//进入角度显示界面
				firstDis=false;
				return;
			}
			else if(backKey==2)
			{
				interfaceIndex=2;//进入摆臂控制界面
				firstDis=false;
				return;
			}
			else if(backKey==3)
			{
				interfaceIndex=3;//进入手臂控制界面
				firstDis=false;
				return;
			}
			else if(backKey==4)
			{
				interfaceIndex=4;//进入其他控制界面
				firstDis=false;
				return;
			}
			else if(backKey==5)
			{
				interfaceIndex=5;//进入应急控制界面
				firstDis=false;
				return;
			}
			break;
		case 0:	//M键按下
			if(backKey!=0)
			setMainButtonPress(MAINBUTTON_M);//M按键变成按下状态
			break;
		case 1:	//A键按下
			if(backKey!=1)
			setMainButtonPress(MAINBUTTON_A);//A按键变成按下状态
			break;
		case 2:	//B键按下
			if(backKey!=2)
			setMainButtonPress(MAINBUTTON_B);//B按键变成按下状态
			break;
		case 3://C键按下
			if(backKey!=3)
			setMainButtonPress(MAINBUTTON_C);//C按键变成按下状态
			break;	
		case 4://D键按下
			if(backKey!=4)
			setMainButtonPress(MAINBUTTON_D);//D按键变成按下状态
			break;
		case 5://ABD键同时按下 进入隐藏界面
			if(backKey!=5)
			{
				setMainButtonPress(MAINBUTTON_A);//ABD按键变成按下状态
				setMainButtonPress(MAINBUTTON_B);
				setMainButtonPress(MAINBUTTON_D);
			}
			break;
	}
	if(LCDManager->WireLength==0&&backWireLength!=0)//重新显示
	{
		pageID=MAINPAGENUM;
		LCDManager->ShowPic(pageID);
		if(!disError(true))//强制显示错误信息，返回fasle代表物错误内容
		{
			LCDManager->showVoltageAndSpeed();
			LCDManager->ShowCtrlSpeed(true);
		}

		LCDManager->ShowBattery(true);				//显示电池电量
		LCDManager->ShowSignal(true);					//显示信号强度
		backWireLength=LCDManager->WireLength;
	}
	else if(LCDManager->WireLength!=0&&backWireLength==0)//重新显示
	{
		pageID=MAINPAGENUM_1;
		LCDManager->ShowPic(pageID);
		if(!disError(true))//强制显示错误信息，返回fasle代表无错误内容
		{
			LCDManager->showVoltageAndSpeed_1();
			LCDManager->ShowCtrlSpeed_1(true);
		}
		LCDManager->ShowBattery(true);				//显示电池电量
		LCDManager->ShowSignal(true);					//显示信号强度
		backWireLength=LCDManager->WireLength;	
	}
	else
	{
		if(LCDManager->WireLength==0)
		{
			if(!disError(false)) //无错误
			{
				LCDManager->ShowCtrlSpeed(false);
				if(updateFlag)
					LCDManager->showVoltageAndSpeed();//有新的一帧到来
			}
		}
		else
		{
			if(!disError(false)) //无错误
			{
				LCDManager->ShowCtrlSpeed_1(false);
				if(updateFlag)
					LCDManager->showVoltageAndSpeed_1();//有新的一帧到来
			}
		}
		LCDManager->ShowBattery(false);				//显示电池电量
		LCDManager->ShowSignal(false);				//显示信号强度
	}
}

/**
  * 功  能：显示角度信息界面
  * 参  数：
	* key:			本次按键的值
	* backKey:	上次按键的值
  * 返回值：无
  */
void XbotDisplayApp::disPageAngle(int8_t key,int8_t backKey,bool updateFlag)					//显示角度界面
{
	static bool firstDis=false;
	static bool haveError=false;//是否有错误信息
	bool haveError_1=false;			//是否有错误信息
	if(interfaceIndex!=1)
		return;
	//信息报告处理
	if(!firstDis)//第一次显示
	{
		firstDis=true;
		pageID=ANGLEPAGENUM;
		LCDManager->ShowPic(pageID);
		LCDManager->ShowBattery(true);				//显示电池电量
		LCDManager->ShowSignal(true);					//显示信号强度
		haveError=disError(true);
		if(!haveError)//强制显示错误信息，返回fasle代表物错误内容
			LCDManager->showAngle(195,208,true);//强制刷新角度

// 		return;
	}
	if(keysValue==-1) //检测按键
	{
		if(backKey==0)//M键弹起
		{
			interfaceIndex=0;//进入主菜单显示界面
			firstDis=false;
			return;
		}
	}
	LCDManager->ShowBattery(false);				//显示电池电量
	LCDManager->ShowSignal(false);					//显示信号强度
	haveError_1=disError(false);
	if(!haveError_1)//本次没有错误信息并且有新的一帧到来
	{
		if(haveError)//上次有，当次无，强制刷新
			LCDManager->showAngle(195,208,haveError);
		else if(updateFlag)//上次无，当次无，并且有新的一帧到来
			LCDManager->showAngle(195,208,haveError);
	}
	haveError=haveError_1;

}
/**
  * 功  能：显示摆臂控制界面
  * 参  数：
	* key:			本次按键的值
	* backKey:	上次按键的值
  * 返回值：无
  */

void XbotDisplayApp::disPageSwingArmCtrl(int8_t key,int8_t backKey)	//显示摆臂控制界面
{
	static bool firstDis=false;
	static bool haveError=false;//是否有错误信息
	bool haveError_1=false;			//是否有错误信息
	if(interfaceIndex!=2)
		return;
	//信息报告处理
	if(!firstDis)//第一次显示
	{
		firstDis=true;
		pageID=SWINGARMCTRLPAGENUM;
		LCDManager->ShowPic(pageID);
		if(workMode==MODE_SHOULDER_A)//强制显示按钮
		{
			setButtonChecked(BUTTON_A);
		}
		else if(workMode==MODE_SHOULDER_B)
		{
			setButtonChecked(BUTTON_B);
		}
		else if(workMode==MODE_SHOULDER_C)
		{
			setButtonChecked(BUTTON_C);
		}
		else if(workMode==MODE_SHOULDER_D)
		{
			setButtonChecked(BUTTON_D);
		}
		haveError=disError(true);
		if(!haveError)//强制显示错误信息，返回fasle代表物错误内容
		{
			disSwingArmWorkMode(true);
		}
		LCDManager->ShowBattery(true);				//显示电池电量
		LCDManager->ShowSignal(true);					//显示信号强度
		return;
	}
	switch(keysValue) //检测按键
	{
		case -1://按键复位
			if(backKey==0)//M键弹起
			{
				interfaceIndex=0;//进入主菜单显示界面
				firstDis=false;
				return;
			}
			else if(backKey==1)//A键弹起
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,1,69,46,145,1,69);//将所有的按键置正常
				setWorkMode(MODE_SHOULDER_A);
				if(workMode==MODE_SHOULDER_A)
					setButtonChecked(BUTTON_A);
			}
			else if(backKey==2)//B键弹起
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,1,69,46,145,1,69);//将所有的按键置正常
				setWorkMode(MODE_SHOULDER_B);
				if(workMode==MODE_SHOULDER_B)
					setButtonChecked(BUTTON_B);
			}
			else if(backKey==3)//C键弹起
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,1,69,46,145,1,69);//将所有的按键置正常
				setWorkMode(MODE_SHOULDER_C);
				if(workMode==MODE_SHOULDER_C)
					setButtonChecked(BUTTON_C);
			}
			else if(backKey==4)//D键弹起
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,1,69,46,145,1,69);//将所有的按键置正常
				setWorkMode(MODE_SHOULDER_D);
				if(workMode==MODE_SHOULDER_D)
					setButtonChecked(BUTTON_D);
			}
			break;
		case 0:	//M键按下
			if(backKey!=0)
			setButtonPress(BUTTON_M);//M按键变成按下状态
			break;
		case 1:	//A键按下
			if(backKey!=1)
			
			setButtonPress(BUTTON_A);//A按键变成按下状态
			break;
		case 2:	//B键按下
			if(backKey!=2)

			setButtonPress(BUTTON_B);//B按键变成按下状态
			break;
		case 3://C键按下
			if(backKey!=3)

			setButtonPress(BUTTON_C);//C按键变成按下状态
			break;	
		case 4://D键按下
			if(backKey!=4)

			setButtonPress(BUTTON_D);//D按键变成按下状态
			break;
	}
	haveError_1=disError(false);
	if(!haveError_1)//本次没有错误信息
	{
		disSwingArmWorkMode(haveError);
	}
	haveError=haveError_1;
	LCDManager->ShowBattery(false);				//显示电池电量
	LCDManager->ShowSignal(false);					//显示信号强度
}

/**
  * 功  能：显示手臂控制界面
  * 参  数：
	* key:			本次按键的值
	* backKey:	上次按键的值
  * 返回值：无
  */
void XbotDisplayApp::disPageArmCtrl(int8_t key,int8_t backKey)				//显示手臂控制界面
{
	static bool firstDis=false;
	static bool haveError=false;//是否有错误信息
	bool haveError_1=false;			//是否有错误信息
	if(interfaceIndex!=3)
		return;
	//信息报告处理
	if(!firstDis)//第一次显示
	{
		firstDis=true;
		pageID=ARMCTRLPAGENUM;
		LCDManager->ShowPic(pageID);
		if(workMode==MODE_ARM_CA)//强制显示按钮
		{
			setButtonChecked(BUTTON_A);
		}
		else if(workMode==MODE_ARM_CB)
		{
			setButtonChecked(BUTTON_B);
		}
		else if(workMode==MODE_ARM_CC)
		{
			setButtonChecked(BUTTON_C);
		}
		else if(workMode==MODE_ARM_3D)
		{
			setButtonChecked(BUTTON_D);
		}
		haveError=disError(true);
		if(!haveError)//强制显示错误信息，返回fasle代表物错误内容
		{
			disArmWorkMode(true);
		}
		LCDManager->ShowBattery(true);				//显示电池电量
		LCDManager->ShowSignal(true);					//显示信号强度
		return;
	}
	switch(keysValue) //检测按键
	{
		case -1://按键复位
			if(backKey==0)//M键弹起
			{
				interfaceIndex=0;//进入主菜单显示界面
				firstDis=false;
				return;
			}
			else if(backKey==1)//A键弹起
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,3,71,42,141,3,71);//将所有的按键置正常
				setWorkMode(MODE_ARM_CA);
				if(workMode==MODE_ARM_CA)
					setButtonChecked(BUTTON_A);
			}
			else if(backKey==2)//B键弹起
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,3,71,42,141,3,71);//将所有的按键置正常
				setWorkMode(MODE_ARM_CB);
				if(workMode==MODE_ARM_CB)
					setButtonChecked(BUTTON_B);
			}
			else if(backKey==3)//C键弹起
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,3,71,42,141,3,71);//将所有的按键置正常
				setWorkMode(MODE_ARM_CC);
				if(workMode==MODE_ARM_CC)
					setButtonChecked(BUTTON_C);
			}
			else if(backKey==4)//D键弹起
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,3,71,42,141,3,71);//将所有的按键置正常
				setWorkMode(MODE_ARM_3D);
				if(workMode==MODE_ARM_3D)
					setButtonChecked(BUTTON_D);
			}
			break;
		case 0:	//M键按下
			if(backKey!=0)
			setButtonPress(BUTTON_M);//M按键变成按下状态
			break;
		case 1:	//A键按下
			if(backKey!=1)
			
			setButtonPress(BUTTON_A);//A按键变成按下状态
			break;
		case 2:	//B键按下
			if(backKey!=2)

			setButtonPress(BUTTON_B);//B按键变成按下状态
			break;
		case 3://C键按下
			if(backKey!=3)

			setButtonPress(BUTTON_C);//C按键变成按下状态
			break;	
		case 4://D键按下
			if(backKey!=4)

			setButtonPress(BUTTON_D);//D按键变成按下状态
			break;
	}
	haveError_1=disError(false);
	if(!haveError_1)//本次没有错误信息
	{
		disArmWorkMode(haveError);
	}
	haveError=haveError_1;
	LCDManager->ShowBattery(false);				//显示电池电量
	LCDManager->ShowSignal(false);					//显示信号强度
}

/**
  * 功  能：显示其他控制界面
  * 参  数：
	* key:			本次按键的值
	* backKey:	上次按键的值
  * 返回值：无
  */
void XbotDisplayApp::disPageOtherCtrl(int8_t key,int8_t backKey)			//显示其他控制界面
{
	static bool firstDis=false;
	static bool haveError=false;//是否有错误信息
	static uint8_t backWireLength=0;
	bool haveError_1=false;			//是否有错误信息
	if(interfaceIndex!=4)
		return;
	//信息报告处理
	if(!firstDis)//第一次显示
	{
		firstDis=true;
		if(LCDManager->WireLength==0)
			pageID=OTHERCTRLPAGENUM;
		else
			pageID=OTHERCTRLPAGENUM1;
		LCDManager->ShowPic(pageID);
		if(workMode==MODE_CAMERA_A)//强制显示按钮
		{
			setButtonChecked(BUTTON_A);
		}
		else if(workMode==MODE_CAMERA_B)
		{
			setButtonChecked(BUTTON_B);
		}
		else if(workMode==MODE_ARM_DC)
		{
			setButtonChecked(BUTTON_C);
		}
		else if(workMode==MODE_ARM_DD)
		{
			setButtonChecked(BUTTON_D);
		}
		haveError=disError(true);
		if(!haveError)//强制显示错误信息，返回fasle代表物错误内容
		{
			disOtherWorkMode(true);
		}
		LCDManager->ShowBattery(true);				//显示电池电量
		LCDManager->ShowSignal(true);					//显示信号强度
		backWireLength=LCDManager->WireLength;
		return;
	}
	switch(keysValue) //检测按键
	{
		case -1://按键复位
			if(backKey==0)//M键弹起
			{
				interfaceIndex=0;//进入主菜单显示界面
				firstDis=false;
				return;
			}
			else if(backKey==1)//A键弹起
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,3,71,42,141,3,71);//将所有的按键置正常
				if(LCDManager->WireLength==0)//无线状态
				{
					setWorkMode(MODE_CAMERA_A);
					if(workMode==MODE_CAMERA_A)
						setButtonChecked(BUTTON_A);
				}
				else
				{
					workMode=MODE_NULL;
				}
			}
			else if(backKey==2)//B键弹起
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,3,71,42,141,3,71);//将所有的按键置正常
				if(LCDManager->WireLength==0)//无线状态
				{
					setWorkMode(MODE_CAMERA_B);
					if(workMode==MODE_CAMERA_B)
						setButtonChecked(BUTTON_B);
				}
				else
				{
					workMode=MODE_NULL;
				}
			}
			else if(backKey==3)//C键弹起
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,3,71,42,141,3,71);//将所有的按键置正常
				setWorkMode(MODE_ARM_DC);
				if(workMode==MODE_ARM_DC)
					setButtonChecked(BUTTON_C);
			}
			else if(backKey==4)//D键弹起
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,3,71,42,141,3,71);//将所有的按键置正常
				setWorkMode(MODE_ARM_DD);
				if(workMode==MODE_ARM_DD)
					setButtonChecked(BUTTON_D);
			}
			break;
		case 0:	//M键按下
			if(backKey!=0)
			setButtonPress(BUTTON_M);//M按键变成按下状态
			break;
		case 1:	//A键按下
			if(backKey!=1)
			{
				if(LCDManager->WireLength==0)
					setButtonPress(BUTTON_A);//A按键变成按下状态
				else
				{
					setButtonChecked(BUTTON_A);
					workMode=MODE_CAMERA_A;
				}
			}

			break;
		case 2:	//B键按下
			if(backKey!=2)
			{
				if(LCDManager->WireLength==0)
					setButtonPress(BUTTON_B);//A按键变成按下状态
				else
				{
					setButtonChecked(BUTTON_B);
					workMode=MODE_CAMERA_B;
				}
			}
			break;
		case 3://C键按下
			if(backKey!=3)

			setButtonPress(BUTTON_C);//C按键变成按下状态
			break;	
		case 4://D键按下
			if(backKey!=4)

			setButtonPress(BUTTON_D);//D按键变成按下状态
			break;
	}
	if(LCDManager->WireLength==0&&backWireLength!=0)//重新显示
	{
		pageID=OTHERCTRLPAGENUM;
		LCDManager->ShowPic(pageID);
		haveError=disError(true);
		if(!haveError)//本次没有错误信息
		{
			disOtherWorkMode(true);
		}
		if(workMode==MODE_CAMERA_A)//强制显示按钮
		{
			setButtonChecked(BUTTON_A);
		}
		else if(workMode==MODE_CAMERA_B)
		{
			setButtonChecked(BUTTON_B);
		}
		else if(workMode==MODE_ARM_DC)
		{
			setButtonChecked(BUTTON_C);
		}
		else if(workMode==MODE_ARM_DD)
		{
			setButtonChecked(BUTTON_D);
		}
		LCDManager->ShowBattery(true);				//显示电池电量
		LCDManager->ShowSignal(true);					//显示信号强度
		backWireLength=LCDManager->WireLength;
	}
	else if(LCDManager->WireLength!=0&&backWireLength==0)//重新显示
	{
		pageID=OTHERCTRLPAGENUM1;
		LCDManager->ShowPic(pageID);
		haveError=disError(true);
		if(!haveError)//本次没有错误信息
		{
			disOtherWorkMode(true);
		}
		if(workMode==MODE_CAMERA_A)//强制显示按钮
		{
			setButtonChecked(BUTTON_A);
		}
		else if(workMode==MODE_CAMERA_B)
		{
			setButtonChecked(BUTTON_B);
		}
		else if(workMode==MODE_ARM_DC)
		{
			setButtonChecked(BUTTON_C);
		}
		else if(workMode==MODE_ARM_DD)
		{
			setButtonChecked(BUTTON_D);
		}
		LCDManager->ShowBattery(true);				//显示电池电量
		LCDManager->ShowSignal(true);					//显示信号强度
		backWireLength=LCDManager->WireLength;
	}
	else
	{		
		haveError_1=disError(false);
		if(!haveError_1)//本次没有错误信息
		{
			disOtherWorkMode(haveError);
		}
		haveError=haveError_1;
		LCDManager->ShowBattery(false);				//显示电池电量
		LCDManager->ShowSignal(false);					//显示信号强度
	}
}



/**
  * 功  能：显示应急控制界面
  * 参  数：
	* key:			本次按键的值
	* backKey:	上次按键的值
  * 返回值：无
  */
void XbotDisplayApp::disPageDubugCtrl(int8_t key,int8_t backKey)			//显示应急控制界面
{
	static bool firstDis=false;
	if(interfaceIndex!=5)
		return;
	//信息报告处理
	if(!firstDis)//第一次显示
	{
		firstDis=true;
		pageID=DEBUGCTRLPAGENUM;
		LCDManager->ShowPic(pageID);
// 		disError(true);											//该界面不显示警告
		LCDManager->ShowBattery(true);				//显示电池电量
		LCDManager->ShowSignal(true);					//显示信号强度
		if(enabledShowError==false)						//禁止警告显示开启
		{
			LCDManager->CutPicAndShow(DEBUGCTRLPAGENUM_1,206,133,107,29,206,133);
		}
		return;
	}
	switch(keysValue) //检测按键
	{
		case -1://按键复位
			if(backKey==0)//M键弹起
			{
				interfaceIndex=0;//进入主菜单显示界面
				firstDis=false;
				return;
			}
			else if(backKey==1)//A键弹起
			{
				setButtonNormal(BUTTON_A);
			}
			else if(backKey==2)//B键弹起
			{
				setButtonNormal(BUTTON_B);
			}
			else if(backKey==3)//C键弹起
			{
				setButtonNormal(BUTTON_C);
				if(enabledShowError==true)
				{
					enabledShowError=false;
					LCDManager->CutPicAndShow(DEBUGCTRLPAGENUM_1,206,133,107,29,206,133);
				}
				else
				{
					LCDManager->CutPicAndShow(DEBUGCTRLPAGENUM,206,133,107,29,206,133);
					enabledShowError=true;
				}
			}
			else if(backKey==4)//D键弹起 中英文切换
			{
				setButtonNormal(BUTTON_D);
				if(languagePosition==CHINESE)
				{
					languagePosition=ENGLISH;
#ifndef ABROAD	
					LCDManager->setLanguageBuf(0xEE);//设置语言区BUF
#endif
				}
				else
				{
					languagePosition=CHINESE;
#ifndef ABROAD
					LCDManager->setLanguageBuf(0x00);//设置语言区BUF
#endif
				}
				//重新显示当前界面
				LCDManager->setAnglePic(ANGLEPAGENUM);
				pageID=DEBUGCTRLPAGENUM;
				LCDManager->ShowPic(pageID);
				LCDManager->ShowBattery(true);				//显示电池电量
				LCDManager->ShowSignal(true);					//显示信号强度
				if(enabledShowError==false)						//禁止警告显示开启
				{
					LCDManager->CutPicAndShow(DEBUGCTRLPAGENUM_1,206,133,107,29,206,133);
				}
			}
			break;
		case 0:	//M键按下
			if(backKey!=0)
			setButtonPress(BUTTON_M);//M按键变成按下状态
			break;
		case 1:	//A键按下
			if(backKey!=1)
			setButtonPress(BUTTON_A);//A按键变成按下状态
			workMode=MODE_NULL;
			debugMode=DEBUF_CANCEL;//取消限位
			break;
		case 2:	//B键按下
			if(backKey!=2)
			setButtonPress(BUTTON_B);//B按键变成按下状态
			workMode=MODE_NULL;
			debugMode=DEBUF_RESET;//重设零位
			break;
		case 3://C键按下
			if(backKey!=3)
			setButtonPress(BUTTON_C);//C按键变成按下状态
			break;	
		case 4://D键按下
			if(backKey!=4)
			setButtonPress(BUTTON_D);//D按键变成按下状态
			break;
	}
// 	disError(false);//该界面不显示警告
	LCDManager->ShowBattery(false);				//显示电池电量
	LCDManager->ShowSignal(false);					//显示信号强度
}

/**
  * 功  能：显示武器控制界面
  * 参  数：
	* key:			本次按键的值
	* backKey:	上次按键的值
  * 返回值：水炮打开
  */
bool XbotDisplayApp::disPageWeaponCtrl()		//显示武器控制界面，该界面不显示警告信息
{
	static bool fireOpen=false;
	static bool lightFlag=true;
	static bool shootSucceed=false;
	static int8_t lightTimer=0;
	if(LCDManager->fireFlag==0x01&&(!shootSucceed)) //水炮钥匙开启 
	{
		if(!fireOpen)
		{
			fireOpen=true;
			workMode=MODE_NULL;
			LCDManager->ShowPic(WEAPONCTRLPAGENUM);//
			LCDManager->DisRecentage(0x5a,103,199,305,214);//清空进度条
			LCDManager->ShowBattery(true);				//强制显示电池电量
			LCDManager->ShowSignal(true);					//强制显示信号强度
			return fireOpen;
		}
		else
		{
			lightTimer++;
			lightTimer&=0x07;
			if(lightTimer==0)
			{
				LCDManager->backlightOn();
				lightFlag=true;
			}
			else if(lightTimer==5)
			{
				LCDManager->backlightOff();
				lightFlag=false;
			}
			LCDManager->DisRecentage(0x5a,103,199,305,214);//清空进度条
			LCDManager->ShowBattery(false);					//强制显示电池电量
			LCDManager->ShowSignal(false);					//强制显示信号强度
			return fireOpen;
		}
	}
	else if(LCDManager->fireFlag==0x02&&fireOpen) //水炮发射成功
	{
		//显示发射成功字样 OK
		if(!lightFlag)
		{
			lightFlag=true;
			LCDManager->backlightOn();
		}
		if(!shootSucceed)
		{
			//显示3
			LCDManager->ClearScreen();
			LCDManager->DisRecentage(0x5b,117,51,203,69); //
			LCDManager->DisRecentage(0x5b,187,69,203,189); //
			LCDManager->DisRecentage(0x5b,117,111,203,129); //
			LCDManager->DisRecentage(0x5b,117,171,203,189); //
			SysTick_DelayMs(400);//延时
			//显示2
			LCDManager->ClearScreen();
			LCDManager->DisRecentage(0x5b,117,51,203,69); //
			LCDManager->DisRecentage(0x5b,187,69,203,129); //
			LCDManager->DisRecentage(0x5b,117,111,203,129); //
			LCDManager->DisRecentage(0x5b,117,111,133,171); //
			LCDManager->DisRecentage(0x5b,117,171,203,189); //
			SysTick_DelayMs(400);//延时
			//显示1
			LCDManager->ClearScreen();
			LCDManager->DisRecentage(0x5b,152,51,168,189); //
			SysTick_DelayMs(300);//延时
			shootSucceed=true;
// 			LCDManager->DisRecentage(0x5a,103,199,305,215); //清空进度条
			LCDManager->ShowPic(WEAPONCTRLPAGENUM_1);				//显示发射成功的界面
			LCDManager->ShowBattery(true);									//强制显示电池电量
			LCDManager->ShowSignal(true);										//强制显示信号强度
		}
		else
		{
			LCDManager->ShowBattery(false);									//强制显示电池电量
			LCDManager->ShowSignal(false);									//强制显示信号强度
		}
		return fireOpen;
	}
	else if(LCDManager->fireFlag>0x04&&fireOpen)//显示发射进度条
	{
		//点亮背光
		if(!lightFlag)
		{
			lightFlag=true;
			LCDManager->backlightOn();
		}
		if(!shootSucceed)
			LCDManager->DisRecentage(0x5b,103,199,103+(LCDManager->fireFlag-0x04)*8,214);
		LCDManager->ShowBattery(false);				//强制显示电池电量
		LCDManager->ShowSignal(false);					//强制显示信号强度
		return fireOpen;
	}
	else if(LCDManager->fireFlag>0x01&&(!fireOpen))
	{
		LCDManager->fireFlag=0x00;
		return fireOpen;
	}
	else if(LCDManager->fireFlag==0x00)
	{
		shootSucceed=false;
		if(!lightFlag)
		{
			lightFlag=true;
			LCDManager->backlightOn();
		}
		if(fireOpen)
		{
			fireOpen=false;
// 			if(interfaceIndex>-1)
			{
				LCDManager->ShowPic(pageID);//
				if(interfaceIndex==1)//角度信息显示界面
				{
					LCDManager->showAngle(195,208,true);//强制刷新
				}
			}
			LCDManager->ShowBattery(true);				//强制显示电池电量
			LCDManager->ShowSignal(true);					//强制显示信号强度
		}
		return fireOpen;
	}
	return false;
}

/**
  * 功  能：显示信息报告界面
  * 参  数：
	* key:			本次按键的值
	* backKey:	上次按键的值
  * 返回值：无
  */
// void XbotDisplayApp::disPageWarning()										//显示信息报告界面
// {

// }

/**
  * 功  能：运行在定时器2中的函数，主要作用获取按键的键值
  * 参  数：无
  * 返回值：无
  * 备  注：定时时间20MS 按键反应时间是0.2S,ABD按键反应时间是5S
  */

void XbotDisplayApp::runOnTime2()
{
	static uint16_t keyIndex = 0;
	
	static bool backKaym=0;
	static bool backKaya=0;
	static bool backKayb=0;
	static bool backKayc=0;
	static bool bacdKayd=0;
// 	static int8_t bacdKeysValue=-1;

	bool kaym=key_M->getValue();
	bool kaya=key_A->getValue();
	bool kayb=key_B->getValue();
	bool kayc=key_C->getValue();
	bool kayd=key_D->getValue();
	maskKeysValue=(kaym<<4)|(kaya<<3)|(kayb<<2)|(kayc<<1)|kayd;
	if(kaym!=backKaym)
	{
		keyIndex=0;
		backKaym=kaym;
	}
	if(kaya!=backKaya)
	{
		keyIndex=0;
		backKaya=kaya;
	}
	if(kayb!=backKayb)
	{
		keyIndex=0;
		backKayb=kayb;
	}
	if(kayc!=backKayc)
	{
		keyIndex=0;
		backKayc=kayc;
	}
	if(kayd!=bacdKayd)
	{
		keyIndex=0;
		bacdKayd=kayd;
	}
	
	if(kaym&&!kaya&&!kayb&&!kayc&&!kayd)
	{
		if(keyIndex>KEYINDEX_MAX)
		{
			keysValue=KM;
		}
		else
			keyIndex++;
	}
	else 	if(!kaym&&kaya&&!kayb&&!kayc&&!kayd)
	{
		if(keyIndex>KEYINDEX_MAX)
		{
			keysValue=KA;
		}
		else
			keyIndex++;
	}
	else 	if(!kaym&&!kaya&&kayb&&!kayc&&!kayd)
	{
		if(keyIndex>KEYINDEX_MAX)
		{
			keysValue=KB;
		}
		else
			keyIndex++;
	}
	else 	if(!kaym&&!kaya&&!kayb&&kayc&&!kayd)
	{
		if(keyIndex>KEYINDEX_MAX)
		{
			keysValue=KC;
		}
		else
			keyIndex++;
	}
	else 	if(!kaym&&!kaya&&!kayb&&!kayc&&kayd)
	{
		if(keyIndex>KEYINDEX_MAX)
		{
			keysValue=KD;
		}
		else
			keyIndex++;
	}
	else 	if(!kaym&&kaya&&kayb&&!kayc&&kayd)
	{
		if(keyIndex>KEYINDEX_ABD_MAX)
		{
			keysValue=KABD;
		}
		else
			keyIndex++;
	}
	else
	{
		keyIndex=0;
		keysValue=-1;
	}
		
	
// 	if(keysValue!=bacdKeysValue)
// 	{
// 		bacdKeysValue=keysValue;
// 		if(keysValue==-1)
// 			terminalPort->writeLine("the key is NULL\r\n");
// 		else 	if(keysValue==0)
// 			terminalPort->writeLine("the key is M\r\n");
// 		else 	if(keysValue==1)
// 			terminalPort->writeLine("the key is A\r\n");
// 		else 	if(keysValue==2)
// 			terminalPort->writeLine("the key is B\r\n");
// 		else 	if(keysValue==3)
// 			terminalPort->writeLine("the key is C\r\n");
// 		else 	if(keysValue==4)
// 			terminalPort->writeLine("the key is D\r\n");
// 		else 	if(keysValue==5)
// 			terminalPort->writeLine("the key is ABD\r\n");
// 		else 
// 			terminalPort->writeLine("the key is error!\r\n");
// 	}
}





/**
  * 功  能：运行在定时器3中的函数,主要作用是检测数据
  * 参  数：无
  * 返回值：无
  * 
  */

void XbotDisplayApp::runOnTime3()
{
	static int8_t backKeysValue=-1;
	static int8_t backWireLength=0;
	bool lcdUpdateFlag=false;
	if(terminalManager->reciveData())								//新的一帧到来
	{
		led_1->reverseLight();
		lcdUpdateFlag=updateLCDdata();
		terminalManager->updateSendBuf(workMode,debugMode,maskKeysValue);
		terminalManager->sendcommand();
		if(debugMode!=DEBUF_NULL)
		{
			debugMode=DEBUF_NULL;
		}
		if(disPageWeaponCtrl())
			return;
	}
	disPageStart();
	if(LCDManager->fireFlag!=0x00)
		return;
	if(keysValue>-2&&keysValue<6)//合法的key值-1 0 1 2 3 4 5 //水炮钥匙没有开启 
	{
		if((backWireLength==0&&LCDManager->WireLength!=0)||(backWireLength!=0&&LCDManager->WireLength==0))//有线和无线有切换
		{
			if(workMode==MODE_CAMERA_A||workMode==MODE_CAMERA_B)
			{
				workMode=MODE_NULL;
			}
			backWireLength=LCDManager->WireLength;
		}
		disPageMain(keysValue,backKeysValue,lcdUpdateFlag);			//显示主菜单界面
		disPageAngle(keysValue,backKeysValue,lcdUpdateFlag);		//显示角度界面
		disPageSwingArmCtrl(keysValue,backKeysValue);						//显示摆臂控制界面
		disPageArmCtrl(keysValue,backKeysValue);								//显示手臂控制界面
		disPageOtherCtrl(keysValue,backKeysValue);							//显示其他控制界面
		disPageDubugCtrl(keysValue,backKeysValue);							//显示应急控制界面
		if(keysValue!=backKeysValue)
		{
			backKeysValue=keysValue;
		}
	}
}

/**
  * 功  能：运行在定时器4中的函数
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotDisplayApp::runOnTime4()
{
	uint8_t temLanguge;
	temLanguge=LCDManager->riceveData();
	if(temLanguge==2)
	{
		languagePosition=CHINESE;
		LCDManager->setAnglePic(ANGLEPAGENUM);
	}
	else if(temLanguge==1)//英文
	{
		languagePosition=ENGLISH;
		LCDManager->setAnglePic(ANGLEPAGENUM);
	}
}





