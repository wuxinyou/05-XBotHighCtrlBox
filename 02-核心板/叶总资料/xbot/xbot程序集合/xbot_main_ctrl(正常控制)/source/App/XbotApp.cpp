/**
  ******************************************************************************
	*文件：XbotApp.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：控制Xbot的主类的实现文件
	*备注：
	*
  ******************************************************************************  
	*/ 


/* 头文件包含 ------------------------------------------------------------------*/
#include "XbotApp.h"
#include <stdlib.h>
#include "STM32F4_SysTick.h"
#include <math.h>
/* 类型定义 --------------------------------------------------------------------*/

/* 宏定义-----------------------------------------------------------------------*/ 

//绝对值宏
#define ABS(X)			((X)>0?(X):(-(X)))
//二者绝对值谁大谁小宏
#define MAX(X,Y)		((ABS(X))>(ABS(Y))?(ABS(X)):(ABS(Y)))
#define MIN(X,Y)		((ABS(X))<(ABS(Y))?(ABS(X)):(ABS(Y)))

#define SEND_CHECK_TIME_MAX 		10
#define CHECK_TIME_MAX 					(SEND_CHECK_TIME_MAX+1)
#define CHECK_DRIVER_NUM 				13
#define TERMINAL_FRAME_LEN    	13

//地址宏
#define 	LEFTRUN_DDR						0x00
#define 	RIGHTRUN_DDR					0x01
#define 	SUPPORT_ARM_DDR				0x02
#define 	POWER_DDR							0x03
	
#define 	BIG_ARM_ROTATE_DDR		0x00
#define 	BIG_ARM_PITCH_ADDR		0x01
#define 	FORE_ARM_PITCH_DDR		0x02
#define 	WRIST_PITCH_DDR				0x03
#define 	WRIST_ROTATE_DDR			0x04
#define 	PAN_TILT_PITCH_DDR  	0x05
#define 	PAN_TILT_ROTATE_DDR 	0x06
#define 	FINGER_MEDIATE_DDR 		0x07
#define 	CAMERA_PITCH_DDR 			0x08
#define 	OTHER_DEVICE_DDR 			0x09

//串口设置宏 
#define		WIRE_LESS_PORT_NUM		6
#define		WIRE_PORT_NUM					4
#define		CODED_DISC_PORT_NUM		5
#define		ARM_PORT_NUM					1
#define		UNDERPAN_PORT_NUM			2
#define		GPS_PORT_NUM					3

#define		WIRE_LESS_PORT_BAUD		19200
#define		WIRE_PORT_BAUD				19200
#define		CODED_DISC_PORT_BAUD	115200
#define		ARM_PORT_BAUD					38400
#define		UNDERPAN_PORT_BAUD		38400
#define		GPS_PORT_BAUD					38400

//新驱动器程序启动开关
#define NEW_DRIVER_PROGRAM

//新版XBOT511启动开关
#define NEWXBOT

//新式线缆盘启动开关
#define NEWOPTICALBOBBIN  

//使用点位器 启动开关
#define USEPOTENTIOMETER

//底盘三电机温度上限
#define WARNINGTEMPERATURE 90

//角度查询指令ID
#define ANGLE_INQUIRE_ID				0X08
//取消限位指令ID
#define ANGLE_FREE_ID						0X02
//重设角度零位指令ID
#define ANGLE_REINIT_ID					0X06
//保存角度指令ID
#define ANGLE_SAVE_ID						0X07
//速度查询指令ID
#define SPEED_INQUIRE_ID				0X09
//速度使能指令
#define ENASPEED_ID							0X0C

#define FB_OK_1 					0X4F
#define FB_OK_2 					0X4B
#define FB_SAVE_ID 				0x67
#define FB_REINIT_ID 			0x66
#define FB_FREE_POS_ID 		0x62
#define FB_POS_SPEED_ID 	0x41
#define FB_POS_USPEED_ID 	0x43
#define FB_ENASPEED_ID 		0x4C
#define FB_POS_ANGLE_ID 	0x68
#define FB_SPEED_ID				0x49
#define FB_ECTQ_ID				0x72
#define FB_TEMPERATURE_ID	0x73


#define ARM0_ANGLE_0			((uint32_t)0)
#define ARM0_ANGLE_45			((uint32_t)128)
#define ARM0_ANGLE_90			((uint32_t)256)
#define ARM0_ANGLE_135		((uint32_t)384)
#define ARM0_ANGLE_145		((uint32_t)412)
// #define ARM0_ANGLE_192		((uint32_t)545)
#define ARM0_ANGLE_185		((uint32_t)527)
#define ARM0_ANGLE_192		((uint32_t)538)
#define ARM0_ANGLE_200		((uint32_t)569)
#define ARM0_ANGLE_210		((uint32_t)594)
#define ARM0_ANGLE_180		((uint32_t)512)
#define ARM0_ANGLE_225		((uint32_t)640)
#define ARM0_ANGLE_232		((uint32_t)660)
#define ARM0_ANGLE_270		((uint32_t)768)
#define ARM0_ANGLE_280		((uint32_t)796)
#define ARM0_ANGLE_290		((uint32_t)825)

#define ARM0_ANGLE_300		((uint32_t)853)
#define ARM0_ANGLE_315		((uint32_t)896)
#define ARM0_ANGLE_330		((uint32_t)938)
#define ARM0_ANGLE_340		((uint32_t)967)
#define ARM0_ANGLE_343		((uint32_t)976)
#define ARM0_ANGLE_348		((uint32_t)997)
#define ARM0_ANGLE_360		((uint32_t)1024)

//支臂预置位角度宏 加入修正值开关
// 	#define XBOT_SUB_ARM0			((uint32_t)(-35))

#ifdef XBOT_SUB_ARM0
	#define XBOT_HHH_ARM0				(ARM0_ANGLE_145+XBOT_SUB_ARM0)
	#define XBOT_III_ARM0				(ARM0_ANGLE_232+XBOT_SUB_ARM0)
	#define XBOT_JJJ_ARM0				(ARM0_ANGLE_348+XBOT_SUB_ARM0)
	#define XBOT_KKK_ARM0				(ARM0_ANGLE_192+XBOT_SUB_ARM0)
	#define XBOT_LLL_ARM0				(ARM0_ANGLE_210+XBOT_SUB_ARM0)
	#define XBOT_CRITICAL_ARM0	(ARM0_ANGLE_300+XBOT_SUB_ARM0)
	
	#define XBOT_CRITICAL_ARM0_UP	 	(ARM0_ANGLE_330+XBOT_SUB_ARM0) //支臂限位死区上限330度
	#define XBOT_CRITICAL_ARM0_DN		(ARM0_ANGLE_290+XBOT_SUB_ARM0) //支臂限位死区下限290度
	#define XBOT_CRITICAL_ARM0_UP_1	(ARM0_ANGLE_340+XBOT_SUB_ARM0) //支臂限位死区上限330度
	#define XBOT_CRITICAL_ARM0_DN_1	(ARM0_ANGLE_280+XBOT_SUB_ARM0) //支臂限位死区下限290度
#else
	#define XBOT_HHH_ARM0				ARM0_ANGLE_145
	#define XBOT_III_ARM0				ARM0_ANGLE_232
	#define XBOT_JJJ_ARM0				ARM0_ANGLE_348
	#define XBOT_KKK_ARM0				ARM0_ANGLE_192
	#define XBOT_LLL_ARM0				ARM0_ANGLE_210
	#define XBOT_CRITICAL_ARM0	ARM0_ANGLE_300
	
	#define XBOT_CRITICAL_ARM0_UP	ARM0_ANGLE_330 //支臂限位死区上限330度
	#define XBOT_CRITICAL_ARM0_DN	ARM0_ANGLE_290 //支臂限位死区下限290度
	#define XBOT_CRITICAL_ARM0_UP_1	ARM0_ANGLE_340 //支臂限位死区上限330度
	#define XBOT_CRITICAL_ARM0_DN_1	ARM0_ANGLE_280 //支臂限位死区下限290度
#endif


//预置位控制角度值
#define XBOT_AAAA_ARM0		XBOT_HHH_ARM0
#define XBOT_AAAA_ARM1		0
#define XBOT_AAAA_ARM2		-1500
#define XBOT_AAAA_ARM3		2900
#define XBOT_AAAA_ARM4		1600
#define XBOT_AAAA_ARM5		0
#define XBOT_AAAA_ARM6		16000
#define XBOT_AAAA_ARM7		0

#define XBOT_BBBB_ARM0		XBOT_LLL_ARM0
#define XBOT_BBBB_ARM1		0
#define XBOT_BBBB_ARM2		-10500
#define XBOT_BBBB_ARM3 		5500
#define XBOT_BBBB_ARM4		4400
#define XBOT_BBBB_ARM5 		0
#define XBOT_BBBB_ARM6		16000
#define XBOT_BBBB_ARM7		0

#define XBOT_CCCC_ARM0		XBOT_JJJ_ARM0
#define XBOT_CCCC_ARM1		0
#define XBOT_CCCC_ARM2		0 //向C模式靠拢时 大臂俯仰的角度增大
#define XBOT_CCCC_ARM3 		600//向C模式靠拢时 小臂俯仰的角度减小
#define XBOT_CCCC_ARM4		200//向C模式靠拢时 手腕俯仰的角度减小


#define XBOT_CCCC_ARM5 		0
#define XBOT_CCCC_ARM6		16000
#define XBOT_CCCC_ARM7		0

#define XBOT_DDDD_ARM0		XBOT_LLL_ARM0
#define XBOT_DDDD_ARM1		0
#define XBOT_DDDD_ARM2		-12600
#define XBOT_DDDD_ARM3 		5400
#define XBOT_DDDD_ARM4		10900
#define XBOT_DDDD_ARM5 		0
#define XBOT_DDDD_ARM6		-2000
#define XBOT_DDDD_ARM7		0

#define XBOT_EEEE_ARM0		XBOT_LLL_ARM0
#define XBOT_EEEE_ARM1		0
#define XBOT_EEEE_ARM2		-3100
#define XBOT_EEEE_ARM3 		6200
#define XBOT_EEEE_ARM4		6200
#define XBOT_EEEE_ARM5 		0
#define XBOT_EEEE_ARM6		13700
#define XBOT_EEEE_ARM7		0

//最大参考速度宏
#define REFER_SPEED_MAX_ARM0		7000
// #define REFER_SPEED_MAX_ARM1		5000
#define REFER_SPEED_MAX_ARM1		8000
#define REFER_SPEED_MAX_ARM2		5000
#define REFER_SPEED_MAX_ARM3		5000
#define REFER_SPEED_MAX_ARM4		5000
#define REFER_SPEED_MAX_ARM5		12000
#define REFER_SPEED_MAX_ARM6		9000
#define REFER_SPEED_MAX_ARM7		2000
#define REFER_SPEED_MAX_ARM8		9000
//最小参考角度宏
#define REFER_SPEED_MIN_ARM0		250
#define REFER_SPEED_MIN_ARM1		400
#define REFER_SPEED_MIN_ARM2		250
#define REFER_SPEED_MIN_ARM3		250
#define REFER_SPEED_MIN_ARM4		250
#define REFER_SPEED_MIN_ARM5		600
#define REFER_SPEED_MIN_ARM6		450
#define REFER_SPEED_MIN_ARM7		100
#define REFER_SPEED_MIN_ARM8		450

//零位绝对值
// #define XBOT_ZERO_A1		0
// #define XBOT_ZERO_A2		0
// #define XBOT_ZERO_A3		700
// #define XBOT_ZERO_A4		400
// #define XBOT_ZERO_A5		0
// #define XBOT_ZERO_A6		18000
// #define XBOT_ZERO_A7		0
// #define XBOT_ZERO_A8		0

#define XBOT_ZERO_A1		0
#define XBOT_ZERO_A2		-9000
#define XBOT_ZERO_A3		18000
#define XBOT_ZERO_A4		18000
#define XBOT_ZERO_A5		0
#define XBOT_ZERO_A6		16000
#define XBOT_ZERO_A7		0
#define XBOT_ZERO_A8		0

//零位重设开关
#define RE_INIT_ALL_ARM

#ifdef RE_INIT_ALL_ARM

	#define RE_INIT_ARM1
	#define RE_INIT_ARM2
	#define RE_INIT_ARM3
	#define RE_INIT_ARM4
	#define RE_INIT_ARM5
	#define RE_INIT_ARM6
	#define RE_INIT_ARM7
	#define RE_INIT_ARM8
#endif

//各个关节速度系数 只能写成分数形式 不要写成小数形式 也不要加括号 x/y->  (x*5000)/(y*500*maxspeed)
//(x*10)/(y*max)->x/(y*(max/10))->x/y=SPEED_COEFFICIENT*max/10
#define SPEED_COEFFICIENT_ARM0	7137/3500          //支臂俯仰 
#define SPEED_COEFFICIENT_ARM1	121/16					 	 //大臂旋转
#define SPEED_COEFFICIENT_ARM2	36504/6125				 //大臂俯仰 
#define SPEED_COEFFICIENT_ARM3	36504/6125				 //小臂俯仰
#define SPEED_COEFFICIENT_ARM4	36504/6125				 //手腕俯仰

#define SPEED_COEFFICIENT_ARM5	1397/200						//手爪旋转 *9/12
#define SPEED_COEFFICIENT_ARM6	1397/300						//云台俯仰 
#define SPEED_COEFFICIENT_ARM7	2783/1000				 		//云台旋转 
#define SPEED_COEFFICIENT_ARM8	1397/200				 		//手爪夹持 

#ifdef NEWOPTICALBOBBIN	
#define LRMOTERMAXSPEED_WIRE_WORK				3000
#else
#define LRMOTERMAXSPEED_WIRE_WORK				8000 //智能线缆盘有线速度减慢
#endif
#define LRMOTERMAXSPEED_WIRELESS_WORK		8000

#define PI 3.1415926536

#define YYY_LINE_RADIAN (0)
#define ZZZ_LINE_RADIAN (PI/2)
#define BIG_ARM_LEN 	55800
#define FORE_ARM_LEN 	53820
#define WRIST_ARM_LEN 25000

//构造函数
XbotApp::XbotApp()
{
	SysTick_DelayMs(5000);				//延时2秒，等待设备启动
	workModel=NORMAL;							//工作模式，默认为正常模式
	signalType=WIRELESS_WORK_MODE;//信号类型默认是无线信号
	sendEnaSpeedOk=true;
	reInitPosSendOk=true;					//零位重设完成标志 默认完成 为true
	saveSendOk=true;							//保存指令完成标志 默认完成 
	offLimitSendOk=true;					//限位指令发送完成标志 默认完成 
	reWeaponSendOk=true;					//武器发射发送完成标志 默认完成 
	WireType=false;								//默认为普通有线
	riciveCboxFlag=false;
	xyzFlag=false;
	checkTime=			new int8_t[CHECK_DRIVER_NUM];
	ectQuantity=0;

	FBTemperature_1=0;
	FBTemperature_2=0;
	FBTemperature_3=0;
	
	fBTerminalData=	new uint8_t[TERMINAL_FRAME_LEN]; //终端反馈数据暂存
	for(int i=0;i<TERMINAL_FRAME_LEN;i++)
		fBTerminalData[i]=0;

	fBLeftSpeed=				new ctrData();				//反馈的左电机速度暂存
	fBRightSpeed=				new ctrData();				//反馈的右电机速度暂存
	
	fBEctQuantity_1=		new ctrData();				//反馈的电源电量暂存
	fBEctQuantity_2=		new ctrData();				//反馈的电源电量暂存
	fBEctQuantity_3=		new ctrData();				//反馈的电源电量暂存
	fBEctQuantity_4=		new ctrData();				//反馈的电源电量暂存

	led_1 = new LEDLighter(GPIOC,GPIO_Pin_0);	//默认点亮
	led_2 = new LEDLighter(GPIOC,GPIO_Pin_1);	//默认点亮
	led_1->setLightOff();
	led_2->setLightOff();
	GPSPort=new SerialPort(GPS_PORT_NUM,GPS_PORT_BAUD);					//和终端有线通信的串口

//设备初始化
	Terminal=				new TerminalControl(wirePort,wireLessPort);	//终端通信的协议类变量

	leftRunM=				new MotorControl(underpanPort);							//行进左电机
	rightRunM=			new MotorControl(underpanPort);							//行进右电机

	power=					new PowerControl(underpanPort);							//电源管理通信协议类变量
	OtherDevice=		new OtherDeviceControl(armPort);						//其他设备的通信协议变量
	CodedDisc=			new CodedDiscControl(codedDiscPort);				//绝对码盘的通信协议类变量
	gpsDevice=			new GpsImuControl(GPSPort);									//GPS设备的通信协议类变量
	opticalBobbinDevice=new OpticalBobbin(armPort);							//自动线缆盘的通信协议类变量
	
//设备地址设定
	leftRunM->					setAddr(LEFTRUN_DDR);
	rightRunM->					setAddr(RIGHTRUN_DDR);
	supportArmM->				setAddr(SUPPORT_ARM_DDR);
	power->							setAddr(POWER_DDR);
	
	bigArmRotateM->			setAddr(BIG_ARM_ROTATE_DDR);
	bigArmPitchM->			setAddr(BIG_ARM_PITCH_ADDR);
	forearmPitchM->			setAddr(FORE_ARM_PITCH_DDR);
	wristPitchM->				setAddr(WRIST_PITCH_DDR);
	wristRotateM->			setAddr(WRIST_ROTATE_DDR);
	panTiltPitchM->			setAddr(PAN_TILT_PITCH_DDR);
	panTiltRotateM->		setAddr(PAN_TILT_ROTATE_DDR);
	fingerMediateM->		setAddr(FINGER_MEDIATE_DDR);
	cameraPitchM->			setAddr(CAMERA_PITCH_DDR);
	OtherDevice->				setAddr(OTHER_DEVICE_DDR);
	
//设置零位的绝对参考角度
	bigArmRotateM->			setZeroAngle(XBOT_ZERO_A1);
	bigArmPitchM->			setZeroAngle(XBOT_ZERO_A2);
	forearmPitchM->			setZeroAngle(XBOT_ZERO_A3);
	wristPitchM->				setZeroAngle(XBOT_ZERO_A4);
	wristRotateM->			setZeroAngle(XBOT_ZERO_A5);
	panTiltPitchM->			setZeroAngle(XBOT_ZERO_A6);
	panTiltRotateM->		setZeroAngle(XBOT_ZERO_A7);
	fingerMediateM->		setZeroAngle(XBOT_ZERO_A8);	

//设置最大参考速度
	supportArmM->				setReferSpeedMax(REFER_SPEED_MAX_ARM0);
	bigArmRotateM->			setReferSpeedMax(REFER_SPEED_MAX_ARM1);
	bigArmPitchM->			setReferSpeedMax(REFER_SPEED_MAX_ARM2);
	forearmPitchM->			setReferSpeedMax(REFER_SPEED_MAX_ARM3);
	wristPitchM->				setReferSpeedMax(REFER_SPEED_MAX_ARM4);
	wristRotateM->			setReferSpeedMax(REFER_SPEED_MAX_ARM5);
	panTiltPitchM->			setReferSpeedMax(REFER_SPEED_MAX_ARM6);
	panTiltRotateM->		setReferSpeedMax(REFER_SPEED_MAX_ARM7);
	
//设置最小参考速度
	supportArmM->				setReferSpeedMin(REFER_SPEED_MIN_ARM0);
	bigArmRotateM->			setReferSpeedMin(REFER_SPEED_MIN_ARM1);
	bigArmPitchM->			setReferSpeedMin(REFER_SPEED_MIN_ARM2);
	forearmPitchM->			setReferSpeedMin(REFER_SPEED_MIN_ARM3);
	wristPitchM->				setReferSpeedMin(REFER_SPEED_MIN_ARM4);
	wristRotateM->			setReferSpeedMin(REFER_SPEED_MIN_ARM5);
	panTiltPitchM->			setReferSpeedMin(REFER_SPEED_MIN_ARM6);
	panTiltRotateM->		setReferSpeedMin(REFER_SPEED_MIN_ARM7);

	fBbigArmRotateA->DATA_16=0;						//反馈的大臂旋转电机角度暂存初始化
	fBbigArmPitchA->DATA_16=0; 						//反馈的大臂俯仰电机角度暂存初始化
	fBforearmPitchA->DATA_16=0;						//反馈的小臂俯仰电机角度暂存初始化
	fBwristPitchA->DATA_16=0;							//反馈的手腕俯仰电机角度暂存初始化
	fBwristRotateA->DATA_16=0;						//反馈的手腕旋转电机角度暂存初始化
	fBpanTiltPitchA->DATA_16=0;						//反馈的云台俯仰电机角度暂存初始化
	fBpanTiltRotateA->DATA_16=0;					//反馈的云台旋转电机角度暂存初始化
	fBfingerMediateA->DATA_16=0;					//反馈的手爪捏合电机角度暂存初始化
	fBcameraPitchA->DATA_16=0;						//反馈的相机俯仰电机角度暂存初始化
	fBDiscA->DATA_16=0;										//反馈的绝对码盘数据暂存初始化
	resetEnaSpeed();							//重启使能速度指令
//定时器初始化
	t1=new Timer(TIM2);
	t1->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM2_SubPriority);
	t1->setTimeOut(1);

	t2=new Timer(TIM3);
	t2->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM3_SubPriority);
	t2->setTimeOut(7);

	t3=new Timer(TIM4);
	t3->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM4_SubPriority);
	t3->setTimeOut(100);

