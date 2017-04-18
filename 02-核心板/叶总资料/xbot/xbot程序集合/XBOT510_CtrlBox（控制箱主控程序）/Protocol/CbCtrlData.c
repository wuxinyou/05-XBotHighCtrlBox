/*
 * CbCtrlData.c
 *
 *  Created on: 2011-6-21
 *      Author: wulin
 */

#include "Protocol/CbCtrlData.h"


CB_CTRL_DATA_STRUCT CbCtrlData =
{
		.RobotSelfPowerVal = 0X00,
		.TestMode = TEST_NC,
		.FireState= 0X00,


//				uint8_t TxdDataBuf[CB_TXD_LEN];
//				uint8_t RxdDataBuf[CB_RXD_LEN];
//
//				uint8_t TxdCheckSum;
//				uint8_t RxdCheckSum;
//
//				uint8_t DevID;					//设备端口号
//
//				uint8_t LeftMoveCtrl;			//左电机控制
//				uint8_t RightMoveCtrl;			//右电机控制
//				uint8_t LeftMoveSpeed;			//左电机速度
//				uint8_t RightMoveSpeed;			//右电机速度
//
//				uint8_t Arm12Ctrl;				//机械臂12关节控制
//				uint8_t Arm34Ctrl;				//机械臂34关节控制
//				uint8_t Arm50Ctrl;				//机械臂50关节控制
//				uint8_t Arm78Ctrl;				//机械臂78关节控制
//				uint8_t Arm6Ctrl;				//机械臂6关节控制
//
//				uint8_t ExCtrl;					//其它控制信号
//				uint8_t SwCtrl;					//开关量控制信号
//				uint8_t CamZoomCtrl;			//图像及焦距设置
//
//
//				uint8_t Arm12356Speed;			//机械臂12356速度控制
//
//
//				uint8_t ComSwState;				//有线无线控制
//
//				uint8_t FireState;				//武器状态
//
//				uint8_t Arm0Angle;				//摆腿旋转
//				uint8_t Arm1Angle;				//底盘旋转
//				uint8_t Arm2Angle;				//大臂俯仰
//				uint8_t Arm3Angle;				//小臂俯仰
//				uint8_t Arm4Angle;				//腕关节俯仰
//				uint8_t Arm5Angle;				//手爪旋转
//				uint8_t Arm6Angle;				//云台俯仰
//				uint8_t Arm7Angle;				//云台旋转
//
//				uint8_t HandWidth;				//手爪抓持
//				uint8_t CamPtAngle;				//前视摄像头俯仰
//
//				uint8_t Arm0ModeTime;			//摆腿运动时间
//				uint8_t Arm18ModeTime;			//机械臂运动时间
//
//				uint8_t CtrlBoxPowerVal;		//控制箱电压
//				uint8_t RobotSelfPowerVal;		//机器本体电压
//
//				uint8_t Arm0WorkMode;			//摆腿工作模式
//				uint8_t Arm18WorkMode;			//机械臂工作模式
//				uint8_t YtWorkMode;				//云台工作模式
//
		.KeyVal=0,					//小液晶屏的按键状态
		.SendToXbotCounter=0,		//发送到机器人数据帧计数器
		.ReceiveFormXbotCounter=0,	//接收自机器人数据帧计数器
		.SendToDisCounter=0,		//发送到液晶屏数据帧计数器
		.ReceiveFormDisCounter=0,	//接收自液晶屏数据帧计数器
		.signal=0
};





















