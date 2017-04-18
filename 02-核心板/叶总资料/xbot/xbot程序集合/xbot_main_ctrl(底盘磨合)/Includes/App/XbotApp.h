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
#ifndef _XBOT_APP_H
#define _XBOT_APP_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "CodedDiscControl.h"
#include "MotorControl.h"
#include "PowerControl.h"
#include "TerminalControl.h"
#include "OtherDeviceControl.h"
#include "GpsImuControl.h"
#include "Timer.h"
#include "LEDLighter.h"
#include "OpticalBobbin.h"

/* 类型定义 --------------------------------------------------------------------*/
//枚举模式ID
typedef enum
{
	TTTModel,		//T模式 正常工作，单关节控制
	AAAModel,		//A模式 手臂半展
	BBBModel,		//B模式 手臂前抓取
	CCCModel,		//C模式 手臂收起
	DDDModel,		//D模式 手臂前观测
	EEEModel,		//E模式 手臂全展开
	HHHModel,		//H模式 支臂抬起
	IIIModel,		//I模式 支臂支地
	JJJModel,		//J模式 支臂收起
	KKKModel,		//K模式 支臂水平
	LLLModel,		//L模式 支臂微支
	
	MMMModel,		//M模式 线缆盘放线或者云台归位
	NNNModel,		//N模式 线缆盘收线或者手抓归位
	
	SSSModel,		//S模式 机器人静止所有速度为0 但是其他的设备（如：灯）还能控制 
	XLLModel,		//三维模式 X向左
	XRRModel, 	//三维模式 X向右
	YFFModel,		//三维模式 Y向前
	YBBModel,		//三维模式 Y向后
	ZUUModel,		//三维模式 Z向上
	ZDDModel,		//三维模式 Z向下
	XYZModel		//笛卡尔坐标系的三维模式
}workIdType;

//枚举工作模式 正常模式和镜像模式
typedef enum
{
	NORMAL,
	MIRROR,
}workModelType;


/* 宏定义-----------------------------------------------------------------------*/ 

class XbotApp
{
public:
	XbotApp();
	~XbotApp();

	void runOnTime2();								//运行在定时器TIM2中的函数
	void runOnTime3();								//运行在定时器TIM3中的函数
	void runOnTime4();								//运行在定时器TIM4中的函数
	void openUserInterrupt();					//打开用户中断
	SerialPort *GPSPort;							//GPS和IMU通信的串口
private:
	
	Timer *t1;												//定时器1
	Timer *t2;												//定时器2
	Timer *t3;												//定时器3

	LEDLighter *led_1;// = new LEDLighter(GPIOC,GPIO_Pin_0);//默认点亮
	LEDLighter *led_2;
	LEDLighter *led_3;
	volatile int8_t signalType;								//信号类型	
	volatile int8_t ectQuantity;							//本体电压，电压低于24伏，自动关机
	volatile int8_t *checkTime;								//用于计算检测超时的数组

	volatile workModelType workModel;					//工作模式
	volatile bool riciveCboxFlag;
	static workIdType workId;									//工作ID
	static bool limitFlag;										//限位标志 默认限位 为true 失能限位后置为false
	static bool zoreCtrFlag;									//校零控制标志位，默认为false，开启后，大臂、小臂、手腕三关节速度设置模式变为U模式
	
	bool xyzFlag;														//三维模式三关节的运动与否标志 0:无XYZ模式 1:y方向运动 2:x方向运动 3:z方向运动
	int8_t wireLength;												//线缆盘线长

	volatile bool sendEnaSpeedOk;							//设备指令发送完成标志 默认未完成 为false 开机自动激活关节运动指令
	volatile bool saveSendOk;									//保存指令发送完成标志 默认完成 为true 
	volatile bool offLimitSendOk;							//取消限位发送完成标志 默认完成 为true 
	volatile bool reInitPosSendOk;						//零位重设发送完成标志 默认完成 为true 
	volatile bool reWeaponSendOk;							//武器发射发送完成标志 默认完成 为true 
	uint8_t *fBTerminalData;									//反馈的终端数据暂存
	
//static ctrData *fBsupportArmA;						//反馈的支臂电机角度暂存
	static ctrData *fBbigArmRotateA;					//反馈的大臂旋转电机角度暂存
	static ctrData *fBbigArmPitchA; 					//反馈的大臂俯仰电机角度暂存
	static ctrData *fBforearmPitchA;					//反馈的小臂俯仰电机角度暂存
	static ctrData *fBwristPitchA;						//反馈的手腕俯仰电机角度暂存
	static ctrData *fBwristRotateA;						//反馈的手腕旋转电机角度暂存
	static ctrData *fBpanTiltPitchA;					//反馈的云台俯仰电机角度暂存
	static ctrData *fBpanTiltRotateA;					//反馈的云台旋转电机角度暂存
	static ctrData *fBfingerMediateA;					//反馈的手爪捏合电机角度暂存
	static ctrData *fBcameraPitchA;						//反馈的相机俯仰电机角度暂存
	static 	CodeDiscData *fBDiscA;						//反馈的绝对码盘数据暂存
	
	ctrData	*fBLeftSpeed;											//反馈的左电机速度暂存
	ctrData	*fBRightSpeed;										//反馈的右电机速度暂存
	