//打开定时器	
// 	t1->start();
// 	t2->start();
// 	t3->start();
// 	armPort->writeLine("xbotApp init ok!");
}
	workIdType XbotApp::workId=TTTModel;												//工作ID 默认为直接控制
	bool XbotApp::limitFlag=true;																//限位标志 默认限位 为true
	CodeDiscData * XbotApp::fBDiscA=new CodeDiscData();					//反馈的绝对码盘数据暂存	
	ctrData * XbotApp::fBbigArmRotateA=			new ctrData();			//反馈的大臂旋转电机角度暂存
	ctrData * XbotApp::fBbigArmPitchA=			new ctrData(); 			//反馈的大臂俯仰电机角度暂存
	ctrData * XbotApp::fBforearmPitchA=			new ctrData();			//反馈的小臂俯仰电机角度暂存
	ctrData * XbotApp::fBwristPitchA=				new ctrData();			//反馈的手腕俯仰电机角度暂存
	ctrData * XbotApp::fBwristRotateA=			new ctrData();			//反馈的手腕旋转电机角度暂存
	ctrData * XbotApp::fBpanTiltPitchA=			new ctrData();			//反馈的云台俯仰电机角度暂存
	ctrData * XbotApp::fBpanTiltRotateA=		new ctrData();			//反馈的云台旋转电机角度暂存
	ctrData * XbotApp::fBfingerMediateA=		new ctrData();			//反馈的手爪捏合电机角度暂存
	ctrData * XbotApp::fBcameraPitchA=			new ctrData();			//反馈的相机俯仰电机角度暂存

	SerialPort* XbotApp::wireLessPort=			new SerialPort(WIRE_LESS_PORT_NUM,WIRE_LESS_PORT_BAUD);		//和终端无线通信的串口
	SerialPort* XbotApp::wirePort=					new SerialPort(WIRE_PORT_NUM,WIRE_PORT_BAUD);							//和终端有线通信的串口
	SerialPort* XbotApp::codedDiscPort=			new SerialPort(CODED_DISC_PORT_NUM,CODED_DISC_PORT_BAUD);	//和码盘通信的串口
	SerialPort* XbotApp::armPort=						new SerialPort(ARM_PORT_NUM,ARM_PORT_BAUD);								//和机械臂通信的串口
	SerialPort* XbotApp::underpanPort=			new SerialPort(UNDERPAN_PORT_NUM,UNDERPAN_PORT_BAUD);			//和底盘三电机以及电源控制板通信的串口

	MotorControl * XbotApp::supportArmM=		new MotorControl(underpanPort);						//支臂电机
	MotorControl * XbotApp::bigArmRotateM=	new MotorControl(armPort);								//大臂旋转电机
	MotorControl * XbotApp::bigArmPitchM=		new MotorControl(armPort); 								//大臂俯仰电机
	MotorControl * XbotApp::forearmPitchM=	new MotorControl(armPort);								//小臂俯仰电机
	MotorControl * XbotApp::wristPitchM=		new MotorControl(armPort);								//手腕俯仰电机
	MotorControl * XbotApp::wristRotateM=		new MotorControl(armPort);								//手腕旋转电机
	MotorControl * XbotApp::panTiltPitchM=	new MotorControl(armPort);								//云台俯仰电机
	MotorControl * XbotApp::panTiltRotateM=	new MotorControl(armPort);								//云台旋转电机
	MotorControl * XbotApp::fingerMediateM=	new MotorControl(armPort);								//手爪捏合电机
	MotorControl * XbotApp::cameraPitchM=		new MotorControl(armPort);								//相机俯仰电机

//析构函数
XbotApp::~XbotApp()
{
	delete wireLessPort;
	delete wirePort;
	delete codedDiscPort;
	delete armPort;
	delete underpanPort;
// 	delete GPSPort;
	delete Terminal;
	delete leftRunM;
	delete rightRunM;
	delete supportArmM;
	delete bigArmRotateM;
	delete bigArmPitchM;
	delete forearmPitchM;
	delete wristPitchM;
	delete wristRotateM;
	delete panTiltPitchM;
	delete panTiltRotateM;
	delete fingerMediateM;
	delete cameraPitchM;
	delete power;
	delete OtherDevice;
	delete CodedDisc;
}

/**
  * 功  能：运行在定时器2中的函数，主要作用是解析和更新各个设备的数据
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::runOnTime2()
{
	signalType=Terminal->getSerialWorkMode();
	if(power->checkPowerKey()&&saveSendOk==true)								//检测电源按键是否按下 如果按下复位保存指令
	{
		resetSave();
	}
	if(workModel==MIRROR)											//镜像传输打开
	{
		controlArmISO();												//启动镜像传输 数据交互转发
		return;
	}
	if(signalType==NOSIGNAL_WORK_MODE)
	{
		stopAllMoter();													//信号中断 停掉所有电机
		riciveCboxFlag=true;
	}
	
	checkEnaSpeed();														//检测设备是否准备完毕
	if(!sendEnaSpeedOk)													//设备检测未完成 直接退出
		return;
	
	checkOffLimit();
	if(!offLimitSendOk)												//限位指令发送未完成 直接退出
		return;
	
	checkReInit();
	if(!reInitPosSendOk)											//零位重设指令发送未完成 直接退出
		return;

#ifdef 	NEW_DRIVER_PROGRAM
	checkSave();
	if(!saveSendOk)														//保存指令发送未完成 直接退出
		return;
#endif
	
	if(Terminal->reciveData())								//检测终端控制数据，如果成功接收一帧，则反馈数据并处理数据
	{
		riciveCboxFlag=true;
		disposeTerminalData();									//处理终端的数据
		updateSendTerminalData();								//更新要发送到终端的数据
		updateSendDriverData();									//更新要发送到所有设备的数据
		Terminal->sendcommand();								//发送数据到终端
	}
	disposeArmsData();											//接收并处理机械臂及其他设备反馈的数据
	disposUnderpanData();										//接收并处理底盘三电机以及电源管理模块的数据
	disposCodedDiscData();									//接收并处理绝对编码器的数据

	//更新U0指令的时间
	bigArmRotateM->	updateUspeedTime();
	bigArmPitchM	->updateUspeedTime();
	forearmPitchM->	updateUspeedTime();
	wristPitchM->		updateUspeedTime();
	wristRotateM->	updateUspeedTime();
	panTiltPitchM->	updateUspeedTime();
	panTiltRotateM->updateUspeedTime();
	fingerMediateM->updateUspeedTime();
	cameraPitchM->	updateUspeedTime();
}

void XbotApp::openUserInterrupt()
{
#ifdef USEPOTENTIOMETER                 //使用电位器
	CodedDisc->initADC();
#endif
	wireLessPort->open();						//和终端无线通信的串口
	wirePort->open();								//和终端有线通信的串口
	codedDiscPort->open();					//和码盘通信的串口
	armPort->open();								//和机械臂通信的串口
	underpanPort->open();						//和底盘三电机以及电源控制板通信的串口
	GPSPort->open();
	t1->start();
	t2->start();
	t3->start();
}

/**
  * 功  能：运行在定时器3中的函数，主要作用是发送数据到机器人的外部设备
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::runOnTime3()
{

	static unsigned char index=0;
	static unsigned char batteryIndex=0;

#ifndef NEWXBOT
	static bool bigArmPitchU0Flag=false;
	static bool forearmPitchU0Flag=false;
	static bool wristPitchPitchU0Flag=false;
#endif	

	sendSaveCommand();					//启动角度保存
	if(!saveSendOk)
		return;
	
	sendEnaSpeedCommand();			//使能运动关节
	if(!sendEnaSpeedOk)
		return;
	
	sendOffLimitCommand();			//启动取消限位
	if(!offLimitSendOk)
		return;	

	sendReInitCommand();				//启动零位重设
	if(!reInitPosSendOk)
		return;	
	
	sendWeaponCommand();				//启动武器发射 此处应该做个判断 所有电机速度为零时才启动
	if(!reWeaponSendOk)
		return;	
	
	if(riciveCboxFlag==false)
		return;
	
	switch(index)
	{
		case 0:
			bigArmRotateM->sendSpeedCommand();
			if(signalType==NOSIGNAL_WORK_MODE)
			{
				leftRunM->setPWMSpeed(0);
				leftRunM->sendSpeedCommand(0x03);
			}
			else
				leftRunM->sendSpeedCommand(0x02);
			break;
		case 1://大臂俯仰
#ifndef NEWXBOT
			if(bigArmPitchM->getPWMSpeed()==0)
				bigArmPitchM->sendSpeedCommand();
			else
			{
				if(bigArmPitchU0Flag)
				{
					bigArmPitchM->sendSpeedCommand();
					bigArmPitchU0Flag=false;
				}
				else
				{
					bigArmPitchM->sendAngleCommand(ANGLE_INQUIRE_ID);
					bigArmPitchU0Flag=true;
				}					
			}
#else
		 bigArmPitchM->sendSpeedCommand();
#endif						
			power->sendGetTemperatureCommand(0x00);
			break;
		case 2://小臂俯仰
#ifndef NEWXBOT
			if(forearmPitchM->getPWMSpeed()==0)
				forearmPitchM->sendSpeedCommand();
			else
			{
				if(forearmPitchU0Flag)
				{
					forearmPitchM->sendSpeedCommand();
					forearmPitchU0Flag=false;
				}
				else
				{
					forearmPitchM->sendAngleCommand(ANGLE_INQUIRE_ID);
					forearmPitchU0Flag=true;
				}
			}
#else
			forearmPitchM->sendSpeedCommand();
#endif
			if(signalType==NOSIGNAL_WORK_MODE)
			{
				rightRunM->setPWMSpeed(0);
				rightRunM->sendSpeedCommand(0x03);
			}
			else
				rightRunM->sendSpeedCommand(0x02);
			break;
		case 3:
#ifndef NEWXBOT
			if(wristPitchM->getPWMSpeed()==0)
			{
				wristPitchM->sendSpeedCommand();
			}
			else
			{
				if(wristPitchPitchU0Flag)
				{
					wristPitchM->sendSpeedCommand();
					wristPitchPitchU0Flag=false;
				}
				else
				{
					wristPitchM->sendAngleCommand(ANGLE_INQUIRE_ID);
					wristPitchPitchU0Flag=true;
				}
			}
#else
			wristPitchM->sendSpeedCommand();
#endif
			power->sendGetTemperatureCommand(0x01);
			break;
		case 4:
			wristRotateM->sendSpeedCommand();
			if(signalType==NOSIGNAL_WORK_MODE)
			{
				supportArmM->setPWMSpeed(0);
				supportArmM->sendSpeedCommand(0x03);
			}
			else
				supportArmM->sendSpeedCommand(0x02);
			break;
		case 5:
			panTiltPitchM->sendSpeedCommand();
			power->sendGetTemperatureCommand(0x02);
			break;
		case 6:
// 			panTiltRotateM->sendSpeedCommand(0x01);
			panTiltRotateM->sendSpeedCommand();
			leftRunM->sendSpeedCommand(SPEED_INQUIRE_ID); //查询速度
			break;
		case 7:
			fingerMediateM->sendSpeedCommand();
			break;
		case 8:
			cameraPitchM->sendSpeedCommand();
			rightRunM->sendSpeedCommand(SPEED_INQUIRE_ID); //查询速度
			break;
		case 9:
			OtherDevice->sendOtherDeviceCommand();
			break;
		case 10://发送自动线缆盘的命令
#ifdef NEWOPTICALBOBBIN
			if(signalType==WIRE_WORK_MODE)									//有线模式
				opticalBobbinDevice->sendOpticalBobbinCommand();
#endif
			power->sendGetEctQuantityCommand(batteryIndex);			//发送电量查询命令,轮询四个电池
			batteryIndex++;
			batteryIndex&=0x03;
			break;
// 		default:
// 			break;
	}
	index++;
	if(index==11)
	{
		index=0;
		riciveCboxFlag=false;
	}
}

/**
  * 功  能：运行在定时器4中的函数，主要作用是发送码盘角度查询命令以及GPS等的查询信息
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::runOnTime4()
{
	
/*测试看门狗	*/
// 	GPSPort->writeLine("this is time4 run!\r\n");
// 	while(1)
// 	{
// 	}
	power->sendPowerOnOffCommand();								//
	#ifndef USEPOTENTIOMETER  										//没有使用电位器的情况
		CodedDisc->sendCodeDiscCommand();							//发送绝对码盘的数据查询指令
	#endif
	//gpsServe->sendGetGpsCommand();					 		//发送GPS和IMU数据	备用接口
	gpsDevice->sendsetLEDColorCommand();

	if(signalType==WIRELESS_WORK_MODE)
	{
		led_1->reverseLight();
	}
	else if(signalType==WIRE_WORK_MODE)
	{
		led_2->reverseLight();
	}
	else
	{
		led_1->setLightOff();
		led_2->setLightOff();
	}
}

/**
  * 功  能：发送取消电机限位命令，每个设备最多发送SEND_CHECK_TIME_MAX次
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::sendOffLimitCommand()
{
	//只能限位一次：
	if(offLimitSendOk)
		return;
	
	if(checkTime[0]<SEND_CHECK_TIME_MAX)
	{
		checkTime[0]++;
		bigArmRotateM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[0]<CHECK_TIME_MAX)
	{
		checkTime[0]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
	
	if(checkTime[1]<SEND_CHECK_TIME_MAX)
	{
		checkTime[1]++;
		bigArmPitchM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[1]<CHECK_TIME_MAX)
	{
		checkTime[1]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}

	if(checkTime[2]<SEND_CHECK_TIME_MAX)
	{
		checkTime[2]++;
		forearmPitchM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[2]<CHECK_TIME_MAX)
	{
		checkTime[2]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}

	if(checkTime[3]<SEND_CHECK_TIME_MAX)
	{
		checkTime[3]++;
		wristPitchM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[3]<CHECK_TIME_MAX)
	{
		checkTime[3]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}

	if(checkTime[4]<SEND_CHECK_TIME_MAX)
	{
		checkTime[4]++;
		wristRotateM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[4]<CHECK_TIME_MAX)
	{
		checkTime[4]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[5]<SEND_CHECK_TIME_MAX)
	{
		checkTime[5]++;
		panTiltPitchM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[5]<CHECK_TIME_MAX)
	{
		checkTime[5]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[6]<SEND_CHECK_TIME_MAX)
	{
		checkTime[6]++;
		panTiltRotateM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[6]<CHECK_TIME_MAX)
	{
		checkTime[6]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}

	if(checkTime[7]<SEND_CHECK_TIME_MAX)
	{
		checkTime[7]++;
		fingerMediateM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[7]<CHECK_TIME_MAX)
	{
		checkTime[7]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
	offLimitSendOk=true;//发送取消限位完毕
}
/**
  * 功  能：发送重设零位指令 根据开关宏可以选定哪些关节重设
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::sendReInitCommand()
{
	if(reInitPosSendOk)
		return;
#ifdef RE_INIT_ARM1
	if(checkTime[0]<SEND_CHECK_TIME_MAX)
	{
		checkTime[0]++;
		bigArmRotateM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[0]<CHECK_TIME_MAX)
	{
		checkTime[0]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
#endif

#ifdef RE_INIT_ARM2
	if(checkTime[1]<SEND_CHECK_TIME_MAX)
	{
		checkTime[1]++;
		bigArmPitchM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[1]<CHECK_TIME_MAX)
	{
		checkTime[1]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
#endif

#ifdef RE_INIT_ARM3
	if(checkTime[2]<SEND_CHECK_TIME_MAX)
	{
		checkTime[2]++;
		forearmPitchM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[2]<CHECK_TIME_MAX)
	{
		checkTime[2]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
#endif

#ifdef RE_INIT_ARM4
	if(checkTime[3]<SEND_CHECK_TIME_MAX)
	{
		checkTime[3]++;
		wristPitchM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[3]<CHECK_TIME_MAX)
	{
		checkTime[3]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
#endif

#ifdef RE_INIT_ARM5
	if(checkTime[4]<SEND_CHECK_TIME_MAX)
	{
		checkTime[4]++;
		wristRotateM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[4]<CHECK_TIME_MAX)
	{
		checkTime[4]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
#endif

#ifdef RE_INIT_ARM6
	if(checkTime[5]<SEND_CHECK_TIME_MAX)
	{
		checkTime[5]++;
		panTiltPitchM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[5]<CHECK_TIME_MAX)
	{
		checkTime[5]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
#endif
	
#ifdef RE_INIT_ARM7
	if(checkTime[6]<SEND_CHECK_TIME_MAX)
	{
		checkTime[6]++;
		panTiltRotateM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[6]<CHECK_TIME_MAX)
	{
		checkTime[6]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
#endif

#ifdef RE_INIT_ARM8
	if(checkTime[7]<SEND_CHECK_TIME_MAX)
	{
		checkTime[7]++;
		fingerMediateM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[7]<CHECK_TIME_MAX)
	{
		checkTime[7]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}
#endif
	reInitPosSendOk=true;//发送重设零位完毕
}

/**
  * 功  能：发送保存设置命令 只有关机时才启用
  * 参  数：无
  * 返回值：无
  * 备  注：最小延时时间：600+8*150+200=
  */
