
/*******************************************************Copyright*********************************************************
**                                            北京博创兴盛机器人技术有限公司
**                                                       研发部
**                                               http://www.uptech-eod.com
**
**-------------------------------------------------------文件信息---------------------------------------------------------
** 文件名称:			CbIoCtrl.h
** 最后修订日期:		2010-05-01
** 最后版本:			1.0
** 描述:				应用于排爆机器人
**
**------------------------------------------------------------------------------------------------------------------------
** 创建人:			吴琳
** 创建日期:			2009-04-01
** 版本:				1.0
** 描述:				应用于排爆机器人；
**
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
*************************************************************************************************************************/


#ifndef CBIOCTRL_H_
#define CBIOCTRL_H_

#include "avr_compiler.h"
#include "ConfigTypes.h"

#include "Apps/UsartInit.h"



#include "Apps/SystemInit.h"

#include "Drivers/port_driver.h"
#include "Apps/AdcControl.h"
#include "Protocol/CbDisCtrl.h"
#include "Protocol/CbCtrlData.h"

#define		RAPTOR_CBIOCTRL_GLOBALS

#ifndef   RAPTOR_CBIOCTRL_GLOBALS
     #define RAPTOR_CBIOCTRL_EXT
#else
     #define RAPTOR_CBIOCTRL_EXT  extern
#endif


#define CBIOCTRL_TXD_EN		PORTD.OUTSET  = PIN1_bm
#define CBIOCTRL_TXD_DIS	PORTD.OUTCLR  = PIN1_bm












typedef struct S_CbCtrl
{
	uint8 CtrlState;

	void (*p_InitDev) (void);
	void (*p_DealCtrl) (void);

	uint8_t (*pRxdPacket)(USART_data_t* p_usart_data, CB_CTRL_DATA_STRUCT* p_Rp_receive);
	uint8_t (*pTxdToRpCtrl)(USART_data_t* p_usart_data, CB_CTRL_DATA_STRUCT* p_Rp_send);

	uint8_t (*pTxdToRpFire)(USART_data_t* p_usart_data, CB_CTRL_DATA_STRUCT* p_Rp_send);

	void (*pDearRcData)(USART_data_t* p_usart_data, CB_CTRL_DATA_STRUCT* p_Xbot_receive);



}CB_CTRL_STRUCT;

RAPTOR_CBIOCTRL_EXT CB_CTRL_STRUCT CbCtrl;




#endif /* CBIOCTRL_H_ */



/******************************所有控制接口定义**************************/

/*************** IO 输入接口**************/
/****************************************
PC0  	IN_Aim   		瞄准控制
PC1		IN_Aim_Lock		开火钥匙
PC4		IN_Fire			开火控制
PC5		IN_COM_SW		有线无线切换检测

PD0		OUT_COM_CTRL	有线无线切换控制
PD5		IN_CAM0			图像通道编码输入0
PD6		IN_CAM1			图像通道编码输入1
PD7		IN_CAM2			图像通道编码输入2

PE0		OUT_CAM0		图像通道LED编码控制0
PE1		OUT_CAM1		图像通道LED编码控制1
PE2		OUT_CAM2		图像通道LED编码控制2
PE3		IN_HD_LIGHT		云台灯光控制
PE4		IN_MV_LIGHT		行使灯光控制
PE5		IN_HANDA		手爪抓持
PE6		IN_HANDB		手爪松开
PE7		IN_HAND_AUTO	手爪自动

PF0		IN_JOINT1_A		底座左转
PF1		IN_JOINT1_B		底座右转
PF2		IN_JOINT2_A		大臂下俯
PF3		IN_JOINT2_B		大臂上仰
PF4		IN_JOINT3_A		小臂上仰
PF5		IN_JOINT3_B		小臂下俯
PF6		IN_JOINT4_A		手爪右转
PF7		IN_JOINT4_B		手爪左转

**********	ADC-A	通道 	**********
ADC0	ARM_SPEED		机械臂运动速度
ADC1	HAND_FORCE		手爪抓持力度
ADC2	REVERVATION		保留
ADC3	Voltage			系统工作电压
ADC4	HEADX			云台旋转控制
ADC5	HEADY			云台俯仰控制
ADC6	HEAD_FOCUS		云台变焦控制
ADC7	MOVE_X			运动左右控制


**********	ADC-B	通道 	**********
ADC0	MOVE_Y			运动前后控制
ADC1	MOVE_Z			保留
ADC2	MOVE_SPEED		运动速度控制


********************************************/