	ctrData *fBEctQuantity_1;									//反馈的电源电量1暂存
	ctrData *fBEctQuantity_2;									//反馈的电源电量2暂存
	ctrData *fBEctQuantity_3;									//反馈的电源电量3暂存
	ctrData *fBEctQuantity_4;									//反馈的电源电量4暂存
	int8_t FBTemperature_1;										//反馈的温度
	int8_t FBTemperature_2;										//反馈的温度
	int8_t FBTemperature_3;										//反馈的温度
	static SerialPort *wireLessPort;					//和终端无线通信的串口
	static SerialPort *wirePort;							//和终端有线通信的串口
	static SerialPort *codedDiscPort;					//和码盘通信的串口
	static SerialPort *armPort;								//和机械臂通信的串口
	static SerialPort *underpanPort;					//和底盘三电机以及电源控制板通信的串口
// 	SerialPort *GPSPort;										//GPS和IMU通信的串口

	TerminalControl *Terminal;								//终端通信的协议类变量

	MotorControl *leftRunM;										//行进左电机
	MotorControl *rightRunM;									//行进右电机
	static MotorControl *supportArmM;					//支臂电机
	
	static MotorControl *bigArmRotateM;				//大臂旋转电机
	static MotorControl *bigArmPitchM; 				//大臂俯仰电机
	static MotorControl *forearmPitchM;				//小臂俯仰电机
	static MotorControl *wristPitchM;					//手腕俯仰电机
	static MotorControl *wristRotateM;				//手腕旋转电机
	static MotorControl *panTiltPitchM;				//云台俯仰电机
	static MotorControl *panTiltRotateM;			//云台旋转电机
	static MotorControl *fingerMediateM;			//手爪捏合电机
	static MotorControl *cameraPitchM;				//相机俯仰电机

	PowerControl *power;											//电源管理通信协议类变量
	OtherDeviceControl *OtherDevice;					//其他设备的通信协议变量
	CodedDiscControl *CodedDisc;							//绝对码盘的通信协议类变量
	GpsImuControl *gpsDevice;									//GPS设备的通信协议类变量
	OpticalBobbin *opticalBobbinDevice;				//自动线缆盘的通信协议类变量
	
	
	
private:
	
//重启特殊命令
	void resetOffLimit();							//重启取消限位的命令
	void resetReInit();								//重启重置零位的命令
	void resetSave();									//重启保存命令
	void resetWeapon();								//重启武器命令
	void resetEnaSpeed();							//重启使能速度指令
//发送特殊命令
	void sendOffLimitCommand();				//发送取消限位指令
	void sendReInitCommand();					//发送零位重设命令
	void sendSaveCommand();						//发送保存设置命令
	void sendWeaponCommand();					//发送武器发射命令
	void sendEnaSpeedCommand();				//发送使能速度指令
//检测特殊命令是否发送完毕
	void checkOffLimit();							//检测取消限位指令是否发送完毕
	void checkReInit();								//检测零位重设命令是否发送完毕
	void checkSave();									//检测角度保存命令是否发送完毕
// 	void checkWeapon();							//检测武器发射命令是否发送完毕
	void checkEnaSpeed();							//检测使能速度指令是否发送完毕
//更新数据
	void updateSendTerminalData();		//更新发送到终端的数据
	void updateSendDriverData();			//更新发送到设备的数据

//接收并处理数据
	void disposeTerminalData();				//接收并处理终端设置反馈的数据
	void disposeArmsData();						//接收并处理机械臂设备反馈的数据
	void disposUnderpanData();				//接收并处理底盘设备的反馈的数据
	void disposCodedDiscData();				//接收并处理绝对编码盘反馈的数据

//支臂运行到指定角度
	void suppArmRunToPos(int,bool showError=true);
	
//云台运行到归位状态
	void panTiltRunToMMMModel();
	
//手抓运行到归位状态
	void fingerRunToNNNModel();
	
//单独获取支臂的角度差
	int16_t getSuppArmSubAngle(int);
	
//单独根据角度差和时间差设置支臂的速度，支臂比较特殊，运动方向的设定要根据临界角度
	void setSuppArmspeed(int,int,int);

//所有关节运行到指定角度，除前进相机和手抓抓持关节
	void allArmRunToPos(int,int,int,int,int,int,int,int);
	
//大臂旋转，大臂俯仰，小臂俯仰三个关节运行到指定位置
	void threeArmRunToPos(int,int,int,int);
//求时间差最大时间
	inline int maxTime(int32_t *);

	//停止所有的电机
	void stopAllMoter();

	//设置云台俯仰的速度
	static uint8_t setPanTiltPitchSpeed(int16_t);

	//设置手腕俯仰的速度
	static uint8_t setWristPitchSpeed(int16_t);

	//设置手抓夹持速度
	static uint8_t setFingerMediateSpeed(int16_t);

	//设置小臂俯仰速度
	static uint8_t setForearmPitchSpeed(int16_t);

	//设置大臂俯仰速度
	static uint8_t setBigArmPitchSpeed(int16_t);

	//设置大臂旋转速度
	static uint8_t setBigArmRotateSpeed(int16_t);

	//设置支臂旋转速度
	static uint8_t setSupportArmSpeed(int16_t);

	//解除机械臂收起后的角度锁定
	bool unlockArms(int16_t);

	bool unlockForZup();
	//计算电流
	uint8_t subEctQuantity(); 

	//Z 模式下运动 极坐标
	void runOnZZZLine(int16_t);

	//Y 模式下运动 极坐标
	void runOnYYYLine(int16_t);

	//X 模式下运动 极坐标
	void runOnXXXLine(int16_t);
	
	//平行于笛卡尔坐标的XYZ轴运动
	double runOnXYZLine(int8_t,double *,int16_t speed);		
	
	//镜像控制机械臂
	void controlArmISO();

	//xyz 笛卡尔坐标系
	void XbotArmSetXyzCtrlMode();
	
	//检测有无堵转错误
	bool checkBlockError();
	
};
#endif /* _XBOT_APP_H */