void XbotApp::sendSaveCommand()
{
#ifdef NEW_DRIVER_PROGRAM
	if(saveSendOk)
		return;
	if(checkTime[9]<3)
	{
		checkTime[9]++;
		SysTick_DelayMs(100);				//延时600MS，保证电机停止
		return;
	}
	if(checkTime[0]<SEND_CHECK_TIME_MAX)
	{
		checkTime[0]++;
		bigArmRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[0]<CHECK_TIME_MAX)
	{
		checkTime[0]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}
	
	if(checkTime[1]<SEND_CHECK_TIME_MAX)
	{
		checkTime[1]++;
		bigArmPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[1]<CHECK_TIME_MAX)
	{
		checkTime[1]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[2]<SEND_CHECK_TIME_MAX)
	{
		checkTime[2]++;
		forearmPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[2]<CHECK_TIME_MAX)
	{
		checkTime[2]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[3]<SEND_CHECK_TIME_MAX)
	{
		checkTime[3]++;
		wristPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[3]<CHECK_TIME_MAX)
	{
		checkTime[3]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[4]<SEND_CHECK_TIME_MAX)
	{
		checkTime[4]++;
		wristRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[4]<CHECK_TIME_MAX)
	{
		checkTime[4]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[5]<SEND_CHECK_TIME_MAX)
	{
		checkTime[5]++;
		panTiltPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[5]<CHECK_TIME_MAX)
	{
		checkTime[5]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[6]<SEND_CHECK_TIME_MAX)
	{
		checkTime[6]++;
		panTiltRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[6]<CHECK_TIME_MAX)
	{
		checkTime[6]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[7]<SEND_CHECK_TIME_MAX)
	{
		checkTime[7]++;
		fingerMediateM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[7]<CHECK_TIME_MAX)
	{
		checkTime[7]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}
	else if(checkTime[8]<1)
	{
		checkTime[8]=1;
		SysTick_DelayMs(2000);				//延时2000MS，保证驱动器有足够的时间保存角度
		power-> shutDown();
		power->sendPowerOnOffCommand();
		return;
	}
	else
	{
		return;
	}

#else
	if(saveSendOk)
		return;
	static uint8_t index=0x00;
	if(index==0x00)
	{
		t1->stop();
		t3->stop();
		t2->setTimeOut(5);
		bigArmRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x01)
	{
		bigArmPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x02)
	{
		forearmPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x03)
	{
		wristPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x04)
	{
		wristRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x05)
	{
		panTiltPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x06)
	{
		panTiltRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x07)
	{
		fingerMediateM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 
	{
		SysTick_DelayMs(5000);				//延时2000MS，保证驱动器有足够的时间保存角度
		SysTick_DelayMs(5000);				//延时2000MS，保证驱动器有足够的时间保存角度
		power-> shutDown();
		power->sendPowerOnOffCommand();
		return;
	}
#endif
}
/**
  * 功  能：发送武器发射命令
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::sendWeaponCommand()
{
	if(reWeaponSendOk)
		return;
	static uint8_t index=0x00;
	if(index<0x0a)
	{
		OtherDevice->sendWeaponControlCommand();
		index++;
		return;
	}
	else 
	{
		reWeaponSendOk=true;
		index=0x00;
	}
}

/**
  * 功  能：发送使能速度指令
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::sendEnaSpeedCommand()
{
	if(sendEnaSpeedOk)
		return;

	if(checkTime[0]<SEND_CHECK_TIME_MAX)
	{
		checkTime[0]++;
		bigArmRotateM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[0]<CHECK_TIME_MAX)
	{
		checkTime[0]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
	
	if(checkTime[1]<SEND_CHECK_TIME_MAX)
	{
		checkTime[1]++;
		bigArmPitchM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[1]<CHECK_TIME_MAX)
	{
		checkTime[1]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[2]<SEND_CHECK_TIME_MAX)
	{
		checkTime[2]++;
		forearmPitchM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[2]<CHECK_TIME_MAX)
	{
		checkTime[2]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[3]<SEND_CHECK_TIME_MAX)
	{
		checkTime[3]++;
		wristPitchM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[3]<CHECK_TIME_MAX)
	{
		checkTime[3]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[4]<SEND_CHECK_TIME_MAX)
	{
		checkTime[4]++;
		wristRotateM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[4]<CHECK_TIME_MAX)
	{
		checkTime[4]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[5]<SEND_CHECK_TIME_MAX)
	{
		checkTime[5]++;
		panTiltPitchM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[5]<CHECK_TIME_MAX)
	{
		checkTime[5]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	

	if(checkTime[6]<SEND_CHECK_TIME_MAX)
	{
		checkTime[6]++;
		panTiltRotateM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[6]<CHECK_TIME_MAX)
	{
		checkTime[6]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}

	if(checkTime[7]<SEND_CHECK_TIME_MAX)
	{
		checkTime[7]++;
		fingerMediateM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[7]<CHECK_TIME_MAX)
	{
		checkTime[7]++;//预留CHECK_TIME_MAX-SEND_CHECK_TIME_MAX个周期 保证充足的时间检测
		return;
	}	
	sendEnaSpeedOk=true;//发送完毕
	for(int i=0;i<13;i++)
		checkTime[i]=0;
}
/**
  * 功  能：检测取消限位的反馈
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::checkOffLimit()
{
	uint8_t *temData=NULL;
	uint8_t armDataNum=ARM_PORT_NUM-1;
	if(offLimitSendOk)
		return;
	if(checkTime[0]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x00&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[0]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[1]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x01&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[1]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[2]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x02&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[2]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[3]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x03&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[3]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[4]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x04&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[4]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[5]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x05&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[5]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[6]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x06&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[6]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[7]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x07&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[7]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	offLimitSendOk=true;
	limitFlag=false;
}

/**
  * 功  能：检测重设零位指令的反馈
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::checkReInit()
{
	uint8_t *temData=NULL;
	uint8_t armDataNum=ARM_PORT_NUM-1;
	if(reInitPosSendOk)
		return;
#ifdef RE_INIT_ARM1
	if(checkTime[0]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x00&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[0]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM2
	if(checkTime[1]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x01&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[1]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM3
	if(checkTime[2]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x02&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[2]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM4
	if(checkTime[3]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x03&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[3]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM5
	if(checkTime[4]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x04&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[4]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM6
	if(checkTime[5]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x05&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[5]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM7
	if(checkTime[6]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x06&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[6]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM8
	if(checkTime[7]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x07&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[7]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	reInitPosSendOk=true;
}
/**
  * 功  能：检测保存角度指令的反馈，该函数没有使用，作为改进型驱动器的备用
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::checkSave()
{
	uint8_t *temData=NULL;
	uint8_t armDataNum=ARM_PORT_NUM-1;
	if(saveSendOk)
		return;
	if(checkTime[0]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x00&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[0]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[1]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x01&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[1]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[2]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x02&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[2]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[3]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x03&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[3]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[4]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x04&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[4]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[5]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x05&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[5]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[6]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x06&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[6]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[7]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x07&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[7]=CHECK_TIME_MAX;
			}
		}
		return;
	}
// 	saveSendOk=true;
}

/**
  * 功  能：检测使能速度指令是否发送完毕
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::checkEnaSpeed()
{
	uint8_t *temData=NULL;
	uint8_t armDataNum=ARM_PORT_NUM-1;
	if(sendEnaSpeedOk)
		return;
	if(checkTime[0]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x00&&temData[2]==FB_ENASPEED_ID)
			{
				fBbigArmRotateA->DATA_8[1]=temData[3];
				fBbigArmRotateA->DATA_8[0]=temData[4];
				checkTime[0]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[1]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x01&&temData[2]==FB_ENASPEED_ID)
			{
				fBbigArmPitchA->DATA_8[1]=temData[3];
				fBbigArmPitchA->DATA_8[0]=temData[4];
				checkTime[1]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[2]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x02&&temData[2]==FB_ENASPEED_ID)
			{
				fBforearmPitchA->DATA_8[1]=temData[3];
				fBforearmPitchA->DATA_8[0]=temData[4];
				checkTime[2]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[3]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x03&&temData[2]==FB_ENASPEED_ID)
			{
				fBwristPitchA->DATA_8[1]=temData[3];
				fBwristPitchA->DATA_8[0]=temData[4];
				checkTime[3]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[4]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x04&&temData[2]==FB_ENASPEED_ID)
			{
				fBwristRotateA->DATA_8[1]=temData[3];
				fBwristRotateA->DATA_8[0]=temData[4];
				checkTime[4]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[5]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x05&&temData[2]==FB_ENASPEED_ID)
			{
				fBpanTiltPitchA->DATA_8[1]=temData[3];
				fBpanTiltPitchA->DATA_8[0]=temData[4];
				checkTime[5]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[6]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x06&&temData[2]==FB_ENASPEED_ID)
			{
				fBpanTiltRotateA->DATA_8[1]=temData[3];
				fBpanTiltRotateA->DATA_8[0]=temData[4];
				checkTime[6]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[7]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x07&&temData[2]==FB_ENASPEED_ID)
			{
				fBfingerMediateA->DATA_8[1]=temData[3];
				fBfingerMediateA->DATA_8[0]=temData[4];
				checkTime[7]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	sendEnaSpeedOk=true;
}
/**
  * 功  能：重启取消限位命令
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::resetOffLimit()
{
// 	limitFlag=false;
	offLimitSendOk=false;
	for(int i=0;i<CHECK_DRIVER_NUM;i++)//将检测时间数组清零
	{
		checkTime[i]=0;
	}
}
/**
  * 功  能：重启零位设置命令
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::resetReInit()
{
	reInitPosSendOk=false;
	for(int i=0;i<CHECK_DRIVER_NUM;i++)//将检测时间数组清零
	{
		checkTime[i]=0;
	}
}

/**
  * 功  能：重启角度保存命令
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::resetSave()
{
	Timer::stop(TIM3); //关闭定时器3
	t2->setTimeOut(150);
	Timer::start(TIM3); //打开定时器3
	Timer::start(TIM4); //打开定时器4
	
	if(workModel==MIRROR)	
	{
		workModel=NORMAL;
	}
 	saveSendOk=false;
	for(int i=0;i<CHECK_DRIVER_NUM;i++)//将检测时间数组清零
	{
		checkTime[i]=0;
	}
}
/**
  * 功  能：重启武器发射命令
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::resetWeapon()
{
	reWeaponSendOk=false;
}

/**
  * 功  能：重启使能速度指令
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::resetEnaSpeed()
{
	sendEnaSpeedOk=false;
	for(int i=0;i<CHECK_DRIVER_NUM;i++)//将检测时间数组清零
	{
		checkTime[i]=0;
	}
}
/**
  * 功  能：处理终端控制命令
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::disposeTerminalData()
{
	uint8_t* temData=Terminal->getReciveData();	// 获取终端反馈的数据 并暂存
	//先检测工作模式
	if(temData[1]==0x30&&temData[2]==0xAA&&temData[3]==0xBB&&temData[4]==0xCC&&temData[5]==0xDD) \
		//&&temData[6]==0x00&&temData[7]==0x00&&temData[8]==0x00&&temData[9]==0x00&&temData[10]==0x00&&temData[11]==0x00)
	{
		workModel=MIRROR;					//切换到镜像模式 启动透明传输
		t2->stop();
		t3->stop();
	}
	else if(temData[1]==0x30&&temData[2]==0x11&&temData[3]==0x22&&temData[4]==0x33&&temData[5]==0x44) \
		//&&temData[6]==0x00&&temData[7]==0x00&&temData[8]==0x00&&temData[9]==0x00&&temData[10]==0x00&&temData[11]==0x00)
	{
		resetOffLimit();
	}
	else if(temData[1]==0x30&&temData[2]==0x55&&temData[3]==0x66&&temData[4]==0x77&&temData[5]==0x88) \
		//&&temData[6]==0x00&&temData[7]==0x00&&temData[8]==0x00&&temData[9]==0x00&&temData[10]==0x00&&temData[11]==0x00)
	{
		resetReInit();
	}
	else if(temData[1]==0x50&&temData[2]==0xAA&&temData[3]==0xBB&&temData[4]==0xCC&&temData[5]==0xDD \
		&&temData[6]==0xEE&&temData[7]==0xFF&&temData[8]==0x11&&temData[9]==0x22&&temData[10]==0x33&&temData[11]==0x44)
	{
		resetWeapon();
	}
	else	//正常指令
	{
		workModel=NORMAL;
		if((temData[9]&0x0f)==0x00)//模式控制位全为0
		{	
			workId=TTTModel;
		}
		else 
		{
			if((temData[9]&0x08)==0x08)//摆臂模式控制位为1
			{
				if((temData[6]&0x07)==0x01)
				{
					if((temData[4]&0x07)==0x00)
						workId=HHHModel;
					else
						workId=SSSModel;
				}
				else if((temData[6]&0x07)==0x02)
				{
					if((temData[4]&0x07)==0x00)
						workId=IIIModel;
					else
						workId=SSSModel;
				}
				else if((temData[6]&0x07)==0x03)
				{
					if((temData[4]&0x07)==0x00)
						workId=JJJModel;
					else
					{
						if((temData[4]&0x07)==0x03&&(temData[9]&0x04)==0x04)
							workId=CCCModel;
						else
							workId=SSSModel;
					}
				}
				else if((temData[6]&0x07)==0x04)
				{
					if((temData[4]&0x07)==0x00)
						workId=KKKModel;
				}
				else if((temData[6]&0x07)==0x05)
				{
					if((temData[4]&0x07)==0x00)
						workId=LLLModel;
					else
					{
						if((temData[4]&0x07)==0x01&&(temData[9]&0x04)==0x04)
							workId=AAAModel;
						else if((temData[4]&0x07)==0x02&&(temData[9]&0x04)==0x04)
							workId=BBBModel;
						else if((temData[4]&0x07)==0x04&&(temData[9]&0x04)==0x04)
							workId=DDDModel;
						else if((temData[4]&0x07)==0x05&&(temData[9]&0x04)==0x04)
							workId=EEEModel;
						else
							workId=SSSModel;
					}
				}
				else
				{
					workId=SSSModel;
				}
			}
			else if((temData[9]&0x0C)==0x04)//机械臂模式控制位为1 其余的控制模式位为0 启动三维控制模式
			{
				if((temData[4]&0x07)==0x07)
				{
					if((temData[5]&0x07)!=0x00)
					{
						if((temData[5]&0x08)==0x00)
						{
							workId=ZUUModel;				//Z向上模式
						}
						else
						{
							workId=ZDDModel;				//Z向下模式
						}
					}
					else if((temData[7]&0x07)!=0x00)
					{
						if((temData[7]&0x08)==0x00)
						{
							workId=YFFModel;				//Y向前模式
						}
						else
						{
							workId=YBBModel;				//Y向后模式
						}
					}
					else if((temData[7]&0x70)!=0x00)
					{
						if((temData[7]&0x80)==0x00)
						{
							workId=XRRModel;				//X向右模式
						}
						else
						{
							workId=XLLModel;				//X向左模式
						}
					}
					else
						workId=SSSModel;
				}
				else if((temData[4]&0x07)==0x06)
				{
					workId=XYZModel;
				}
				else
					workId=SSSModel;
			}
			else if((temData[9]&0x03)==0x02)//收线模式
			{
				workId=MMMModel;
			}
			else if((temData[9]&0x03)==0x01)//放线模式
			{
				workId=NNNModel;
			}
		}
		for(int i=0;i<TERMINAL_FRAME_LEN;i++)
		{
			fBTerminalData[i]=temData[i];
		}
	}
}

/**
  * 功  能：处理机械臂反馈的数据
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::disposeArmsData()
{
	if(bigArmRotateM->getNumCounter()>10)//连续10次没有反馈
	{
		bigArmRotateM->setErrorFlag(0x08);
	}
	if(bigArmPitchM->getNumCounter()>10)
	{
		bigArmPitchM->setErrorFlag(0x08);
	}
	if(forearmPitchM->getNumCounter()>10)
	{
		forearmPitchM->setErrorFlag(0x08);
	}
	if(wristPitchM->getNumCounter()>10)
	{
		wristPitchM->setErrorFlag(0x08);
	}
	if(wristRotateM->getNumCounter()>10)
	{
		wristRotateM->setErrorFlag(0x08);
	}
	if(panTiltPitchM->getNumCounter()>10)
	{
		panTiltPitchM->setErrorFlag(0x08);
	}
	if(panTiltRotateM->getNumCounter()>10)
	{
		panTiltRotateM->setErrorFlag(0x08);
	}
	if(fingerMediateM->getNumCounter()>10)
	{
		fingerMediateM->setErrorFlag(0x08);
	}
	if(cameraPitchM->getNumCounter()>10)
	{
		cameraPitchM->setErrorFlag(0x08);
	}
	if(OtherDevice->getNumCounter()>10)
	{
		OtherDevice->setErrorFlag(0x08);
	}
	if(opticalBobbinDevice->getNumCounter()>10)//接收不到数据，默认我普通有线
	{
// 		opticalBobbinDevice->setErrorFlag(0x08);
		WireType=false;
	}
// 	if(signalType==WIRELESS_WORK_MODE)//无线的情况下
// 	{
// 		opticalBobbinDevice->setErrorFlag(0x00);
// 	}
	if(!BaseControl::reciveData(armPort))		  //接收并处理机械臂及其他设备反馈的数据
	{
		return;
	}
	uint8_t* temData=BaseControl::getReciveData(ARM_PORT_NUM-1);//获取串口接收的数据
	uint8_t temError=(temData[1]&0xf0)>>4;
	if(temError!=0)
		temError+=0x08;
	
	
#ifdef NEWXBOT
	if(temData[2]==FB_POS_SPEED_ID||temData[2]==FB_POS_ANGLE_ID||temData[2]==FB_POS_USPEED_ID)//反馈的是由带回传的速度设定指令而触发的角度反馈 0x41 0x43 0x68
#else
	if(temData[2]==FB_POS_SPEED_ID||temData[2]==FB_POS_ANGLE_ID)//反馈的是由带回传的速度设定指令而触发的角度反馈 0x41 0x68
#endif
	{
		switch(temData[1]&0x0f)
		{
			case BIG_ARM_ROTATE_DDR:											//大臂旋转
				bigArmRotateM->resetNumCounter();
				bigArmRotateM->setErrorFlag(temError);
				fBbigArmRotateA->DATA_8[1]=temData[3];			//高八位
				fBbigArmRotateA->DATA_8[0]=temData[4];			//低八位
				break;
			
			case BIG_ARM_PITCH_ADDR:											//大臂俯仰
				bigArmPitchM->resetNumCounter();
				bigArmPitchM->setErrorFlag(temError);
				fBbigArmPitchA->DATA_8[1]=temData[3];				//高八位
				fBbigArmPitchA->DATA_8[0]=temData[4];				//低八位
				break;
			
			case FORE_ARM_PITCH_DDR:											//小臂俯仰
				forearmPitchM->resetNumCounter();
				forearmPitchM->setErrorFlag(temError);
				fBforearmPitchA->DATA_8[1]=temData[3];			//高八位
				fBforearmPitchA->DATA_8[0]=temData[4];			//低八位
				break;
			
			case WRIST_PITCH_DDR:													//手腕俯仰
				wristPitchM->resetNumCounter();
				wristPitchM->setErrorFlag(temError);
				fBwristPitchA->DATA_8[1]=temData[3];				//高八位
				fBwristPitchA->DATA_8[0]=temData[4];				//低八位
				break;
			
			case WRIST_ROTATE_DDR:												//手腕旋转
				wristRotateM->resetNumCounter();
				wristRotateM->setErrorFlag(temError);
				fBwristRotateA->DATA_8[1]=temData[3];				//高八位
				fBwristRotateA->DATA_8[0]=temData[4];				//低八位
				break;
			
			case PAN_TILT_PITCH_DDR:											//云台俯仰
				panTiltPitchM->resetNumCounter();
				panTiltPitchM->setErrorFlag(temError);
				fBpanTiltPitchA->DATA_8[1]=temData[3];			//高八位
				fBpanTiltPitchA->DATA_8[0]=temData[4];			//低八位
				break;
			
			case PAN_TILT_ROTATE_DDR:											//云台旋转
				panTiltRotateM->resetNumCounter();
				panTiltRotateM->setErrorFlag(temError);
				fBpanTiltRotateA->DATA_8[1]=temData[3];			//高八位
				fBpanTiltRotateA->DATA_8[0]=temData[4];			//低八位
				break;
			
			case FINGER_MEDIATE_DDR:											//手爪捏合
				fingerMediateM->resetNumCounter();
				fingerMediateM->setErrorFlag(temError);
				fBfingerMediateA->DATA_8[1]=temData[3];			//高八位
				fBfingerMediateA->DATA_8[0]=temData[4];			//低八位
				break;
			case CAMERA_PITCH_DDR:												//底座相机俯仰 目前没有角度反馈
				cameraPitchM->resetNumCounter();
				cameraPitchM->setErrorFlag(temError);
				break;
			default:
				break;
		}
	}
	if(workId==CCCModel)//在C模式下
	{
		if(ABS(XBOT_CCCC_ARM2-(fBbigArmPitchA->DATA_16))<600&&(bigArmPitchM->getErrorFlag()==0x0b||bigArmPitchM->getErrorFlag()==0x0c))
		{
			bigArmPitchM->setErrorFlag(0x00);
		}
		if(ABS(XBOT_CCCC_ARM3-(fBforearmPitchA->DATA_16))<600&&(forearmPitchM->getErrorFlag()==0x0b||forearmPitchM->getErrorFlag()==0x0c))
		{
			forearmPitchM->setErrorFlag(0x00);
		}
		if(ABS(XBOT_CCCC_ARM4-(fBwristPitchA->DATA_16))<600&&(wristPitchM->getErrorFlag()==0x0b||wristPitchM->getErrorFlag()==0x0c))
		{
			wristPitchM->setErrorFlag(0x00);
		}
	}
	if((temData[1]&0x0f)==OTHER_DEVICE_DDR)
	{
		OtherDevice->resetNumCounter();
		OtherDevice->setErrorFlag(temError);
	}
	if((temData[1]&0x0f)==0x0A)//线缆盘的反馈
	{
		opticalBobbinDevice->resetNumCounter();
		opticalBobbinDevice->setErrorFlag(temError);
		opticalBobbinDevice->setWireLength(temData[4]);
		WireType=true;																//接收到数据 为智能线缆盘
	}
}

/**
  * 功  能：处理底盘设备反馈的数据
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::disposUnderpanData()
{
	static int16_t timeIndex=0;
	if(timeIndex<5000)
	{
		timeIndex++;
	}
	else if(timeIndex==5000)
	{
		timeIndex++;
		power->resetNumCounter();
	}
	else
	{
		if(power->getNumCounter()>10)
		{
			power->setErrorFlag(0x08);
		}
	}
	if(leftRunM->getNumCounter()>10)//连续10次没有反馈
	{
		leftRunM->setErrorFlag(0x08);
	}
	if(rightRunM->getNumCounter()>10)
	{
		rightRunM->setErrorFlag(0x08);
	}
	if(supportArmM->getNumCounter()>10)
	{
		supportArmM->setErrorFlag(0x08);
	}

	
	if(!BaseControl::reciveData(underpanPort)) //接收并处理底盘三电机以及电源管理模块的数据
	{
		return;
	}
	uint8_t* temData=BaseControl::getReciveData(UNDERPAN_PORT_NUM-1);	//获取串口接收的数据
	uint8_t temError=(temData[1]&0xf0)>>4;
	(temError==0)?(temError=0):(temError+=0x08);
	switch(temData[1]&0x0f)
	{
		case LEFTRUN_DDR: 		//左电机
			leftRunM->resetNumCounter();
			if(temError==0)
			{
					if(FBTemperature_1>WARNINGTEMPERATURE)
					{
						leftRunM->setErrorFlag(0x09);
					}
					else
						leftRunM->setErrorFlag(0);
			}
			else
			{
				leftRunM->setErrorFlag(temError);
			}
			if(temData[2]==FB_SPEED_ID)										//左电机速度
			{
				fBLeftSpeed->DATA_8[1]=temData[3];					//高八位
				fBLeftSpeed->DATA_8[0]=temData[4];					//低八位
			}
			break;
		case RIGHTRUN_DDR: 		//右电机
			rightRunM->resetNumCounter();
		
			if(temError==0)
			{
					if(FBTemperature_2>WARNINGTEMPERATURE)
					{
						rightRunM->setErrorFlag(0x09);
					}
					else
						rightRunM->setErrorFlag(0);
			}
			else
			{
				rightRunM->setErrorFlag(temError);
			}
			if(temData[2]==FB_SPEED_ID)										//左电机速度
			{
				fBRightSpeed->DATA_8[1]=temData[3];					//高八位
				fBRightSpeed->DATA_8[0]=temData[4];					//低八位
			}
			break;
		case SUPPORT_ARM_DDR:	//支臂电机
			supportArmM->resetNumCounter();
			if(temError==0)
			{
					if(FBTemperature_3>WARNINGTEMPERATURE)
					{
						supportArmM->setErrorFlag(0x09);
					}
					else
						supportArmM->setErrorFlag(0);
			}
			else
			{
				supportArmM->setErrorFlag(temError);
			}
			break;
		case POWER_DDR:				//电源控制板
			power->resetNumCounter();
			power->setErrorFlag(temError);
			if(temData[2]==FB_ECTQ_ID)														//反馈的是电压值
			{
				if((temData[3]&0xc0)==0x00)													//电池1电量
				{
					fBEctQuantity_1->DATA_8[1]=(temData[3]&0x3f);			//高八位
					fBEctQuantity_1->DATA_8[0]=temData[4];						//低八位
				}
				else if((temData[3]&0xc0)==0x40)										//电池2电量
				{
					fBEctQuantity_2->DATA_8[1]=(temData[3]&0x3f);			//高八位
					fBEctQuantity_2->DATA_8[0]=temData[4];						//低八位
				}
				else if((temData[3]&0xc0)==0x80)										//电池3电量
				{
					fBEctQuantity_3->DATA_8[1]=(temData[3]&0x3f);			//高八位
					fBEctQuantity_3->DATA_8[0]=temData[4];						//低八位
				}
				else if((temData[3]&0xc0)==0xc0)										//电池4电量
				{
					fBEctQuantity_4->DATA_8[1]=(temData[3]&0x3f);			//高八位
					fBEctQuantity_4->DATA_8[0]=temData[4];						//低八位
				}
				ectQuantity=subEctQuantity();
				gpsDevice->setPowerLEDColorFromVoltage(ectQuantity);
	// 				if(gpsDevice->setPowerLEDColorFromVoltage(ectQuantity))//电压太小 自动关机并保存
	// 				{
	// 					resetSave();
	// 				}
// 				if(ectQuantity<118)//电压过低 报警
// 				{
// 					power->setErrorFlag(0x0c);
// 				}
			}
			else if(temData[2]==FB_TEMPERATURE_ID)										//反馈的是电机温度值
			{
				if((temData[3]&0xc0)==0x00)													//左电机温度
				{
					FBTemperature_1=temData[4];
				}
				else if((temData[3]&0xc0)==0x40)										//右电机温度
				{
					FBTemperature_2=temData[4];
				}
				else if((temData[3]&0xc0)==0x80)										//支臂电机温度
				{
					FBTemperature_3=temData[4];
				}
			}
			break;
		default:
			break;
	}
}


/**
  * 功  能：处理绝对编码盘设备反馈的数据
  * 参  数：无
  * 返回值：无
  * 
  */
void  XbotApp::disposCodedDiscData()
{
#ifndef USEPOTENTIOMETER                 //没有使用电位器
	if(CodedDisc->getNumCounter()>10)
	{
		CodedDisc->setErrorFlag(0x08);
	}
	else
	{
		CodedDisc->resetErrorFlag();
	}
	
	if(!CodedDisc->reciveData())								//接收并处理绝对编码器的数据
	{
		return;
	}
	fBDiscA->DATA_16=CodedDisc->getAngle()->DATA_16;
	CodedDisc->resetNumCounter();
#else																			//使用了电位器
	int temAngle=0;
	temAngle=CodedDisc->getADCAngle()*17/72;//转化为1024 一周的角度值
	if(temAngle<114) //909-1023
		temAngle=temAngle+909;
	else
		temAngle=temAngle-114;
	fBDiscA->DATA_16=temAngle;							//转化为和码盘一样的角度
#endif
}


/**
  * 功  能：更新发送到终端的数据
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::updateSendTerminalData()
{
	static int index=0;
	uint8_t temBuf[13]={0XA5,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XA5};
	temBuf[1]|=index;
	temBuf[2]=(uint8_t)((-fBLeftSpeed->DATA_16)/96); //*0.0142 近似为除以96  有符号数
	temBuf[3]=(uint8_t)((-fBRightSpeed->DATA_16)/96);
	if(index==0)
	{
		temBuf[4]=(uint8_t)((-(fBbigArmRotateA->DATA_16)/200+180)%180);										//回传大臂旋转角度 无符号数
		temBuf[5]=(uint8_t)((fBwristRotateA->DATA_16/200+180)%180);												//回传手腕旋转角度 无符号数
		temBuf[6]=(uint8_t)((fBfingerMediateA->DATA_16/200+180)%180);											//回传手爪捏合角度 无符号数
		temBuf[7]=(uint8_t)(fBEctQuantity_1->DATA_16/2);	  															//回传电池1电压 单位0.2v
		temBuf[8]=(power->getErrorFlag()<<4)|(OtherDevice->getErrorFlag()&0x0f);					//电源控制板+灯和摄像头等外设报警参数
		temBuf[9]=(bigArmRotateM->getErrorFlag()<<4)|(bigArmPitchM->getErrorFlag()&0x0f);	//大臂旋转+大臂俯仰报警参数
	}
	else if(index==1)
	{
		temBuf[4]=(uint8_t)((-fBbigArmPitchA->DATA_16/200+270)%180); 											//回传大臂俯仰角度 无符号数
		temBuf[5]=(uint8_t)((fBpanTiltPitchA->DATA_16/200+190)%180);											//回传云台俯仰角度 无符号数
		temBuf[6]=(uint8_t)(fBDiscA->DATA_U16*45/256);																		//回传绝对码盘的角度 无符号数
		temBuf[7]=(uint8_t)(fBEctQuantity_2->DATA_16/2);	  															//回传电池2电压 单位0.2v
		temBuf[8]=(opticalBobbinDevice->getErrorFlag()<<4)|(CodedDisc->getErrorFlag()&0x0f);			//线缆盘+支臂码盘报警参数
		temBuf[9]=(forearmPitchM->getErrorFlag()<<4)|(wristPitchM->getErrorFlag()&0x0f);					//小臂俯仰+手腕俯仰报警参数
	}
	else if(index==2)
	{
		temBuf[4]=(uint8_t)((-fBforearmPitchA->DATA_16/200+270)%180);											//回传小臂俯仰角度 无符号数
		temBuf[5]=(uint8_t)((fBpanTiltRotateA->DATA_16/200+180)%180);											//回传云台旋转角度 无符号数
		if(signalType==WIRE_WORK_MODE&&WireType==true)																		//有线和无线分别设置线缆盘剩余线长
		{
			temBuf[6]=opticalBobbinDevice->getWireLength();																	//线缆盘剩余线长
		}
		else// if(signalType==WIRELESS_WORK_MODE)
		{
			temBuf[6]=0;																																		//线缆盘剩余线长
		}
		temBuf[7]=(uint8_t)(fBEctQuantity_3->DATA_16/2);	  															//回传电池3电压 单位0.2v
		temBuf[8]=(leftRunM->getErrorFlag()<<4)|(rightRunM->getErrorFlag()&0x0f);								//左电机+右电机报警参数
		temBuf[9]=(wristRotateM->getErrorFlag()<<4)|(panTiltPitchM->getErrorFlag()&0x0f);				//手腕旋转+云台俯仰报警参数
	}
	else if(index==3)
	{
		temBuf[4]=(uint8_t)((fBwristPitchA->DATA_16/200+180)%180);												//回传手腕俯仰角度 无符号数
// 		temBuf[5]=(uint8_t)(fBcameraPitchA->DATA_16/200);																//回传前进相机俯仰角度  无符号数 暂时没有角度回传
		temBuf[5]=0x00;																																		//回传前进相机俯仰角度 暂时没有角度回传
		temBuf[6]=ectQuantity;																														//系统电压，既平均电压
		temBuf[7]=(uint8_t)(fBEctQuantity_4->DATA_16/2);	  															//回传电池4电压 单位0.2v
		temBuf[8]=(supportArmM->getErrorFlag()<<4)|(cameraPitchM->getErrorFlag()&0x0f);					//支臂电机+底座相机报警参数
		temBuf[9]=(panTiltRotateM->getErrorFlag()<<4)|(fingerMediateM->getErrorFlag()&0x0f);			//云台旋转+手抓夹持报警参数
	}

	for(int i=1;i<10;i++)//计算校验和
	{
		temBuf[12]+=temBuf[i];
	}
	Terminal->updateSendBuf(temBuf);
	index++;
	index&=0x03;
}
/**
  * 功  能：计算本体电压
  * 参  数：无
  * 返回值：本体电压
  * 
  */
uint8_t XbotApp::subEctQuantity()
{
	uint8_t index=0;
	uint16_t temSubEctQuantity=0;
	uint8_t temEctQuantity[4]={0};
	temEctQuantity[0]=(uint8_t)(fBEctQuantity_1->DATA_16/2);
	temEctQuantity[1]=(uint8_t)(fBEctQuantity_2->DATA_16/2);
	temEctQuantity[2]=(uint8_t)(fBEctQuantity_3->DATA_16/2);
	temEctQuantity[3]=(uint8_t)(fBEctQuantity_4->DATA_16/2);
	if(temEctQuantity[0]>50)
	{
		index++;
		temSubEctQuantity+=temEctQuantity[0];
	}
	if(temEctQuantity[1]>50)
	{
		index++;
		temSubEctQuantity+=temEctQuantity[1];
	}
		if(temEctQuantity[2]>50)
	{
		index++;
		temSubEctQuantity+=temEctQuantity[2];
	}
		if(temEctQuantity[3]>50)
	{
		index++;
		temSubEctQuantity+=temEctQuantity[3];
	}
	if(index==0)
		temSubEctQuantity=0;
	else
		temSubEctQuantity/=index;
	return (uint8_t)temSubEctQuantity;
}

/**
  * 功  能：更新发送到设备的数据
  * 参  数：无
  * 返回值：无
  * 
  */

void XbotApp::updateSendDriverData()
{	
	static bool CCCUFlag_1=false;
	static bool CCCUFlag_2=false;
	static bool CCCUFlag_3=false;	
	
	static uint16_t CCCUTime_1=0;
	static uint16_t CCCUTime_2=0;
	static uint16_t CCCUTime_3=0;	
	
	int temsetPanTiltPitchSpeed=0;
	int temsetPanTiltRotateSpeed=0;
// 	int temLeftSpeed;
// 	int temRightSpeed;
	int LandRMoterMaxSpeed=LRMOTERMAXSPEED_WIRELESS_WORK;
	stopAllMoter();
	
	//软件错误标志归零
	bigArmRotateM	->setErrorFlag_1(0x00);
	bigArmPitchM	->setErrorFlag_1(0x00);
	forearmPitchM	->setErrorFlag_1(0x00);
	wristPitchM		->setErrorFlag_1(0x00);
	panTiltPitchM	->setErrorFlag_1(0x00);
	fingerMediateM->setErrorFlag_1(0x00);
	supportArmM		->setErrorFlag_1(0x00);
	
#ifdef NEWOPTICALBOBBIN
	if(signalType==WIRE_WORK_MODE&&WireType==true)//有线和无线分别设置速度
	{
		LandRMoterMaxSpeed=LRMOTERMAXSPEED_WIRE_WORK;
	}
	else// if(signalType==WIRELESS_WORK_MODE)
	{
		LandRMoterMaxSpeed=LRMOTERMAXSPEED_WIRELESS_WORK;
	}
#endif
//行驶模式和抓取模式的判定
	if(fBbigArmPitchA->DATA_16<-800)
	{
		LandRMoterMaxSpeed=1500;
	}
	if((fBTerminalData[9]&0xc0)==0x40) //上仰
	{
		cameraPitchM->setSpeed(-5000);
	}
	else if((fBTerminalData[9]&0xc0)==0x80) //下俯
	{
		cameraPitchM->setSpeed(5000);
	}
	else
	{
		cameraPitchM->resetSpeed();
	}
	if(workId!=CCCModel)
	{
		//防止没压紧 当C模式到达最后一点点的时候，并且C模式还没有停止工作，让C模式继续工作
		CCCUTime_1=0;
		CCCUTime_2=0;
		CCCUTime_3=0;
		if((ABS(XBOT_CCCC_ARM2-(fBbigArmPitchA->DATA_16))<400)||(ABS(XBOT_CCCC_ARM3-(fBforearmPitchA->DATA_16))<400)||(ABS(XBOT_CCCC_ARM4-(fBwristPitchA->DATA_16))<400))
		{
			if((bigArmPitchM->getPWMSpeed()>0)||(forearmPitchM->getPWMSpeed()<0)||(wristPitchM->getPWMSpeed()<0))
			{
				return;
			}
		}
		bigArmPitchM->setPWMSpeed(0);
		forearmPitchM->setPWMSpeed(0);
		wristPitchM->setPWMSpeed(0);
		CCCUFlag_1=false;
		CCCUFlag_2=false;
		CCCUFlag_3=false;
	}

	//设置其他设备的参数
	if((fBTerminalData[10]&0x80)==0x80) //云台灯
	{
		OtherDevice-> headLightOn();
	}
	else
	{
		OtherDevice-> headLightOff();
	}

	if((fBTerminalData[10]&0x20)==0x20) //相机灯
	{
		OtherDevice-> floodLightOn();
	}
	else
	{
		OtherDevice-> floodLightOff();
	}
	
	if((fBTerminalData[10]&0x40)==0x40)//激光灯
	{
		OtherDevice-> laserSightOn();
	}
	else
	{
		OtherDevice-> laserSightOff();
	}
	
	OtherDevice-> setVideoSelect((fBTerminalData[11]&0xe0)>>5);
	OtherDevice-> setVideoZoom(fBTerminalData[11]&0x1f);
	

	if(fBTerminalData[8]&0x80)
	{
		fingerMediateM->setErrorFlag_1(setFingerMediateSpeed(-((int16_t)((fBTerminalData[8]&0x70)>>0x04)*1285)));
	}
	else
	{
		fingerMediateM->setErrorFlag_1(setFingerMediateSpeed((int16_t)((fBTerminalData[8]&0x70)>>0x04)*1285));
	}
		{
			/**
			*主要修正了左右电机不相等的后退速度产生的方向和习惯上相反的缺点
			*
			*/
// 			if((fBTerminalData[1]&0x0f)==0x0a)//两个电机都向后
// 			{
// 				rightRunM->setSpeed((int16_t)((fBTerminalData[3]*LandRMoterMaxSpeed)/160));
// 				leftRunM->setSpeed(-(int16_t)((fBTerminalData[2]*LandRMoterMaxSpeed)/160));
// 			}
// 			else if((fBTerminalData[1]&0x0f)==0x08)//摇杆左下↙修正 左电机向后
// 			{
// 				leftRunM->setSpeed(-(int16_t)((fBTerminalData[2]*LandRMoterMaxSpeed)/160)); 
// 				rightRunM->resetSpeed();
// 			}
// 			else if((fBTerminalData[1]&0x0f)==0x02)//摇杆右下↘修正 右电机向后
// 			{
// 				rightRunM->setSpeed((int16_t)((fBTerminalData[3]*LandRMoterMaxSpeed)/160));
// 				leftRunM ->resetSpeed();
// 			}
// 			else

			{
#ifdef NEWOPTICALBOBBIN
				if(opticalBobbinDevice->getWireLength()<5&&signalType==WIRE_WORK_MODE\
						&&(WireType==true)\
						&&(((fBTerminalData[1]&0x0f)==0x01)\
						||((fBTerminalData[1]&0x0f)==0x04)\
						||((fBTerminalData[1]&0x0f)==0x05)))//线缆盘中余下的线长不足5米 并且是智能有线控制 并且是前进状态
				{
					leftRunM->resetSpeed();
					rightRunM->resetSpeed();
				}
				else
#endif
				{
					if(fBTerminalData[2]>150)
						fBTerminalData[2]=150;
					if(fBTerminalData[3]>150)
						fBTerminalData[3]=150;
// 						temLeftSpeed=(fBTerminalData[3]*LandRMoterMaxSpeed)/150;
// 						temRightSpeed=(fBTerminalData[2]*LandRMoterMaxSpeed)/150;

						if((fBTerminalData[1]&0x03)==0x01)//左电机向前 
						rightRunM->setSpeed((int16_t)((fBTerminalData[3]*LandRMoterMaxSpeed)/150));
					else if((fBTerminalData[1]&0x03)==0x02)//左电机向后
						rightRunM->setSpeed(-(int16_t)((fBTerminalData[3]*LandRMoterMaxSpeed)/150));
					else
						rightRunM->resetSpeed();
					
 					if((fBTerminalData[1]&0x0c)==0x04)//右电机向前
 						leftRunM->setSpeed(-(int16_t)((fBTerminalData[2]*LandRMoterMaxSpeed)/150));
					else if((fBTerminalData[1]&0x0c)==0x08)//右电机向后
						leftRunM->setSpeed((int16_t)((fBTerminalData[2]*LandRMoterMaxSpeed)/150));
					else
						leftRunM->resetSpeed();				
					
					
				}
			}
		}
	switch((int)workId)
	{
		case TTTModel: 				//关节控制模式
			if(fBTerminalData[4]&0x77||fBTerminalData[5]&0x70)
				xyzFlag=false;
#ifdef NEWOPTICALBOBBIN
		if(signalType==WIRE_WORK_MODE)//线缆盘自动收放线
		{
			if((fBTerminalData[1]&0x0f)==0x0a||(fBTerminalData[1]&0x0f)==0x08||(fBTerminalData[1]&0x0f)==0x02)//两个电机都向后
			{
				opticalBobbinDevice->setWorkStatus(0x02);
				opticalBobbinDevice->setLeftSpeed((uint8_t)(ABS(fBLeftSpeed->DATA_16)/35));
				opticalBobbinDevice->setRightSpeed((uint8_t)(ABS(fBRightSpeed->DATA_16)/35));
			}
			else if((fBTerminalData[1]&0x0f)==0x05||(fBTerminalData[1]&0x0f)==0x01||(fBTerminalData[1]&0x0f)==0x04)//两个电机都向前
			{
				opticalBobbinDevice->setWorkStatus(0x01);
				opticalBobbinDevice->setLeftSpeed((uint8_t)(ABS(fBLeftSpeed->DATA_16)/35));
				opticalBobbinDevice->setRightSpeed((uint8_t)(ABS(fBRightSpeed->DATA_16)/35));
			}
			else if((fBTerminalData[1]&0x0f)==0x06)//右电机向前，左电机向后，左转 ||(fBTerminalData[1]&0x03)==0x02
			{
				opticalBobbinDevice->setWorkStatus(0x03);
				opticalBobbinDevice->setLeftSpeed((uint8_t)(ABS(fBLeftSpeed->DATA_16)/35));
				opticalBobbinDevice->setRightSpeed((uint8_t)(ABS(fBRightSpeed->DATA_16)/35));
			}
			else if((fBTerminalData[1]&0x0f)==0x09)//右电机向后，左电机向前，右转 ||(fBTerminalData[1]&0x03)==0x01
			{
				opticalBobbinDevice->setWorkStatus(0x04);
				opticalBobbinDevice->setLeftSpeed((uint8_t)(ABS(fBLeftSpeed->DATA_16)/35));
				opticalBobbinDevice->setRightSpeed((uint8_t)(ABS(fBRightSpeed->DATA_16)/35));
			}
			else
			{
				opticalBobbinDevice->setWorkStatus(0x00);
				opticalBobbinDevice->setLeftSpeed(0);
				opticalBobbinDevice->setRightSpeed(0);
			}
		}
#endif
		

			if(fBTerminalData[4]&0x80)
			{
				bigArmRotateM->setErrorFlag_1(setBigArmRotateSpeed((int16_t)((fBTerminalData[4]&0x70)>>0x04)*1142));
			}
			else
			{
				bigArmRotateM->setErrorFlag_1(setBigArmRotateSpeed(-((int16_t)((fBTerminalData[4]&0x70)>>0x04)*1142)));
			}

			if(fBTerminalData[4]&0x08)
			{
				bigArmPitchM->setErrorFlag_1(setBigArmPitchSpeed((int16_t)((fBTerminalData[4]&0x07)*714)));
			}
			else
			{
				bigArmPitchM->setErrorFlag_1(setBigArmPitchSpeed(-((int16_t)((fBTerminalData[4]&0x07)*714))));
			}

			if(fBTerminalData[5]&0x80)
			{
				forearmPitchM->setErrorFlag_1(setForearmPitchSpeed(-((int16_t)((fBTerminalData[5]&0x70)>>0x04)*714)));
			}
			else
			{
				forearmPitchM->setErrorFlag_1(setForearmPitchSpeed((int16_t)((fBTerminalData[5]&0x70)>>0x04)*714));
			}

			if(fBTerminalData[5]&0x08)
			{
				wristPitchM->setErrorFlag_1(setWristPitchSpeed(-((int16_t)((fBTerminalData[5]&0x07)*714))));
			}
			else
			{
				wristPitchM->setErrorFlag_1(setWristPitchSpeed((int16_t)((fBTerminalData[5]&0x07)*714)));
			}


			if(fBTerminalData[6]&0x80)
			{
				wristRotateM->setSpeed((int16_t)((fBTerminalData[6]&0x70)>>0x04)*1714);
			}
			else
			{
				wristRotateM->setSpeed(-((int16_t)((fBTerminalData[6]&0x70)>>0x04)*1714));
			}

			if(fBTerminalData[7]&0x08)
			{
				temsetPanTiltPitchSpeed=(int16_t)(fBTerminalData[7]&0x07);
				temsetPanTiltPitchSpeed=temsetPanTiltPitchSpeed*temsetPanTiltPitchSpeed*183;
				panTiltPitchM->setErrorFlag_1(setPanTiltPitchSpeed(temsetPanTiltPitchSpeed));
			}
			else
			{
				temsetPanTiltPitchSpeed=(int16_t)(fBTerminalData[7]&0x07);
				temsetPanTiltPitchSpeed=-temsetPanTiltPitchSpeed*temsetPanTiltPitchSpeed*183;
				panTiltPitchM->setErrorFlag_1(setPanTiltPitchSpeed(temsetPanTiltPitchSpeed));
			}

			if(fBTerminalData[7]&0x80)
			{
				temsetPanTiltRotateSpeed=(int16_t)((fBTerminalData[7]&0x70)>>0x04);
				temsetPanTiltRotateSpeed=temsetPanTiltRotateSpeed*temsetPanTiltRotateSpeed*40;
				panTiltRotateM->setSpeed(temsetPanTiltRotateSpeed);
			}
			else
			{
				temsetPanTiltRotateSpeed=(int16_t)((fBTerminalData[7]&0x70)>>0x04);
				temsetPanTiltRotateSpeed=-temsetPanTiltRotateSpeed*temsetPanTiltRotateSpeed*40;
				panTiltRotateM->setSpeed(temsetPanTiltRotateSpeed);
			}

			if(fBTerminalData[6]&0x08)
			{
				supportArmM->setErrorFlag_1(setSupportArmSpeed(-((int16_t)((fBTerminalData[6]&0x07)*1000))));
			}
			else
			{
				supportArmM->setErrorFlag_1(setSupportArmSpeed((int16_t)((fBTerminalData[6]&0x07)*1000)));
			}

			break;
		case AAAModel:
				xyzFlag=false;
				if(unlockArms(XBOT_AAAA_ARM0))//unlockArms执行结果是真
					allArmRunToPos(XBOT_AAAA_ARM1,XBOT_AAAA_ARM2,XBOT_AAAA_ARM3,XBOT_AAAA_ARM4,XBOT_AAAA_ARM5,XBOT_AAAA_ARM6,XBOT_AAAA_ARM7,XBOT_AAAA_ARM0);
			break;
		case BBBModel:
			xyzFlag=false;
			if(unlockArms(XBOT_BBBB_ARM0))
				allArmRunToPos(XBOT_BBBB_ARM1,XBOT_BBBB_ARM2,XBOT_BBBB_ARM3,XBOT_BBBB_ARM4,XBOT_BBBB_ARM5,XBOT_BBBB_ARM6,XBOT_BBBB_ARM7,XBOT_BBBB_ARM0);
			break;
			
		case CCCModel:
			xyzFlag=false;
			allArmRunToPos(XBOT_CCCC_ARM1,XBOT_CCCC_ARM2,XBOT_CCCC_ARM3,XBOT_CCCC_ARM4,XBOT_CCCC_ARM5,XBOT_CCCC_ARM6,XBOT_CCCC_ARM7,XBOT_CCCC_ARM0);
			if((bigArmPitchM->getSpeed()==0)&&(forearmPitchM->getSpeed()==0)&&(wristPitchM->getSpeed()==0))//进入限位 之后三个俯仰关节的行程靠U模式完成
			{
				if((ABS(XBOT_CCCC_ARM1-(fBbigArmRotateA->DATA_16))<50))//大臂旋转关节到达
				{
// 					if((-(fBbigArmPitchA->DATA_16)>350) || ((fBwristPitchA->DATA_16)>600) || ((fBforearmPitchA->DATA_16)>1200))
					{
						//大臂
						if(((XBOT_CCCC_ARM2-fBbigArmPitchA->DATA_16)>1000)&&(CCCUTime_1<10000))
						{
							bigArmPitchM->setPWMSpeed(22000);
							bigArmPitchM->resetUspeedTime();
							CCCUTime_1++;
						}
						else if(((XBOT_CCCC_ARM2-fBbigArmPitchA->DATA_16)>500)&&(CCCUTime_1<10000))//大于3度
						{
							bigArmPitchM->setPWMSpeed(12000);
							bigArmPitchM->resetUspeedTime();
							CCCUTime_1++;
						}
						else if(!CCCUFlag_1)
						{
							bigArmPitchM->setPWMSpeed(10000);
							bigArmPitchM->resetUspeedTime();
							CCCUFlag_1=true;
						}
						
						//小臂
						if(((fBforearmPitchA->DATA_16-XBOT_CCCC_ARM3)>1000)&&(CCCUTime_2<10000))
						{
							forearmPitchM->setPWMSpeed(-22000);
							forearmPitchM->resetUspeedTime();
							CCCUTime_2++;
						}
						else if(((fBforearmPitchA->DATA_16-XBOT_CCCC_ARM3)>500)&&(CCCUTime_2<10000))
						{
							forearmPitchM->setPWMSpeed(-12000);
							forearmPitchM->resetUspeedTime();
							CCCUTime_2++;
						}
						else if(!CCCUFlag_2)
						{
							forearmPitchM->setPWMSpeed(-10000);
							forearmPitchM->resetUspeedTime();
							CCCUFlag_2=true;
						}

						//手腕
						if(((fBwristPitchA->DATA_16-XBOT_CCCC_ARM4)>1000)&&(CCCUTime_3<10000))
						{
							wristPitchM->setPWMSpeed(-22000);
							wristPitchM->resetUspeedTime();
							CCCUTime_3++;
						}
						else if(((fBwristPitchA->DATA_16-XBOT_CCCC_ARM4)>500)&&(CCCUTime_3<10000))
						{
							wristPitchM->setPWMSpeed(-12000);
							wristPitchM->resetUspeedTime();
							CCCUTime_3++;
						}
						else if(!CCCUFlag_3)
						{
							wristPitchM->setPWMSpeed(-10000);
							wristPitchM->resetUspeedTime();
							CCCUFlag_3=true;
						}
					}
					/****
// 					else
// 					{
// 						//最后给一次U指令
// 						if(CCCUFlag_1==false)
// 						{
// 							bigArmPitchM->setPWMSpeed(10000);
// 							bigArmPitchM->resetUspeedTime();
// 							CCCUFlag_1=true;
// 						}
// 						//最后给一次U指令
// 						if(CCCUFlag_3==false)
// 						{
// 							wristPitchM->setPWMSpeed(-10000);
// 							wristPitchM->resetUspeedTime();
// 							CCCUFlag_3=true;
// 						}
// 						if(CCCUFlag_2==false)
// 						{
// 							forearmPitchM->setPWMSpeed(-10000);
// 							forearmPitchM->resetUspeedTime();
// 							CCCUFlag_2=true;
// 						}
// 					}
					
					//第一步将大臂俯仰和手腕俯仰归位,小臂运行到10度以内
// 					if(XBOT_CCCC_ARM2-(fBbigArmPitchA->DATA_16)>300||(fBwristPitchA->DATA_16)-XBOT_CCCC_ARM4>300)//大臂或手腕没合上//&&(fBforearmPitchA->DATA_16)-XBOT_CCCC_ARM3>1000)
// 					{
// 						//大臂
// 						if(XBOT_CCCC_ARM2-(fBbigArmPitchA->DATA_16)>600&&CCCUTime_1<10000)
// 						{
// 							bigArmPitchM->setPWMSpeed(22000);
// 							bigArmPitchM->resetUspeedTime();
// 							CCCUTime_1++;
// 						}
// 						else if(XBOT_CCCC_ARM2-(fBbigArmPitchA->DATA_16)>300&&CCCUTime_1<10000)//大于3度
// 						{
// 							bigArmPitchM->setPWMSpeed(7000);
// 							bigArmPitchM->resetUspeedTime();
// 							CCCUTime_1++;
// 						}
// 						
// 						//小臂
// 						if((fBforearmPitchA->DATA_16)-XBOT_CCCC_ARM3>1000)//&&CCCUTime_2<10000)
// 						{
// 							forearmPitchM->setPWMSpeed(-22000);
// 							forearmPitchM->resetUspeedTime();
// 						}
// 						else//小于10度 停止
// 						{
// 							forearmPitchM->setPWMSpeed(0);
// 							forearmPitchM->resetUspeedTime();
// 						}
// 						
// 						//手腕
// 						if((fBwristPitchA->DATA_16)-XBOT_CCCC_ARM4>600&&CCCUTime_3<10000)
// 						{
// 							wristPitchM->setPWMSpeed(-22000);
// 							wristPitchM->resetUspeedTime();
// 							CCCUTime_3++;
// 						}
// 						else if((fBwristPitchA->DATA_16)-XBOT_CCCC_ARM4>300&&CCCUTime_3<10000)
// 						{
// 							wristPitchM->setPWMSpeed(-8000);
// 							wristPitchM->resetUspeedTime();
// 							CCCUTime_3++;
// 						}
// 						
// 					}
// 					else //大臂和小臂都合上
// 					{
// 						//最后给一次U指令
// 						if(CCCUFlag_1==false)
// 						{
// 							bigArmPitchM->setPWMSpeed(5000);
// 							bigArmPitchM->resetUspeedTime();
// 							CCCUFlag_1=true;
// 						}
// 						//最后给一次U指令
// 						if(CCCUFlag_3==false)
// 						{
// 							wristPitchM->setPWMSpeed(-5000);
// 							wristPitchM->resetUspeedTime();
// 							CCCUFlag_3=true;
// 						}
// 						
// 						if((fBforearmPitchA->DATA_16)-XBOT_CCCC_ARM3>600&&CCCUTime_2<10000)
// 						{
// 							forearmPitchM->setPWMSpeed(-22000);
// 							forearmPitchM->resetUspeedTime();
// 							CCCUTime_2++;
// 						}
// 						else if((fBforearmPitchA->DATA_16)-XBOT_CCCC_ARM3>300&&CCCUTime_2<10000)
// 						{
// 							forearmPitchM->setPWMSpeed(-8000);
// 							forearmPitchM->resetUspeedTime();
// 							CCCUTime_2++;
// 						}
// 						else //最后给一次U指令
// 						{
// 							if(CCCUFlag_2==false)
// 							{
// 								forearmPitchM->setPWMSpeed(-5000);
// 								forearmPitchM->resetUspeedTime();
// 								CCCUFlag_2=true;
// 							}
// 						}
// 					}
*/
				}
				else//大臂旋转没有到达
				{
						if(bigArmRotateM->getSpeed()==0)
						{
							if(XBOT_CCCC_ARM1-(fBbigArmRotateA->DATA_16)<0)
							{
								bigArmRotateM->setSpeed(200);
							}
							else
							{
								bigArmRotateM->setSpeed(-200);
							}
						}
				}
			}
			else //if(fBforearmPitchA->DATA_16<500)//加速
			{
				if(bigArmPitchM->getSpeed()!=0&&bigArmPitchM->getSpeed()<3000)
					bigArmPitchM->setSpeed(3000);
				
				if(forearmPitchM->getSpeed()!=0&&forearmPitchM->getSpeed()>-3000)
					forearmPitchM->setSpeed(-3000);
				
				if(wristPitchM->getSpeed()!=0&&wristPitchM->getSpeed()>-3000)
					wristPitchM->setSpeed(-3000);
				
				if(bigArmRotateM->getSpeed()>0&&bigArmRotateM->getSpeed()<500)
					bigArmRotateM->setSpeed(500);
				
				if(bigArmRotateM->getSpeed()<0&&bigArmRotateM->getSpeed()>-500)
					bigArmRotateM->setSpeed(-500);
				
				bigArmPitchM->setPWMSpeed(0);
				forearmPitchM->setPWMSpeed(0);
				wristPitchM->setPWMSpeed(0);
			}
			break;
		case DDDModel:
			xyzFlag=false;
			if(unlockArms(XBOT_DDDD_ARM0))
				allArmRunToPos(XBOT_DDDD_ARM1,XBOT_DDDD_ARM2,XBOT_DDDD_ARM3,XBOT_DDDD_ARM4,XBOT_DDDD_ARM5,XBOT_DDDD_ARM6,XBOT_DDDD_ARM7,XBOT_DDDD_ARM0);
			break;
		case EEEModel:
			xyzFlag=false;
			if(unlockArms(XBOT_EEEE_ARM0))
				allArmRunToPos(XBOT_EEEE_ARM1,XBOT_EEEE_ARM2,XBOT_EEEE_ARM3,XBOT_EEEE_ARM4,XBOT_EEEE_ARM5,XBOT_EEEE_ARM6,XBOT_EEEE_ARM7,XBOT_EEEE_ARM0);
			break;
		case HHHModel:
			suppArmRunToPos(XBOT_HHH_ARM0);
			break;
		case IIIModel:
			suppArmRunToPos(XBOT_III_ARM0);
			break;
		case JJJModel:
			suppArmRunToPos(XBOT_JJJ_ARM0);
			break;
		case KKKModel:
			suppArmRunToPos(XBOT_KKK_ARM0);
			break;
		case LLLModel:
			suppArmRunToPos(XBOT_LLL_ARM0);
			break;


		case MMMModel: //放线模式
#ifdef NEWOPTICALBOBBIN			
			//判断是否为有线
			if(signalType==WIRE_WORK_MODE&&WireType==true)
			{
				if(opticalBobbinDevice->getWireLength()>5||limitFlag==false)//当剩余线长大于5米，或者在取消限位的模式下启动放线
				{
					opticalBobbinDevice->setWorkStatus(0x05);
					opticalBobbinDevice->setLeftSpeed(0);
					opticalBobbinDevice->setRightSpeed(0);
				}
				else
				{
					opticalBobbinDevice->setWorkStatus(0x00);
					opticalBobbinDevice->setLeftSpeed(0);
					opticalBobbinDevice->setRightSpeed(0);
				}
			}
			else
#endif
			{
				panTiltRunToMMMModel();
			}
			break;
		case NNNModel: //收线模式
#ifdef NEWOPTICALBOBBIN			
			//判断是否为有线
			if(signalType==WIRE_WORK_MODE&&WireType==true)
			{
				opticalBobbinDevice->setWorkStatus(0x06);
				opticalBobbinDevice->setLeftSpeed(0);
				opticalBobbinDevice->setRightSpeed(0);
			}
			else
#endif
			{
				fingerRunToNNNModel();
			}
			break;
		case SSSModel:
			stopAllMoter();
			break;
		case XLLModel:
			xyzFlag=false;
			runOnXXXLine(-5000*((fBTerminalData[7]&0x70)>>4)/0x09);
			break;
		case XRRModel:
			xyzFlag=false;
			runOnXXXLine(5000*((fBTerminalData[7]&0x70)>>4)/0x09);
			break;
		case YFFModel:
			xyzFlag=false;
			runOnYYYLine(-5000*(fBTerminalData[7]&0x07)/0x09);
			break;
		case YBBModel:
			xyzFlag=false;
			runOnYYYLine(5000*(fBTerminalData[7]&0x07)/0x09);
			break;
		case ZUUModel:
			xyzFlag=false;
			runOnZZZLine(5000*(fBTerminalData[5]&0x07)/0x0c);
			break;
		case ZDDModel:
			xyzFlag=false;
			runOnZZZLine(-5000*(fBTerminalData[5]&0x07)/0x0c);
			break;
		case XYZModel:
			XbotArmSetXyzCtrlMode();
			break;
	}
}

/**
  * 功  能：云台运行到归位状态
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::panTiltRunToMMMModel()
{
		int a1=(int)fBbigArmRotateA->DATA_16;
		int a2=(int)fBbigArmPitchA->DATA_16;
		int a3=(int)fBforearmPitchA->DATA_16;
		int a4=(int)fBwristPitchA->DATA_16;
		int a5=(int)fBwristRotateA->DATA_16;
		int a6=(int)XBOT_AAAA_ARM6;
		int a7=(int)XBOT_AAAA_ARM7;
		int a8=(int)(fBDiscA->DATA_16);//支臂的角度差单独计算
		allArmRunToPos(a1,a2,a3,a4,a5,a6,a7,a8);
	
}

/**
  * 功  能：手抓运行到归位状态，手抓夹持运动到50度，手抓旋转运动到0度
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::fingerRunToNNNModel()
{
	int temFingerMediateA =(int)fBfingerMediateA->DATA_16;//当前的手抓夹持角度
	int temWristRotateA =(int)fBwristRotateA->DATA_16;		//当前的手抓旋转角度
	int temSpeed=0;
	 
	if(temWristRotateA>0)//负方向运动
	{
		if(temWristRotateA>1000) //10度以上全速运行
		{
			wristRotateM->setSpeed(-12000);
		}
		else if(temWristRotateA>200)//3到10度，半速运行
		{
			wristRotateM->setSpeed(-6000);
		}
		else if(temWristRotateA>100) //1到2度,400速度运行
		{
			wristRotateM->setSpeed(-400);
		}
		else//停止运行
		{
			wristRotateM->resetSpeed();
		}
	}
	else//正方向运动
	{
		if(temWristRotateA<-1000) //10度以上全速运行
		{
			wristRotateM->setSpeed(12000);
		}
		else if(temWristRotateA<-200)//3到10度，半速运行
		{
			wristRotateM->setSpeed(6000);
		}
		else if(temWristRotateA<100) //1到2度,400速度运行
		{
			wristRotateM->setSpeed(400);
		}
		else//停止运行
		{
			wristRotateM->resetSpeed();
		}
	}
	if(temFingerMediateA>5050)//负方向运动 
	{
		if(temFingerMediateA>5500) //5度以上全速运行
		{
			temSpeed=-9000;
		}
		else if(temFingerMediateA>5150)//3到5度，半速运行
		{
			temSpeed=-4500;
		}
		else if(temFingerMediateA>5050) //1到2度,300速度运行
		{
			temSpeed=-300;
		}
		else//停止运行
		{
			temSpeed=0;
		}
	}
	else//正方向运动
	{
		if(temFingerMediateA<5000) //5度以上全速运行
		{
			temSpeed=9000;
		}
		else if(temFingerMediateA<5300)//3到5度，半速运行
		{
			temSpeed=4500;
		}
		else if(temFingerMediateA<5500) //1到2度,300速度运行
		{
			temSpeed=300;
		}
		else//停止运行
		{
			temSpeed=0;
		}
	}
	fingerMediateM->setErrorFlag_1(setFingerMediateSpeed(temSpeed));
}

/**
  * 功  能：支臂运行到指定角度 速度符号的临界角度为300度
  * 参  数：指定的角度
  * 返回值：无
  * 
  */
#define MAXSUPPARMSPEED REFER_SPEED_MAX_ARM0

#define MIDDLESUPPARMSPEED 2000

#define MINSUPPARMSPEED 500

#define SUBANGLE_SUPP_1 20
#define SUBANGLE_SUPP_2 10
#define SUBANGLE_SUPP_3 4

#ifdef USEPOTENTIOMETER

void XbotApp::suppArmRunToPos(int angle,bool showError)
{
	int16_t temAngle=fBDiscA->DATA_16;														//获取当前的角度
	int16_t subAngle=0;
	int temSpeed=0;
	if((angle>XBOT_CRITICAL_ARM0_DN&&angle<XBOT_CRITICAL_ARM0_UP)||(temAngle>XBOT_CRITICAL_ARM0_DN&&temAngle<XBOT_CRITICAL_ARM0_UP))	//指定的角度或者当前角度在死区范围内
	{
		return;
	}
// 	if(CodedDisc->getErrorFlag()==0x08)														//码盘设备丢失
// 		return;
	if(angle<=XBOT_CRITICAL_ARM0_DN)																	//指定的角度小于死区临界下限
	{
		if(temAngle>=XBOT_CRITICAL_ARM0_UP&&temAngle<ARM0_ANGLE_360)	//当前角度在死区临界上限与360之间，正向运动
		{
			subAngle=angle+ARM0_ANGLE_360-temAngle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=REFER_SPEED_MAX_ARM0;
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=MIDDLESUPPARMSPEED;
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=MINSUPPARMSPEED;
			}
			else
			{
				temSpeed=0;
			}
		}
		else if(temAngle>=ARM0_ANGLE_0&&temAngle<angle)						//当前角度在0度与指定角度之间，正向运动
		{
			subAngle=angle-temAngle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=REFER_SPEED_MAX_ARM0;
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=MIDDLESUPPARMSPEED;
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=MINSUPPARMSPEED;
			}
			else
			{
				temSpeed=0;
			}
		}
		else																											//当前角度在指定角度与死区临界下限角度之间，反向运动
		{
			subAngle=temAngle-angle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=(-REFER_SPEED_MAX_ARM0);
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=(-MIDDLESUPPARMSPEED);
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=(-MINSUPPARMSPEED);
			}
			else
			{
				temSpeed=0;
			}
		}
	}
	else 																												//指定的角度大于等于死区临界上限
	{
		if(temAngle>=XBOT_CRITICAL_ARM0_UP&&temAngle<angle)					//当前角度在死区临界上限与指定角度之间 正向运动
		{
			subAngle=angle-temAngle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=(REFER_SPEED_MAX_ARM0);
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=(MIDDLESUPPARMSPEED);
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=(MINSUPPARMSPEED);
			}
			else
			{
				temSpeed=0;
// 				supportArmM->resetSpeed();
			}			
		}
		else if(temAngle>=angle&&temAngle<ARM0_ANGLE_360)					//当前角度在指定角度与360度之间 反向运动
		{
			subAngle=temAngle-angle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=(-REFER_SPEED_MAX_ARM0);
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=(-MIDDLESUPPARMSPEED);
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=(-MINSUPPARMSPEED);
			}
			else
			{
				temSpeed=0;
			}
		}
		else 																											//当前角度在0度与死区临界下限之间 反向运动
		{
			subAngle=angle-temAngle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=(-REFER_SPEED_MAX_ARM0);
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=(-MIDDLESUPPARMSPEED);
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=(-MINSUPPARMSPEED);
			}
// 			else if(subAngle>2)
// 			{
// 				temSpeed=(-200);
// 			}
			else
			{
				temSpeed=0;
			}
		}
	}
	if(showError)
		supportArmM->setErrorFlag_1(setSupportArmSpeed(temSpeed));
	else
		setSupportArmSpeed(temSpeed);
}

#else

void XbotApp::suppArmRunToPos(int angle,bool showError)
{
	int16_t temAngle=fBDiscA->DATA_16;													//获取当前的角度
	int16_t subAngle=0;
	int temSpeed=0;
	if(CodedDisc->getErrorFlag()==0x08)													//码盘设备丢失
		return;
	if(angle<XBOT_CRITICAL_ARM0)																//指定的角度小于临界角度
	{
		if(temAngle>=XBOT_CRITICAL_ARM0&&temAngle<ARM0_ANGLE_360)	//当前角度在临界角度与360之间，正向运动
		{
			subAngle=angle+ARM0_ANGLE_360-temAngle;
			if(subAngle>100)
			{
				temSpeed=5000;
			}
			else if(subAngle>50)
			{
				temSpeed=4500;
			}
			else if(subAngle>10)
			{
				temSpeed=1000;
			}
			else if(subAngle>5)
			{
				temSpeed=500;
			}
			else if(subAngle>2)
			{
				temSpeed=200;
			}
			else
			{
				temSpeed=0;
			}
		}
		else if(temAngle>ARM0_ANGLE_0&&temAngle<angle)						//当前角度在0度与指定角度之间，正向运动
		{
			subAngle=angle-temAngle;
			if(subAngle>100)
			{
				temSpeed=5000;
			}
			else if(subAngle>50)
			{
				temSpeed=4500;
			}
			else if(subAngle>10)
			{
				temSpeed=1000;
			}
			else if(subAngle>5)
			{
				temSpeed=500;
			}
			else if(subAngle>2)
			{
				temSpeed=200;
			}
			else
			{
				temSpeed=0;
			}
		}
		else																											//当前角度在指定角度与临界角度之间，反向运动
		{
			subAngle=temAngle-angle;
			if(subAngle>100)
			{
				temSpeed=(-5000);
			}
			else if(subAngle>50)
			{
				temSpeed=(-4500);
			}
			else if(subAngle>10)
			{
				temSpeed=(-1000);
			}
			else if(subAngle>5)
			{
				temSpeed=(-500);
			}
			else if(subAngle>2)
			{
				temSpeed=(-200);
			}
			else
			{
				temSpeed=0;
			}
		}
	}
	else 																												//指定的角度大于临界角度
	{
		if(temAngle>=XBOT_CRITICAL_ARM0&&temAngle<angle)					//当前角度在临界角度与指定角度之间 正向运动
		{
			subAngle=angle-temAngle;
			if(subAngle>100)
			{
				temSpeed=(5000);
			}
			else if(subAngle>50)
			{
				temSpeed=(4500);
			}
			else if(subAngle>10)
			{
				temSpeed=(1000);
			}
			else if(subAngle>5)
			{
				temSpeed=(500);
			}
			else if(subAngle>2)
			{
				temSpeed=(200);
			}
			else
			{
				supportArmM->resetSpeed();
			}			
		}
		else if(temAngle>=angle&&temAngle<ARM0_ANGLE_360)					//当前角度在指定角度与360度之间 反向运动
		{
			subAngle=temAngle-angle;
			if(subAngle>100)
			{
				temSpeed=(-5000);
			}
			else if(subAngle>50)
			{
				temSpeed=(-4500);
			}
			else if(subAngle>10)
			{
				temSpeed=(-1000);
			}
			else if(subAngle>5)
			{
				temSpeed=(-500);
			}
			else if(subAngle>2)
			{
				temSpeed=(-200);
			}
			else
			{
				temSpeed=0;
			}
		}
		else 																											//当前角度在0度与临界角度之间 反向运动
		{
			subAngle=angle-temAngle;
			if(subAngle>100)
			{
				temSpeed=(-5000);
			}
			else if(subAngle>50)
			{
				temSpeed=(-4500);
			}
			else if(subAngle>10)
			{
				temSpeed=(-1000);
			}
			else if(subAngle>5)
			{
				temSpeed=(-500);
			}
			else if(subAngle>2)
			{
				temSpeed=(-200);
			}
			else
			{
				temSpeed=0;
			}
		}
	}
	if(showError)
		supportArmM->setErrorFlag_1(setSupportArmSpeed(temSpeed));
	else
		setSupportArmSpeed(temSpeed);
}
#endif

/**
  * 功  能：单独获取支臂的角度差 返回的是1024/4096制的角度
  * 参  数：指定到达的角度
  * 返回值：当前角度与指定角度的差
  * 
  */
#ifdef USEPOTENTIOMETER

int16_t XbotApp::getSuppArmSubAngle(int angle)
{
	int16_t temAngle=fBDiscA->DATA_16;													//获取当前的角度 4096制
	int16_t subAngle=0;
	if((angle>XBOT_CRITICAL_ARM0_DN&&angle<XBOT_CRITICAL_ARM0_UP)||(temAngle>XBOT_CRITICAL_ARM0_DN&&temAngle<XBOT_CRITICAL_ARM0_UP))	//指定的角度或者当前角度在死区范围内
	{
		return 0;
	}	

	if(angle<=XBOT_CRITICAL_ARM0_DN)																//指定的角度小于等于临界角度下限
	{
		if(temAngle>=XBOT_CRITICAL_ARM0_UP&&temAngle<ARM0_ANGLE_360)	//当前角度在临界角度上限与360之间，正向运动
		{
			subAngle=angle+ARM0_ANGLE_360-temAngle;
		}
		else
		{
			subAngle=angle-temAngle;
		}
	}
	else 																														//指定的角度大于等于临界角度上限
	{
		if(temAngle>=XBOT_CRITICAL_ARM0_UP&&temAngle<ARM0_ANGLE_360)	//当前角度在临界角度上限与360之间
		{
			subAngle=angle-temAngle;
		}
		else 																													//当前角度在0度与临界角度下限之间 反向运动
		{
			subAngle=angle-temAngle-ARM0_ANGLE_360;
		}
	}
	return subAngle;
}
#else
int16_t XbotApp::getSuppArmSubAngle(int angle)
{
	int16_t temAngle=fBDiscA->DATA_16;													//获取当前的角度 1024制
	int16_t subAngle=0;
	if(angle<XBOT_CRITICAL_ARM0)																//指定的角度小于临界角度
	{
		if(temAngle>=XBOT_CRITICAL_ARM0&&temAngle<ARM0_ANGLE_360)	//当前角度在临界角度与360之间，正向运动
		{
			subAngle=angle+ARM0_ANGLE_360-temAngle;
		}
		else
		{
			subAngle=angle-temAngle;
		}
	}
	else 																												//指定的角度大于临界角度
	{
		if(temAngle>=XBOT_CRITICAL_ARM0&&temAngle<ARM0_ANGLE_360)	//当前角度在临界角度与指定角度之间
		{
			subAngle=angle-temAngle;
		}
		else 																											//当前角度在0度与临界角度之间 反向运动
		{
			subAngle=angle-temAngle-ARM0_ANGLE_360;
		}
	}
	return subAngle;
}
#endif



/**
  * 功  能：单独根据角度差和时间差设置支臂的速度，支臂比较特殊，运动方向的设定要根据临界角度
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::setSuppArmspeed(int subA,int sunT,int sunMaxT)
{
	if(ABS(subA)>100)//误差在 ±1 度
	{
		if(ABS(subA)>1000)
			setSupportArmSpeed((int16_t)(5000*sunT/sunMaxT));
		else if(ABS(subA)>500)
			supportArmM->setSpeed((int16_t)(3500*sunT/sunMaxT));
		else if(ABS(subA)>300)
			setSupportArmSpeed((int16_t)(((int32_t)2250)*sunT/sunMaxT));
		else
			setSupportArmSpeed((int16_t)(((int32_t)600)*sunT/sunMaxT));
	}
	else								//速度置0
	{
		supportArmM->resetSpeed();
	}
}


/**
  * 功  能：所有关节运行到指定角度，除了前进相机和手抓抓持关节
  * 参  数：指定的角度
					angle_1：大臂旋转
					angle_2：大臂俯仰
					angle_3：小臂俯仰
					angle_4：手腕俯仰
					angle_5：手腕旋转
					angle_6：云台俯仰
					angle_7：云台旋转
					angle_8：支臂俯仰
  * 返回值：无
  * 备  注：采用同步到达的方式，如果某些关节发生干涉限位，则该关节等待相应的干涉源关节到达非干涉位置后继续运动
  */
void XbotApp::allArmRunToPos(int angle_1,int angle_2,int angle_3,int angle_4,int angle_5,int angle_6,int angle_7,int angle_8)
{
	int subAngle[8]={0};
	int subtime[8]={0};
	int subMaxTime=0;
	//码盘设备坏了就不可以联动
// 	if(checkBlockError()==false)													//没有电机堵转
	{
		subAngle[0]=(angle_1-(int)fBbigArmRotateA->DATA_16);
		subAngle[1]=(angle_2-(int)fBbigArmPitchA->DATA_16);
		subAngle[2]=(angle_3-(int)fBforearmPitchA->DATA_16);
		subAngle[3]=(angle_4-(int)fBwristPitchA->DATA_16);
		subAngle[4]=(angle_5-(int)fBwristRotateA->DATA_16);
		subAngle[5]=(angle_6-(int)fBpanTiltPitchA->DATA_16);
		subAngle[6]=(angle_7-(int)fBpanTiltRotateA->DATA_16);
// 		subAngle[7]=((int)getSuppArmSubAngle(angle_8))*1125/32;//支臂的角度差单独计算
		subAngle[7]=angle_8;
		//时间差为角度差和速度系数（减速比）的乘积 ，减速比越大时间越长，最大速度越大 时间越短
		subtime[0]=subAngle[0]*SPEED_COEFFICIENT_ARM1;
		subtime[1]=subAngle[1]*SPEED_COEFFICIENT_ARM2;
		subtime[2]=subAngle[2]*SPEED_COEFFICIENT_ARM3;
		subtime[3]=subAngle[3]*SPEED_COEFFICIENT_ARM4;
		subtime[4]=subAngle[4]*SPEED_COEFFICIENT_ARM5;
		subtime[5]=subAngle[5]*SPEED_COEFFICIENT_ARM6;
		subtime[6]=subAngle[6]*SPEED_COEFFICIENT_ARM7;
// 		subtime[7]=subAngle[7]*SPEED_COEFFICIENT_ARM0;
		subtime[7]=0;
		subMaxTime=maxTime(subtime);
		
		suppArmRunToPos(subAngle[7],false); //此处一定要在上个指令之后
		
		if(subMaxTime==0||limitFlag==false)//无限位状态下不执行
			return;

// 	setSuppArmspeed(subAngle[7],subtime[7],subMaxTime);
		panTiltRotateM->	setSpeedFromSubAngle(subAngle[6],subtime[6],subMaxTime);
		panTiltPitchM->		setSpeedFromSubAngle(setPanTiltPitchSpeed,subAngle[5],subtime[5],subMaxTime);	
		wristRotateM->		setSpeedFromSubAngle(subAngle[4],subtime[4],subMaxTime);
		wristPitchM->			setSpeedFromSubAngle(setWristPitchSpeed,subAngle[3],subtime[3],subMaxTime);
		forearmPitchM->		setSpeedFromSubAngle(setForearmPitchSpeed,subAngle[2],subtime[2],subMaxTime);
		bigArmPitchM->		setSpeedFromSubAngle(setBigArmPitchSpeed,subAngle[1],subtime[1],subMaxTime);
		bigArmRotateM->		setSpeedFromSubAngle(setBigArmRotateSpeed,subAngle[0],subtime[0],subMaxTime);
	}
	checkBlockError();
}
/**
  * 功  能：大臂旋转，大臂俯仰，小臂俯仰三个关节运行到指定位置
  * 参  数：指定的角度
					angle_1：大臂旋转
					angle_2：大臂俯仰
					angle_3：小臂俯仰
					speed	 ：速度

  * 返回值：无
  * 备  注：采用同步到达的方式，如果某些关节发生干涉限位，则该关节等待相应的干涉源关节到达非干涉位置后继续运动
  */
void XbotApp::threeArmRunToPos(int angle_1,int angle_2,int angle_3,int speed)
{
	int subAngle[3]={0};
	int subtime[3]={0};
	int subMaxTime=0;
	//码盘设备坏了就不可以联动
// 	if(CodedDisc->getErrorFlag()==0x00)													//码盘设备正常
	{
		subAngle[0]=(angle_1-(int)fBbigArmRotateA->DATA_16);
		subAngle[1]=(angle_2-(int)fBbigArmPitchA->DATA_16);
		subAngle[2]=(angle_3-(int)fBforearmPitchA->DATA_16);


		//时间差为角度差和速度系数（减速比）的乘积 ，减速比越大时间越长，最大速度越大 时间越短
		subtime[0]=subAngle[0]*SPEED_COEFFICIENT_ARM1;
		subtime[1]=subAngle[1]*SPEED_COEFFICIENT_ARM2;
		subtime[2]=subAngle[2]*SPEED_COEFFICIENT_ARM3;

		subMaxTime=maxTime_1(subtime);
		if(subMaxTime==0||limitFlag==false)//无限位状态下不执行
			return;
		forearmPitchM->		setSpeedFromSubAngle_1(subAngle[2],subtime[2]*ABS(speed)/7,subMaxTime);
		bigArmPitchM->		setSpeedFromSubAngle_1(subAngle[1],subtime[1]*ABS(speed)/7,subMaxTime);
		bigArmRotateM->		setSpeedFromSubAngle_1(subAngle[0],subtime[0]*ABS(speed)/7,subMaxTime);
	}
}
/**
  * 功  能：求最长的到位时间,采用了速度预检测机制
  * 参  数：待检测时间差数组
  * 返回值：最大的时间
  * 
  */
int XbotApp::maxTime(int *data)
{
	int *temData=data;
	int32_t max=0;
	
//模拟设置速度，检测是否限位
	if((data[0]==0)||((data[0]>0?setBigArmRotateSpeed(1000):setBigArmRotateSpeed(-1000))!=0))
		data[0]=0;
	setBigArmRotateSpeed(0);
	
	if((data[1]==0)||((data[1]>0?setBigArmPitchSpeed(1000):setBigArmPitchSpeed(-1000))!=0))
		data[1]=0;
	setBigArmPitchSpeed(0);
	
	if((data[2]==0)||((data[2]>0?setForearmPitchSpeed(1000):setForearmPitchSpeed(-1000))!=0))
		data[2]=0;
	setForearmPitchSpeed(0);
	
	if((data[3]==0)||((data[3]>0?setWristPitchSpeed(1000):setWristPitchSpeed(-1000))!=0))
		data[3]=0;
	setWristPitchSpeed(0);
	
// 	if((data[4]>0?setBigArmRotateSpeed(1000):setBigArmRotateSpeed(-1000))!=0)
// 		data[4]=0;
	
	if((data[5]==0)||((data[5]>0?setPanTiltPitchSpeed(1000):setPanTiltPitchSpeed(-1000))!=0))
		data[5]=0;
	setPanTiltPitchSpeed(0);
	
// 	if((data[6]>0?setBigArmRotateSpeed(1000):setBigArmRotateSpeed(-1000))!=0)
// 		data[6]=0;
// 	
	if((data[7]==0)||((data[7]>0?setSupportArmSpeed(1000):setSupportArmSpeed(-1000))!=0))
		data[7]=0;
	setSupportArmSpeed(0);
	
	max=MAX(temData[0],temData[1]);
	max=MAX(max,temData[2]);
	max=MAX(max,temData[3]);
	max=MAX(max,temData[4]);
	max=MAX(max,temData[5]);
	max=MAX(max,temData[6]);
	max=MAX(max,temData[7]);
	return max;
}

/**
  * 功  能：求最长的到位时间,用于三维模式
  * 参  数：待检测时间差数组
  * 返回值：最大的时间
  * 
  */
int XbotApp::maxTime_1(int *data)
{
	int *temData=data;
	int32_t max=0;
	max=MAX(temData[0],temData[1]);
	max=MAX(max,temData[2]);
	return max;
}

/**
  * 功  能：停止所有的电机
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::stopAllMoter()
{
	leftRunM->resetSpeed();						//行进左电机
	rightRunM->resetSpeed();					//行进右电机
	supportArmM->resetSpeed();				//支臂电机
	bigArmRotateM->resetSpeed();			//大臂旋转电机
	bigArmPitchM->resetSpeed(); 			//大臂俯仰电机
	forearmPitchM->resetSpeed();			//小臂俯仰电机
	wristPitchM->resetSpeed();				//手腕俯仰电机
	wristRotateM->resetSpeed();				//手腕旋转电机
	panTiltPitchM->resetSpeed();			//云台俯仰电机
	panTiltRotateM->resetSpeed();			//云台旋转电机
	fingerMediateM->resetSpeed();			//手爪捏合电机
	cameraPitchM->resetSpeed();				//相机俯仰电机
}


/**
  * 功  能：设置手腕俯仰的速度
  * 参  数：设定的速度的参考值
  * 返回值：
  * 0：正常速度设置
  * 1：由云台俯仰关节 产生的干涉限位
  * 2：到达负方向的最大限位
  * 3：由小臂俯仰角度太小 产生的干涉限位
  * 4：由于小臂俯仰角度较小 继续运动可能与手爪产生干涉的限位
  * 5：到达正方向的最大限位
  * 6：手爪产生的干涉限位
  */
uint8_t XbotApp::setWristPitchSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;																					//状态反馈标志
	int16_t temForearmPitchAngle=fBforearmPitchA->DATA_16;			
	int16_t temWristAngle=fBwristPitchA->DATA_16;									//手腕角度
	int16_t temPanTiltPitchAngle=fBpanTiltPitchA->DATA_16;				//云台角度
	int16_t temFingerMediateAngle=fBfingerMediateA->DATA_16;			//手抓开合角度
	if(temSpeed==0)
	{
		wristPitchM->resetSpeed();
		return statusFlag;
	}
	if(limitFlag)
	{
		if(temSpeed<0)//负方向运动
		{
			if(temPanTiltPitchAngle<11800)
			{
					if(temWristAngle>2500)
						wristPitchM->setSpeed(temSpeed);
					else if(temWristAngle>2100)
						wristPitchM->setSpeed(temSpeed/3);
					else if(temWristAngle>2000)
					{
						wristPitchM->setSpeed(-200);
						statusFlag=1;									//由云台俯仰关节 产生的干涉限位
					}
					else
					{
						wristPitchM->resetSpeed();
						statusFlag=1;									//由云台俯仰关节 产生的干涉限位
					}
			}
			else
			{
					if(temWristAngle>1400)
						wristPitchM->setSpeed(temSpeed);
					else if(temWristAngle>1000)
						wristPitchM->setSpeed(temSpeed/3);
					else if(temWristAngle>900)
					{
						wristPitchM->setSpeed(-200);
						statusFlag=2;									//到达负方向的最大限位
					}
					else
					{
						wristPitchM->resetSpeed();
						statusFlag=2;									//到达负方向的最大限位
					}
			}
		}
		else	//正方向运动
		{
			if(temForearmPitchAngle<3500)
			{
// 				if(temWristAngle<4600)
// 				{
					if(temForearmPitchAngle<1400)
					{
						wristPitchM->resetSpeed();//由小臂俯仰角度太小 产生的干涉限位
						statusFlag=3;	
					}
					else
					{
						if(temWristAngle<4000)
							wristPitchM->setSpeed(temSpeed);
						else if(temWristAngle<4400)
							wristPitchM->setSpeed(temSpeed/3);
						else if(temWristAngle<4500)
						{
							wristPitchM->setSpeed(200);
							statusFlag=4;	
						}
						else
						{
							wristPitchM->resetSpeed();//由于小臂俯仰角度较小 继续运动可能与手爪产生干涉的限位
							statusFlag=4;	
						}
					}
// 				}
// 				else //动态处理
// 				{
// 					if(temForearmPitchAngle<temWristAngle-3500)
// 					{
// 						wristPitchM->resetSpeed();
// 					}
// 					else
// 					{
// 						if(temWristAngle<temForearmPitchAngle+3000)
// 							wristPitchM->setSpeed(temSpeed);
// 						else if(temWristAngle<temForearmPitchAngle+3400)
// 							wristPitchM->setSpeed(temSpeed/3);
// 						else if(temWristAngle<temForearmPitchAngle+3500)
// 							wristPitchM->setSpeed(200);
// 						else
// 							wristPitchM->resetSpeed();
// 					}
// 				}
			}
			else 
			{
				if(temFingerMediateAngle<1100)
				{
					if(temWristAngle<17500)
						wristPitchM->setSpeed(temSpeed);
					else if(temWristAngle<17800)
						wristPitchM->setSpeed(temSpeed/3);
					else if(temWristAngle<17900)
					{
						wristPitchM->setSpeed(200);
						statusFlag=5;							 //到达正方向的最大限位
					}
					else
					{
						wristPitchM->resetSpeed();
						statusFlag=5;							 //到达正方向的最大限位
					}
				}
				else
				{
					if(temWristAngle<13300)
						wristPitchM->setSpeed(temSpeed);
					else if(temWristAngle<13700)
						wristPitchM->setSpeed(temSpeed/3);
					else if(temWristAngle<13800)
					{
						wristPitchM->setSpeed(200);
						statusFlag=6;							 //手爪产生的干涉限位
					}
					else
					{
						wristPitchM->resetSpeed();
						statusFlag=6;							 //手爪产生的干涉限位
					}
				}
			}
		}
	}
	else
	{
		wristPitchM->setSpeed(temSpeed);
	}
	return statusFlag;
}

/**
  * 功  能：设置云台俯仰的速度
  * 参  数：设定的速度的参考值
  * 返回值：
  *	 	0：正常设置速度
  * 	1：手腕俯仰角度较小 产生限位干涉
  *		2：云台俯仰负方向最大限位
  *		3：云台俯仰正方向最大限位
  */
uint8_t XbotApp::setPanTiltPitchSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;																					//状态反馈标志
	int16_t temWristPitchAngle=fBwristPitchA->DATA_16;					  //手腕角度
	int16_t temPanTiltPitchAngle=fBpanTiltPitchA->DATA_16;				//云台角度
	if(temSpeed==0)
	{
		panTiltPitchM->resetSpeed();
		return statusFlag;
	}
	
	if(limitFlag)
	{
		if(temSpeed>0)//正方向运动
		{
			if(temPanTiltPitchAngle<17400)//
				panTiltPitchM->setSpeed(temSpeed);
			else if(temPanTiltPitchAngle<17700)
				panTiltPitchM->setSpeed(temSpeed/2);
			else if(temPanTiltPitchAngle<17900)
			{
				panTiltPitchM->setSpeed(temSpeed/3);
				statusFlag=3;//手腕达到正方向最大限位
			}
			else
			{
					panTiltPitchM->resetSpeed();
					statusFlag=3;//手腕达到正方向最大限位
			}
		}
		else
		{
			if(temWristPitchAngle<1900)
			{
				if(temPanTiltPitchAngle>12500)
					panTiltPitchM->setSpeed(temSpeed);
				else if(temPanTiltPitchAngle>12100)
					panTiltPitchM->setSpeed(temSpeed/3);
				else if(temPanTiltPitchAngle>12000)
				{
					panTiltPitchM->setSpeed(200);
					statusFlag=1;//手腕俯仰角度较小 产生限位干涉
				}
				else
				{
					panTiltPitchM->resetSpeed();
					statusFlag=1;//手腕俯仰角度较小 产生限位干涉
				}
			}
			else
			{
				if(temPanTiltPitchAngle>-2300)
				{
					panTiltPitchM->setSpeed(temSpeed);
				}
				else if(temPanTiltPitchAngle>-2700)
				{
					panTiltPitchM->setSpeed(temSpeed/2);
				}
				else if(temPanTiltPitchAngle>-2900)
				{
					panTiltPitchM->setSpeed(temSpeed/3);
					statusFlag=2;//手腕俯仰角度达到负方向限位
				}
				else
				{
					panTiltPitchM->resetSpeed();
					statusFlag=2;//手腕俯仰角度达到负方向限位
				}
			}
		}
	}
	else//无限位
	{
		panTiltPitchM->setSpeed(temSpeed);
	}
	return statusFlag;
}


/**
  * 功  能：设置手抓夹持速度
  * 参  数：设定的速度的参考值
  * 返回值：
  * 0：正常角度赋值
  * 1: 手爪夹持到达负方向的最大限位
  * 2: 手爪夹持到达正方向的最大限位
  * 3: 手爪被手腕俯仰干涉
  */
uint8_t XbotApp::setFingerMediateSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;
	int16_t temWristAngle=fBwristPitchA->DATA_16;									//手腕角度
	int16_t temFingerMediateAngle=fBfingerMediateA->DATA_16;			//手抓开合角度
	
	if(temSpeed==0)
	{
		fingerMediateM->resetSpeed();
		return statusFlag;
	}
	
	if(!limitFlag)
	{
		fingerMediateM->setSpeed(temSpeed);
		return statusFlag;
	}
	if(temSpeed<0)
	{
		if(temFingerMediateAngle>500)
			fingerMediateM->setSpeed(temSpeed);
		else if(temFingerMediateAngle>200)
			fingerMediateM->setSpeed(temSpeed/3);
		else if(temFingerMediateAngle>0)
		{
			fingerMediateM->setSpeed(-200);
			statusFlag=1;//手爪夹持到达负方向的最大限位
		}
		else
		{
			fingerMediateM->resetSpeed();
			statusFlag=1;//手爪夹持到达负方向的最大限位
		}
	}
	else
	{
		if(temWristAngle<13900)
		{
			if(temFingerMediateAngle<7950)
				fingerMediateM->setSpeed(temSpeed);
			else if(temFingerMediateAngle<8250)
				fingerMediateM->setSpeed(temSpeed/3);
			else if(temFingerMediateAngle<8350)
			{
				fingerMediateM->setSpeed(200);
				statusFlag=2;//手爪夹持到达正方向的最大限位
			}
			else
			{
				fingerMediateM->resetSpeed();
				statusFlag=2;//手爪夹持到达正方向的最大限位
			}
		}
		else
		{
			if(temFingerMediateAngle<500)
				fingerMediateM->setSpeed(temSpeed);
			else if(temFingerMediateAngle<900)
				fingerMediateM->setSpeed(temSpeed/3);
			else if(temFingerMediateAngle<1000)
			{
				fingerMediateM->setSpeed(200);
				statusFlag=3;//手爪被手腕俯仰干涉
			}
			else
			{
				fingerMediateM->resetSpeed();
				statusFlag=3;//手爪被手腕俯仰干涉
			}
		}
	}
	return statusFlag;
}

/**
  * 功  能：设置小臂俯仰角度
  * 参  数：设定的速度的参考值
  * 返回值：
  * 0：正常的角度赋值
  * 1: 小臂俯仰到达负方向的最小限位
  * 2: 小臂俯仰被手腕俯仰关节干涉
  * 3: 手腕俯仰关节角度太小 小臂俯仰被限位
  */
uint8_t XbotApp::setForearmPitchSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;
	int16_t temForearmPitchAngle=fBforearmPitchA->DATA_16;				//小臂角度
	int16_t temWristAngle=fBwristPitchA->DATA_16;									//手腕角度
	if(temSpeed==0)
	{
		forearmPitchM->resetSpeed();
		return statusFlag;
	}
	if(!limitFlag)
	{
		forearmPitchM->setSpeed(temSpeed);
		return statusFlag;
	}
	if(temSpeed<0)
	{
		if(temWristAngle<4600)
		{
			if(temForearmPitchAngle>2500)
				forearmPitchM->setSpeed(temSpeed);
			else if(temForearmPitchAngle>2100)
				forearmPitchM->setSpeed(temSpeed/3);
			else if(temForearmPitchAngle>2000)
			{
				forearmPitchM->setSpeed(-200);
				statusFlag=1;//小臂俯仰到达负方向的最小限位
			}
			else
			{
				forearmPitchM->resetSpeed();
				statusFlag=1;//小臂俯仰到达负方向的最小限位
			}
		}
		else
		{
			if(temForearmPitchAngle>4200)
				forearmPitchM->setSpeed(temSpeed);
			else if(temForearmPitchAngle>3700)
				forearmPitchM->setSpeed(temSpeed/3);
			else if(temForearmPitchAngle>3600)
			{
				forearmPitchM->setSpeed(-200);
				statusFlag=2;
			}
			else
			{
				forearmPitchM->resetSpeed();//小臂俯仰被手腕俯仰关节干涉
				statusFlag=2;
			}
		}
	}
	else
	{
		if(temWristAngle<600||temForearmPitchAngle<800)
		{
			forearmPitchM->resetSpeed();//手腕俯仰关节角度太小 小臂俯仰被限位
			statusFlag=3;
			return statusFlag;
		}
		
		if(temForearmPitchAngle<17500)
			forearmPitchM->setSpeed(temSpeed);
		else if(temForearmPitchAngle<17800)
			forearmPitchM->setSpeed(temSpeed/3);
		else if(temForearmPitchAngle<17900)
		{
			forearmPitchM->setSpeed(200);
			statusFlag=4;//小臂俯仰到达正方向最大限位
		}
		else
		{
			forearmPitchM->resetSpeed();
			statusFlag=4;//小臂俯仰到达正方向最大限位
		}
	}
	return statusFlag;
}

/**
  * 功  能：设置大臂俯仰角度
  * 参  数：设定的速度的参考值
  * 返回值：
	* 0：正常的速度赋值
  * 1：小臂太低产生的大臂俯仰限位
  * 2：大臂俯仰到达负方向的最大限位
  * 3：由把手产生的负方向限位
  * 4：由于支臂未支地产生的限位
  * 5：大臂到达最大的角度限位
  * 6：由把手产生的正方向限位
  */
uint8_t XbotApp::setBigArmPitchSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;
	uint16_t temSupportArmAngle=(uint16_t)((int32_t)(fBDiscA->DATA_16)*1125/32);		//支臂俯仰角度
	int16_t temBigArmPitchAngle=fBbigArmPitchA->DATA_16;				//大臂俯仰角度
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;			//大臂旋转角度
	int16_t temForearmPitchAngle=fBforearmPitchA->DATA_16;				//小臂角度
	
	if(temSpeed==0)
	{
		bigArmPitchM->resetSpeed();
		return statusFlag;
	}
	if(!limitFlag)
	{
		bigArmPitchM->setSpeed(temSpeed);
		return statusFlag;
	}
	if(temSpeed<0)//抬起
	{
		if(temForearmPitchAngle<1400)//小臂太低
		{
			bigArmPitchM->resetSpeed(); //小臂太低产生的大臂俯仰限位
			statusFlag=1;
			return statusFlag;
		}
		if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32-300)&&temSupportArmAngle<(ARM0_ANGLE_270*1125/32+300))//支臂撑起了
		{
			if(temBigArmRotateAngle<1800&&temBigArmRotateAngle>-3600)//大臂旋转在安全区间
			{
				if(temBigArmPitchAngle>-17500)
					bigArmPitchM->setSpeed(temSpeed);
				else if(temBigArmPitchAngle>-17800)
					bigArmPitchM->setSpeed(temSpeed/3);
				else if(temBigArmPitchAngle>-17900)
				{
					bigArmPitchM->setSpeed(-200);
					statusFlag=2;
				}
				else
				{
					bigArmPitchM->resetSpeed();//大臂俯仰到达负方向的最大限位
					statusFlag=2;
				}
			}
			else//非安全区间 只能抬到162度
			{
				if(temBigArmPitchAngle>-15700)
					bigArmPitchM->setSpeed(temSpeed);
				else if(temBigArmPitchAngle>-16100)
					bigArmPitchM->setSpeed(temSpeed/3);
				else if(temBigArmPitchAngle>-16200)
				{
					bigArmPitchM->setSpeed(-200);
					statusFlag=3;
				}
				else
				{
					bigArmPitchM->resetSpeed();//由把手产生的负方向限位
					statusFlag=3;
				}
			}
		}
		else //支臂未撑起 只能抬高到50度左右
		{
			if(temBigArmPitchAngle>-4450)
				bigArmPitchM->setSpeed(temSpeed);
			else if(temBigArmPitchAngle>-4850)
				bigArmPitchM->setSpeed(temSpeed/3);
			else if(temBigArmPitchAngle>-4950)
			{
				bigArmPitchM->setSpeed(-200);
				statusFlag=4;
			}
			else
			{
				bigArmPitchM->resetSpeed();//由于支臂未支地产生的限位
				statusFlag=4;
			}
		}
	}
	else//下俯
	{
		if(temBigArmRotateAngle<3600&&temBigArmRotateAngle>-1800)//大臂旋转在安全的区间
		{
			if(temBigArmPitchAngle<-2000)
				bigArmPitchM->setSpeed(temSpeed);
			else if(temBigArmPitchAngle<-1600)
				bigArmPitchM->setSpeed(temSpeed/3);
			else if(temBigArmPitchAngle<-1500)
			{
				bigArmPitchM->setSpeed(200);
				statusFlag=5;
			}
			else
			{
				bigArmPitchM->resetSpeed();//大臂到达最大的角度限位
				statusFlag=5;
			}
		}
		else
		{
			if(temBigArmPitchAngle<-3800)
				bigArmPitchM->setSpeed(temSpeed);
			else if(temBigArmPitchAngle<-3400)
				bigArmPitchM->setSpeed(temSpeed/3);
			else if(temBigArmPitchAngle<-3300)
			{
				bigArmPitchM->setSpeed(200);
				statusFlag=6;
			}
			else
			{
				bigArmPitchM->resetSpeed();//由把手产生的正方向限位
				statusFlag=6;
			}
		}
	}
	return statusFlag;
}

/**
  * 功  能：设置大臂旋转角度
  * 参  数：设定的速度的参考值
  * 返回值：
  * 0：正常设置速度
  * 1：大臂旋转被右边把手干涉
  * 2：支臂未撑起造成的干涉
  * 3：大臂俯仰角度太低造成的干涉
  * 4：大臂旋转被左边把手干涉
  * 5：支臂未撑起造成的干涉
  * 6：大臂俯仰角度太低造成的干涉
  */
uint8_t XbotApp::setBigArmRotateSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;
	uint16_t temSupportArmAngle=(uint16_t)((int32_t)(fBDiscA->DATA_16)*1125/32);		//支臂俯仰角度
	int16_t temBigArmPitchAngle=fBbigArmPitchA->DATA_16;				//大臂俯仰角度
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;			//大臂旋转角度
	if(temSpeed==0)
	{
		bigArmRotateM->resetSpeed();
		return statusFlag;
	}
	if(!limitFlag)
	{
		bigArmRotateM->setSpeed(temSpeed);
		return statusFlag;
	}
	if(temSpeed<0) 	//右旋
	{
		if(temBigArmPitchAngle<-1350) //大臂俯仰较高的状态下
		{
			if(temBigArmPitchAngle>-3200||temBigArmPitchAngle<-16300)//大臂俯仰在把手之下
			{
				if(temBigArmRotateAngle>-1200)
					bigArmRotateM->setSpeed(temSpeed);
				else if(temBigArmRotateAngle>-1600)
					bigArmRotateM->setSpeed(temSpeed/3);
				else if(temBigArmRotateAngle>-1700)
				{
					bigArmRotateM->setSpeed(-200);
					statusFlag=1;//大臂旋转被右边把手干涉
				}
				else
				{
					bigArmRotateM->resetSpeed();
					statusFlag=1;//大臂旋转被右边把手干涉
				}
			}
			else //大臂俯仰在把手之上 
			{
				/////
				if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32-300)&&temSupportArmAngle<(ARM0_ANGLE_270*1125/32+300))//支臂撑起
					bigArmRotateM->setSpeed(temSpeed);
				else
				{
					if(temBigArmRotateAngle>-3500)
						bigArmRotateM->setSpeed(temSpeed);
					else if(temBigArmRotateAngle>-3900)
						bigArmRotateM->setSpeed(temSpeed/3);
					else if(temBigArmRotateAngle>-4000)
					{
						bigArmRotateM->setSpeed(-200);
						statusFlag=2;//支臂未撑起造成的干涉
					}
					else
					{
						bigArmRotateM->resetSpeed();
						statusFlag=2;//支臂未撑起造成的干涉
					}
				}
			}
		}
		else//大臂俯仰角度太低
		{
			bigArmRotateM->resetSpeed();//大臂俯仰角度太低造成的干涉
			statusFlag=3;
		}
	}
	else						//左旋
	{
		if(temBigArmPitchAngle<-1350)
		{
			if(temBigArmPitchAngle>-3200||temBigArmPitchAngle<-16300)
			{
				if(temBigArmRotateAngle<3000)
					bigArmRotateM->setSpeed(temSpeed);
				else if(temBigArmRotateAngle<3400)
					bigArmRotateM->setSpeed(temSpeed/3);
				else if(temBigArmRotateAngle<3500)
				{
					bigArmRotateM->setSpeed(200);
					statusFlag=4;
				}
				else
				{
					bigArmRotateM->resetSpeed();//大臂旋转被左边把手干涉
					statusFlag=4;
				}
			}
			else
			{
				if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32-300)&&temSupportArmAngle<(ARM0_ANGLE_270*1125/32+300))//支臂撑起
					bigArmRotateM->setSpeed(temSpeed);
				else
				{
					if(temBigArmRotateAngle<4500)
						bigArmRotateM->setSpeed(temSpeed);
					else if(temBigArmRotateAngle<4900)
						bigArmRotateM->setSpeed(temSpeed/3);
					else if(temBigArmRotateAngle<5000)
					{
						bigArmRotateM->setSpeed(200);
						statusFlag=5;//支臂未撑起造成的干涉
					}
					else
					{
						bigArmRotateM->resetSpeed();
						statusFlag=5;//支臂未撑起造成的干涉
					}
				}
			}
		}
		else
		{
			bigArmRotateM->resetSpeed();//大臂俯仰角度太低造成的干涉
			statusFlag=6; 
		}
	}
	return statusFlag;
}


/**
  * 功  能：设置支臂旋转速度
  * 参  数：设定的速度的参考值
  * 返回值：
  * 0：正常设置速度
  * 1：大臂的位置形成的干涉，继续运动会造成机器人倾斜
  * 2：大臂的位置形成的干涉，继续运动会造成机器人倾斜
  * 
  */

#ifdef USEPOTENTIOMETER

uint8_t XbotApp::setSupportArmSpeed(int16_t temSpeed) 
{
	uint8_t statusFlag=0;
	uint16_t temSupportArmAngle=(uint16_t)((int32_t)(fBDiscA->DATA_16)*1125/32);								//支臂俯仰角度 转换为36000 制
	int16_t temBigArmPitchAngle=fBbigArmPitchA->DATA_16;													//大臂俯仰角度
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;												//大臂旋转角度
	if(temSpeed==0)
	{
		supportArmM->resetSpeed();
		return statusFlag;
	}
	if(!limitFlag)
	{
		supportArmM->setSpeed(temSpeed);
		return statusFlag;
	}
	if(temSupportArmAngle>(XBOT_CRITICAL_ARM0_DN*1125/32+400)&&temSupportArmAngle<(XBOT_CRITICAL_ARM0_UP*1125/32-400))//在绝对死区 禁止运动，必须关机 手动调整位置 或者使用取消限位 调整位置
	{
		statusFlag=5;
		supportArmM->resetSpeed();
		return statusFlag;
	}
	if(temSpeed<0) //负方向运动
	{
		if(temBigArmPitchAngle>-5100&&temBigArmRotateAngle>-4100&&temBigArmRotateAngle<5100)
		{
			if((temSupportArmAngle>(XBOT_CRITICAL_ARM0_UP_1*1125/32+500))||(temSupportArmAngle<(XBOT_CRITICAL_ARM0_DN*1125/32+500)))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle>(XBOT_CRITICAL_ARM0_UP_1*1125/32+300))
			{
				supportArmM->setSpeed(-2000);
			}
			else if(temSupportArmAngle>(XBOT_CRITICAL_ARM0_UP_1*1125/32+100))
			{
				supportArmM->setSpeed(-200);
				statusFlag=3;
			}
			else
			{
				supportArmM->resetSpeed();
				statusFlag=3;
			}
		}
		else
		{
			if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32+600))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32+300))
				supportArmM->setSpeed(temSpeed/5);
			else if(temSupportArmAngle>XBOT_LLL_ARM0*1125/32+100)
			{
				supportArmM->setSpeed(-200);
				statusFlag=1;
			}
			else
			{
				supportArmM->resetSpeed();//大臂的位置形成的干涉 
				statusFlag=1;
			}
		}
	}
	else //正方向运动
	{
		if(temBigArmPitchAngle>-5100&&temBigArmRotateAngle>-4100&&temBigArmRotateAngle<5100)
		{
			if((temSupportArmAngle<(XBOT_CRITICAL_ARM0_DN_1*1125/32-500))||(temSupportArmAngle>(XBOT_CRITICAL_ARM0_UP*1125/32-500)))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle<(XBOT_CRITICAL_ARM0_DN_1*1125/32-300))
			{
				supportArmM->setSpeed(2000);
			}
			else  if(temSupportArmAngle<(XBOT_CRITICAL_ARM0_DN_1*1125/32-100))
			{
				supportArmM->setSpeed(200);
				statusFlag=4;
			}
			else
			{
				supportArmM->resetSpeed();
				statusFlag=4;
			}
		}
		else 
		{
			if(temSupportArmAngle<(ARM0_ANGLE_270*1125/32-500))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle<(ARM0_ANGLE_270*1125/32-300))
				supportArmM->setSpeed(2000);
			else if(temSupportArmAngle<ARM0_ANGLE_270*1125/32)
			{
				supportArmM->setSpeed(200);
				statusFlag=2;
			}
			else
			{
				supportArmM->resetSpeed();//大臂的位置形成的干涉 
				statusFlag=2;
			}
		}
	}
	return statusFlag;
}
# else
uint8_t XbotApp::setSupportArmSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;
	uint16_t temSupportArmAngle=(uint16_t)((int32_t)(fBDiscA->DATA_16)*1125/32);	//支臂俯仰角度
	int16_t temBigArmPitchAngle=fBbigArmPitchA->DATA_16;													//大臂俯仰角度
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;												//大臂旋转角度
	if(temSpeed==0)
	{
		supportArmM->resetSpeed();
		return statusFlag;
	}
	if(!limitFlag)
	{
		supportArmM->setSpeed(temSpeed);
		return statusFlag;
	}
	
	if(temSpeed<0)
	{
		if(temBigArmPitchAngle>-5100&&temBigArmRotateAngle>-4100&&temBigArmRotateAngle<5100)
		{
			supportArmM->setSpeed(temSpeed);
		}
		else
		{
			if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32+500))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32+200))
				supportArmM->setSpeed(temSpeed/3);
			else if(temSupportArmAngle>XBOT_LLL_ARM0*1125/32)
			{
				supportArmM->setSpeed(-200);
				statusFlag=1;
			}
			else
			{
				supportArmM->resetSpeed();//大臂的位置形成的干涉 
				statusFlag=1;
			}
		}
	}
	else
	{
		if(temBigArmPitchAngle>-5100&&temBigArmRotateAngle>-4100&&temBigArmRotateAngle<5100)
		{
			supportArmM->setSpeed(temSpeed);
		}
		else 
		{
			if(temSupportArmAngle<(ARM0_ANGLE_270*1125/32-800))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle<(ARM0_ANGLE_270*1125/32-300))
				supportArmM->setSpeed(temSpeed/3);
			else if(temSupportArmAngle<ARM0_ANGLE_270*1125/32)
			{
				supportArmM->setSpeed(200);
				statusFlag=2;
			}
			else
			{
				supportArmM->resetSpeed();//大臂的位置形成的干涉 
				statusFlag=2;
			}
		}
	}
	return statusFlag;
}
#endif
/**
  * 功  能：解除机械臂收起后的角度锁定
  * 参  数：无
  * 返回值：无
  * 
  */
bool  XbotApp::unlockArms(int16_t angle)
{
	if(fBforearmPitchA->DATA_16<1500||fBwristPitchA->DATA_16<1100||fBbigArmPitchA->DATA_16>-800)
	{
		suppArmRunToPos(angle,false);

		if(fBforearmPitchA->DATA_16<1500)//小臂小于14度
		{
			forearmPitchM->setPWMSpeed(20000);
			forearmPitchM	->resetUspeedTime();
		}
		else //小臂大于15度
		{
			forearmPitchM->setPWMSpeed(0);
			forearmPitchM	->resetUspeedTime();
		}
		
		if(fBwristPitchA->DATA_16<1100) //手腕小于11度
		{
			wristPitchM->setPWMSpeed(20000);
			wristPitchM	->resetUspeedTime();
		}
		else
		{
			wristPitchM	->resetUspeedTime();
			wristPitchM->setPWMSpeed(0);
		}
		
		if(fBbigArmPitchA->DATA_16>-800) //大臂大于-8度
		{
			bigArmPitchM->setPWMSpeed(-20000);
			bigArmPitchM	->resetUspeedTime();
		}
		else//大臂小于-8度
		{
			bigArmPitchM->setPWMSpeed(0);
			bigArmPitchM	->resetUspeedTime();
		}
		return false;
	}
	return true;
}


/**
  * 功  能：解除Z向上的锁定
  * 参  数：无
  * 返回值：无
  * 
  */
bool XbotApp::unlockForZup()
{
// 	uint16_t temSupportArmAngle=(uint16_t)((int32_t)(fBDiscA->DATA_16)*1125/32);		//支臂俯仰角度

	if(unlockArms(XBOT_LLL_ARM0))//先打开三个关节
	{
		if((fBDiscA->DATA_16)<(XBOT_LLL_ARM0-4)||(fBDiscA->DATA_16)>(XBOT_LLL_ARM0+4))//支臂支起
		{
			suppArmRunToPos(XBOT_LLL_ARM0,false);
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

/****************************************************************************************************/
/************************************XYZ控制算法模式**************************************************/
/****************************************************************************************************/

#define LL1			558
#define LL2			538.2
#define LL3			280.0		//117
#define HH0 		14.0
#define YY0 		7.0
#define M_PI_180	0.0001745329

#define L1L1 	311364								//558*558
#define L2L2 	289659.24							//538.2*538.2
#define L1L2 	300315.6							//558*538.2
#define L1L22 600631.2							//558*538.2*2

#define XBOT_DEV_ARM1	0X00		//大臂旋转
#define XBOT_DEV_ARM2	0X01		//大臂俯仰
#define XBOT_DEV_ARM3	0X02		//小臂俯仰
#define XBOT_DEV_ARM4	0X03		//手腕俯仰
#define XBOT_DEV_ARM5	0X04		//手腕旋转
#define XBOT_DEV_ARM6	0X05		//云台俯仰
#define XBOT_DEV_ARM7	0X06		//云台旋转
#define XBOT_ARM_DEV_TOTAL 0x09

#define BIGARMSUBANGLE_1 (0)
#define BIGARMSUBANGLE 0.028443

void XbotApp::XbotArmSetXyzCtrlMode()
{
	int16_t temAngle[XBOT_ARM_DEV_TOTAL]={0};
	double 	Angle[XBOT_ARM_DEV_TOTAL]={0};		//五关节角度值，单位度
	int16_t SpeedY,SpeedX,SpeedZ;
	int16_t TempSpeed=0;
	int8_t direction=0;

	if(fBTerminalData[5]&0x08)
	{
		SpeedZ=-(fBTerminalData[5]&0x07);
	}
	
	else
	{
		SpeedZ=fBTerminalData[5]&0x07;
	}
	
	if(fBTerminalData[7]&0x08)
	{
		SpeedX=-(fBTerminalData[7]&0x07);
	}
	else
	{
		SpeedX=fBTerminalData[7]&0x07;
	}
	
	if(((fBTerminalData[7]&0x80)>>4)&0x08)
	{
		SpeedY=((fBTerminalData[7]&0x70)>>4)&0x07;
	}
	else
	{
		SpeedY=-((fBTerminalData[7]&0x70)>>4&0x07);
	}

	temAngle[XBOT_DEV_ARM1]=fBbigArmRotateA->DATA_16;
	temAngle[XBOT_DEV_ARM2]=18000+fBbigArmPitchA->DATA_16;
	temAngle[XBOT_DEV_ARM3]=(fBforearmPitchA->DATA_16);
	temAngle[XBOT_DEV_ARM4]=(fBwristPitchA->DATA_16);
	Angle[XBOT_DEV_ARM1] = (double)temAngle[XBOT_DEV_ARM1]*M_PI_180-BIGARMSUBANGLE_1;
	Angle[XBOT_DEV_ARM2] = (double)temAngle[XBOT_DEV_ARM2]*M_PI_180+BIGARMSUBANGLE;
	Angle[XBOT_DEV_ARM3] = (double)temAngle[XBOT_DEV_ARM3]*M_PI_180;
	if(SpeedY == 0x00 && SpeedZ == 0x00 && SpeedX == 0x00)
	{
		runOnXYZLine(0,Angle,0);
	}
	else
	{
		if(SpeedZ!=0)
		{
			direction=3;
			if(runOnXYZLine(direction,Angle,SpeedZ)<250)
			{
				if(SpeedZ<0)//降下手臂
				{
					if(fBforearmPitchA->DATA_16<2000)
					{
						setBigArmPitchSpeed(0);
						setForearmPitchSpeed(0);
						setWristPitchSpeed(0);
						return;
					}
					if((fBbigArmRotateA->DATA_16<3600)&&(fBbigArmRotateA->DATA_16>-1800))
						allArmRunToPos(fBbigArmRotateA->DATA_16,-1000,2000,2000,0,15000,0,XBOT_LLL_ARM0);
					else
						allArmRunToPos(fBbigArmRotateA->DATA_16,-3300,6600,6600,0,12700,0,XBOT_LLL_ARM0);
					return;
				}
				else	//升起手臂
				{
					if(unlockForZup())
					{
						allArmRunToPos(fBbigArmRotateA->DATA_16,-9000,18000,18000,0,7000,0,XBOT_LLL_ARM0);
						return;
					}
					else
						return;
				}
			}
		}
		else if(SpeedY!=0)
		{
			direction=1;
			runOnXYZLine(direction,Angle,SpeedY);
		}
		else if(SpeedX!=0)
		{
			direction=2;
			runOnXYZLine(direction,Angle,SpeedX);
		}
	}
	
	//限位 主要是角度限位
	if((temAngle[XBOT_DEV_ARM3]>15500&&(forearmPitchM->getSpeed()>0))||(temAngle[XBOT_DEV_ARM4]<600&&(wristPitchM->getSpeed()<0)))
	{
		bigArmRotateM->resetSpeed();
		bigArmPitchM->resetSpeed();
		forearmPitchM->resetSpeed();
		wristPitchM->resetSpeed();
		wristRotateM->resetSpeed();
	}

	//手爪旋转可控	
	if(fBTerminalData[6]&0x80)
	{
		TempSpeed=((int16_t)((fBTerminalData[6]&0x70)>>0x04)*1714);
	}
	else
	{
		TempSpeed=(-((int16_t)((fBTerminalData[6]&0x70)>>0x04)*1714));
	}	
	if(TempSpeed)
			wristRotateM->setSpeed(TempSpeed);
}

/**
  * 功  能：手抓末端沿Z直线运动
  * 参  数：运动速度
  * 返回值：无
  * 
  */
void XbotApp::runOnZZZLine(int16_t speed)
{
	double temSpeed=0;
	double maxSpeed;
	double temBigArmPitchSpeed=0;
	double temforeArmPitchSpeed=0;
	double temWristPitchSpeed=0;
	double checkPos=0;
	double checkPos_1=0;
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;
	int16_t temForearmPitchAngle=fBforearmPitchA->DATA_16;
	int16_t temWristPitchAngle=fBwristPitchA->DATA_16;
	
	double bigArmPitchRadian= ((double)(fBbigArmPitchA->DATA_16+18000)*2*PI)/36000+ZZZ_LINE_RADIAN;	//大臂弧度角
	double foreArmPitchRadian=((double)fBforearmPitchA->DATA_16*2*PI)/36000;				//小臂弧度角
	double wristPitchRadian =((double)fBwristPitchA->DATA_16*2*PI)/36000;
	
	double temRadian=PI-foreArmPitchRadian-bigArmPitchRadian;												//小臂末端与运动轨迹直线之间的夹角

	double temRadian_1=wristPitchRadian-foreArmPitchRadian+(PI/2-bigArmPitchRadian+ZZZ_LINE_RADIAN); 
	
	double LLLCOSW1=BIG_ARM_LEN*cos(bigArmPitchRadian);
	double LLLCOSW2=FORE_ARM_LEN*cos(temRadian);
	
	double LLLSINW1=BIG_ARM_LEN*sin(bigArmPitchRadian-ZZZ_LINE_RADIAN);
	double LLLSINW2=FORE_ARM_LEN*sin(temRadian+ZZZ_LINE_RADIAN);
	
	checkPos=BIG_ARM_LEN*cos(bigArmPitchRadian-ZZZ_LINE_RADIAN)+FORE_ARM_LEN*cos(temRadian+ZZZ_LINE_RADIAN);
	checkPos_1=checkPos-WRIST_ARM_LEN*sin(temRadian_1);
	
	if(checkPos<30000)//||checkPos_1<30000)
	{
		if(speed>0)
		{
			if(unlockForZup())
			{
				allArmRunToPos(temBigArmRotateAngle,-9000,18000,18000,0,9000,0,XBOT_LLL_ARM0);
			}
		}
		else
		{
			if(temForearmPitchAngle<2000)
			{
				setBigArmPitchSpeed(0);
				setForearmPitchSpeed(0);
				setWristPitchSpeed(0);
				return;
			}
			if((temBigArmRotateAngle<3600)&&(temBigArmRotateAngle>-1800))
				allArmRunToPos(temBigArmRotateAngle,-1000,2000,2000,0,17000,0,XBOT_LLL_ARM0);
			else
				allArmRunToPos(temBigArmRotateAngle,-3300,6600,6600,0,14700,0,XBOT_LLL_ARM0);
		}
		return;
	}
	if(checkPos_1<37000)
	{
			setBigArmPitchSpeed(0);
			setForearmPitchSpeed(0);
			setWristPitchSpeed(0);
			return;
	}
	if(LLLSINW1>LLLSINW2)
		temSpeed=-(double)speed;
	else
		temSpeed=(double)speed;
	
	if(temSpeed<0&&((temForearmPitchAngle>13000)||(temWristPitchAngle>13000)))
	{
		temforeArmPitchSpeed=0;
		temBigArmPitchSpeed=0;
	}
	else
	{
		temforeArmPitchSpeed=temSpeed;
		temBigArmPitchSpeed=(temSpeed*LLLCOSW2)/(LLLCOSW1+LLLCOSW2);
	}

	temWristPitchSpeed=temforeArmPitchSpeed-temBigArmPitchSpeed;
	
	//比较三个速度的大小关系
	maxSpeed=MAX(temBigArmPitchSpeed,temforeArmPitchSpeed);
	maxSpeed=MAX(maxSpeed,temWristPitchSpeed);
	
	temSpeed=ABS(temSpeed);
	temBigArmPitchSpeed=(temBigArmPitchSpeed/maxSpeed)*temSpeed;
	temforeArmPitchSpeed=(temforeArmPitchSpeed/maxSpeed)*temSpeed;
	temWristPitchSpeed=(temWristPitchSpeed/maxSpeed)*temSpeed;
	
	setBigArmPitchSpeed(temBigArmPitchSpeed);
	setForearmPitchSpeed(-temforeArmPitchSpeed);
	setWristPitchSpeed(-temWristPitchSpeed);

// 	bigArmPitchM->setSpeed(temBigArmPitchSpeed);
// 	forearmPitchM->setSpeed(-temforeArmPitchSpeed);
// 	wristPitchM->setSpeed(-temWristPitchSpeed);

	if(bigArmPitchM->getSpeed()==0||forearmPitchM->getSpeed()==0||wristPitchM->getSpeed()==0)//有一个关节到达限位值 停止运动
	{
		setBigArmPitchSpeed(0);
		setForearmPitchSpeed(0);
		setWristPitchSpeed(0);
		return;
	}

}

/**
  * 功  能：手抓末端沿Y直线运动
  * 参  数：运动速度
  * 返回值：无
  * 
  */
void XbotApp::runOnYYYLine(int16_t speed)
{
	double temSpeed=(double)speed;
// 	double temSpeed=0;
	double maxSpeed=0;
	double checkPos=0;
	double checkPos_1=0;
	double temBigArmPitchSpeed=0;
	double temforeArmPitchSpeed=0;
	double temWristPitchSpeed=0;
	double bigArmPitchRadian= ((double)(fBbigArmPitchA->DATA_16+18000)*2*PI)/36000+YYY_LINE_RADIAN;	//大臂弧度角
	double foreArmPitchRadian=((double)fBforearmPitchA->DATA_16*2*PI)/36000;				//小臂弧度角
	double wristPitchRadian =((double)fBwristPitchA->DATA_16*2*PI)/36000;
	double temRadian=PI-foreArmPitchRadian-bigArmPitchRadian;												//小臂末端与运动轨迹直线之间的夹角
	
	double temRadian_1=wristPitchRadian-foreArmPitchRadian+(PI/2-bigArmPitchRadian+YYY_LINE_RADIAN); 

	double LLLCOSW1=BIG_ARM_LEN*cos(bigArmPitchRadian);
	double LLLCOSW2=FORE_ARM_LEN*cos(temRadian);

	checkPos=LLLCOSW1+LLLCOSW2;
	checkPos_1=checkPos-WRIST_ARM_LEN*sin(temRadian_1);
	
	if((checkPos<40000||checkPos_1<40000)&&temSpeed>0)
	{
		temforeArmPitchSpeed=0;
		temBigArmPitchSpeed=0;
	}
	else if(temSpeed<0&&checkPos<31000)
	{
		temforeArmPitchSpeed=0;
		temBigArmPitchSpeed=0;
	}
	else if(temSpeed<0&&((fBforearmPitchA->DATA_16>13000)||(fBwristPitchA->DATA_16>15000)))
	{
		temforeArmPitchSpeed=0;
		temBigArmPitchSpeed=0;
	}
	else
	{
		temforeArmPitchSpeed=temSpeed;
		temBigArmPitchSpeed=(temSpeed*LLLCOSW2)/(LLLCOSW1+LLLCOSW2);
	}
	temWristPitchSpeed=temforeArmPitchSpeed-temBigArmPitchSpeed;
	
	//比较三个速度的大小关系
	maxSpeed=MAX(temBigArmPitchSpeed,temforeArmPitchSpeed);
	maxSpeed=MAX(maxSpeed,temWristPitchSpeed);
	
	temSpeed=ABS(temSpeed);
	temBigArmPitchSpeed=(temBigArmPitchSpeed/maxSpeed)*temSpeed;
	temforeArmPitchSpeed=(temforeArmPitchSpeed/maxSpeed)*temSpeed;
	temWristPitchSpeed=(temWristPitchSpeed/maxSpeed)*temSpeed;
	
	setBigArmPitchSpeed(temBigArmPitchSpeed);
	setForearmPitchSpeed(-temforeArmPitchSpeed);
	setWristPitchSpeed(-temWristPitchSpeed);

// 	bigArmPitchM->setSpeed(temBigArmPitchSpeed);
// 	forearmPitchM->setSpeed(-temforeArmPitchSpeed);
// 	wristPitchM->setSpeed(-temWristPitchSpeed);

	if(bigArmPitchM->getSpeed()==0||forearmPitchM->getSpeed()==0||wristPitchM->getSpeed()==0)//有一个关节到达限位值 停止运动
	{
		setBigArmPitchSpeed(0);
		setForearmPitchSpeed(0);
		setWristPitchSpeed(0);
		return;
	}
}

/**
  * 功  能：手抓末端转动
  * 参  数：运动速度
  * 返回值：无
  * 
  */
void XbotApp::runOnXXXLine(int16_t speed)
{
	int16_t temSpeed=speed;
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;			//大臂旋转角度
	
	double bigArmPitchRadian= ((double)(fBbigArmPitchA->DATA_16+18000)*2*PI)/36000;	//大臂弧度角
	double foreArmPitchRadian=((double)fBforearmPitchA->DATA_16*2*PI)/36000;				//小臂弧度角
	double temRadian=PI-foreArmPitchRadian-bigArmPitchRadian;												//小臂末端与运动轨迹直线之间的夹角
	if((BIG_ARM_LEN*cos(bigArmPitchRadian)+FORE_ARM_LEN*cos(temRadian))>37000)
	{
		if(temSpeed<0)
		{
			if(temBigArmRotateAngle>-12300)
				setBigArmRotateSpeed(-temSpeed);
			else
				setBigArmRotateSpeed(0);
		}
		else
		{
			if(temBigArmRotateAngle<12300)
				setBigArmRotateSpeed(-temSpeed);
			else
				setBigArmRotateSpeed(0);
		}
	}
	else
	{
		setBigArmRotateSpeed(0);
	}
}

/**
  * 功  能：镜像控制机械臂 主要是调试用
  * 参  数：无
  * 返回值：无
  * 
  */
void XbotApp::controlArmISO()
{
	int temMode=signalType;
	if(temMode==WIRE_WORK_MODE)
	{
		while(wirePort->readAllow())
		{
			while (!armPort->putChar(wirePort->getChar()));
		}
		while( armPort->readAllow())
		{
			while (!wirePort->putChar(armPort->getChar()));
		}
	}
	else if(temMode==WIRELESS_WORK_MODE)
	{
		while(wireLessPort->readAllow())
		{
			while (!armPort->putChar(wireLessPort->getChar()));
		}
		while( armPort->readAllow())
		{
			while (!wireLessPort->putChar(armPort->getChar()));
		}
	}
	
//GPSPort交互的串口镜像
	
// 	int temMode=signalType;
// 	if(temMode==WIRE_WORK_MODE)
// 	{
// 		while(wirePort->readAllow())
// 		{
// 			while (!GPSPort->putChar(wirePort->getChar()));
// 		}
// 		while( GPSPort->readAllow())
// 		{
// 			while (!wirePort->putChar(GPSPort->getChar()));
// 		}
// 	}
// 	else if(temMode==WIRELESS_WORK_MODE)
// 	{
// 		while(wireLessPort->readAllow())
// 		{
// 			while (!GPSPort->putChar(wireLessPort->getChar()));
// 		}
// 		while( GPSPort->readAllow())
// 		{
// 			while (!wireLessPort->putChar(GPSPort->getChar()));
// 		}
// 	}
}

double XbotApp::runOnXYZLine(int8_t direction,double *Angle,int16_t speed)				//平行于笛卡尔坐标的X轴运动 闭环控制
{
	static double XXX,YYY,ZZZ;																										//起始时小臂末端的笛卡尔坐标值
	static int8_t backDirection=0;
	double TEMXXXYYY,XY2,XYZ2,XY,XYZ;
	double temA0,temA1,temA2;//要到达的目标角度
	double distance=0.0;
	if(xyzFlag==false)
	{
		TEMXXXYYY=LL1*cos((double)Angle[1])-LL2*cos((double)(Angle[1]+Angle[2]));
		XXX=TEMXXXYYY*cos(Angle[0]);
		YYY=TEMXXXYYY*sin(Angle[0]);
		ZZZ=LL1*sin(Angle[1])-LL2*sin((double)(Angle[1]+Angle[2]));
		backDirection=0;
		xyzFlag=true;
	}
	if(direction==1)				//y方向运动
	{
		TEMXXXYYY=LL1*cos((double)Angle[1])-LL2*cos((double)(Angle[1]+Angle[2]));
		if(backDirection==2)//上次是X方向运动
		{
			XXX=TEMXXXYYY*cos(Angle[0]);
		}
		else if(backDirection==3)//上次是Z方向运动
		{
			ZZZ=LL1*sin(Angle[1])-LL2*sin(Angle[1]+Angle[2]);
		}
		YYY=TEMXXXYYY*sin(Angle[0])+speed*3;//y坐标重新赋值
		XY2=XXX*XXX+YYY*YYY;
		XYZ2=XY2+ZZZ*ZZZ;
		XY=sqrt(XY2);
		XYZ=sqrt(XYZ2);
		if(XXX<300)//stop
		{
			bigArmRotateM->resetSpeed();
			bigArmPitchM->resetSpeed();
			forearmPitchM->resetSpeed();
		}
		else
		{
			temA0=(atan(YYY/XXX)+BIGARMSUBANGLE_1)*18000/PI;
			temA1=((atan(ZZZ/XY)+acos((L1L1+XYZ2-L2L2)/(2*LL1*XYZ))-BIGARMSUBANGLE)*18000/PI)-18000;				//大臂俯仰角度赋值
			temA2=(acos((L1L1+L2L2-(XYZ2))/L1L22))*18000/PI;
			threeArmRunToPos(temA0,temA1,temA2,speed);
		}
		backDirection=direction;
		distance=XXX;
	}
	else if(direction==2)		//x方向运动 前后运动
	{
		TEMXXXYYY=LL1*cos((double)Angle[1])-LL2*cos((double)(Angle[1]+Angle[2]));
		if(backDirection==1)//上次是Y方向运动
		{
			YYY=TEMXXXYYY*sin(Angle[0]);
		}
		else if(backDirection==3)//上次是Z方向运动
		{
			ZZZ=LL1*sin(Angle[1])-LL2*sin(Angle[1]+Angle[2]);
		}
		XXX=TEMXXXYYY*cos(Angle[0])+speed*3/2;//y坐标重新赋值
		XY2=XXX*XXX+YYY*YYY;
		XYZ2=XY2+ZZZ*ZZZ;
		XY=sqrt(XY2);
		XYZ=sqrt(XYZ2);
		temA0=(atan(YYY/XXX)+BIGARMSUBANGLE_1)*18000/PI;
		temA1=((atan(ZZZ/XY)+acos((L1L1+XYZ2-L2L2)/(2*LL1*XYZ))-BIGARMSUBANGLE)*18000/PI)-18000;				//大臂俯仰角度赋值
		temA2=(acos((L1L1+L2L2-(XYZ2))/L1L22))*18000/PI;																//小臂俯仰角度赋值
		if(XXX<330&&speed<0)//stop
		{
			bigArmRotateM->resetSpeed();
			bigArmPitchM->resetSpeed();
			forearmPitchM->resetSpeed();
		}
		else if(XXX>250)
		{
			threeArmRunToPos(temA0,temA1,temA2,speed*2/3);
		}
		backDirection=direction;
		distance=XXX;
	}
	else if(direction==3)		//z方向运动
	{
		TEMXXXYYY=LL1*cos((double)Angle[1])-LL2*cos((double)(Angle[1]+Angle[2]));
		if(backDirection==1)//上次是X方向运动
		{
			YYY=TEMXXXYYY*sin(Angle[0]);
		}
		else if(backDirection==2)//上次是X方向运动
		{
			XXX=TEMXXXYYY*cos(Angle[0]);
		}
		ZZZ=LL1*sin(Angle[1])-LL2*sin(Angle[1]+Angle[2])+speed;
		XY2=XXX*XXX+YYY*YYY;
		XYZ2=XY2+ZZZ*ZZZ;
		XY=sqrt(XY2);
		XYZ=sqrt(XYZ2);
		temA1=((atan(ZZZ/XY)+acos((L1L1+XYZ2-L2L2)/(2*LL1*XYZ))-BIGARMSUBANGLE)*18000/PI)-18000;				//大臂俯仰角度赋值
		temA2=(acos((L1L1+L2L2-(XYZ2))/L1L22))*18000/PI;																//小臂俯仰角度赋值
		if(XXX<300)//stop
		{
			bigArmRotateM->resetSpeed();
			bigArmPitchM->resetSpeed();
			forearmPitchM->resetSpeed();
		}
		else
			threeArmRunToPos((Angle[0]+BIGARMSUBANGLE_1)*18000/PI,temA1,temA2,speed/3);
		backDirection=direction;
		distance=XXX;
	}
	else if(direction==0)
	{
		//停止运动
		setBigArmRotateSpeed(0);
		setBigArmPitchSpeed(0);
		setForearmPitchSpeed(0);
		distance=0;
	}
	int16_t TempSpeed=0;
	TempSpeed = bigArmPitchM->getSpeed() + forearmPitchM->getSpeed();
	wristPitchM->setSpeed_1(TempSpeed);
	TempSpeed =bigArmRotateM->getSpeed()*1.38545;
	wristRotateM->setSpeed_1(-TempSpeed);
	checkBlockError();
	return distance;
}
/**
  * 功  能：检测关节是否堵转，手抓夹持除外
  * 参  数：无
  * 返回值：true 有堵转关节
  * 				false无堵转关节
  */
bool XbotApp::checkBlockError()
{
	bool error_1=false;
	bool error_2=false;
	bool error_3=false;
	bool error_4=false;
	bool error_5=false;
	bool error_6=false;
	bool error_7=false;
	bool error_8=false;
	if(supportArmM->getErrorFlag()==0x0b||supportArmM->getErrorFlag()==0x0c)
		error_1=true;
	if(bigArmRotateM->getErrorFlag()==0x0b||bigArmRotateM->getErrorFlag()==0x0c)
		error_2=true;
	if(bigArmPitchM->getErrorFlag()==0x0b||bigArmPitchM->getErrorFlag()==0x0c)
		error_3=true;
	if(forearmPitchM->getErrorFlag()==0x0b||forearmPitchM->getErrorFlag()==0x0c)
		error_4=true;
	if(wristPitchM->getErrorFlag()==0x0b||wristPitchM->getErrorFlag()==0x0c)
		error_5=true;
	if(wristRotateM->getErrorFlag()==0x0b||wristRotateM->getErrorFlag()==0x0c)
		error_6=true;
	if(panTiltPitchM->getErrorFlag()==0x0b||panTiltPitchM->getErrorFlag()==0x0c)
		error_7=true;
	if(panTiltRotateM->getErrorFlag()==0x0b||panTiltRotateM->getErrorFlag()==0x0c)
		error_8=true;
	if(error_1||error_2||error_3||error_4||error_5||error_6||error_7||error_8)
	{
		if(!error_1)
			supportArmM->resetSpeed();
		if(!error_2)
			bigArmRotateM->resetSpeed();
		if(!error_3)
			bigArmPitchM->resetSpeed();
		if(!error_4)
			forearmPitchM->resetSpeed();
		if(!error_5)
			wristPitchM->resetSpeed();
		if(!error_6)
			wristRotateM->resetSpeed();
		if(!error_7)
			panTiltPitchM->resetSpeed();
		if(!error_8)
			panTiltRotateM->resetSpeed();
		return true;
	}
	else
		return false;
}

//修改说明：启动模式 先启动小臂 最后启动手腕和大臂
	
//					收起模式(C模式):最后U模式一段，首先收起手腕和大臂，最后收起小臂















