/*
 * CbDisCtrl.c
 *
 *  Created on: 2011-6-21
 *      Author: wulin
 */




/*******************************************************Copyright*********************************************************
**                                            北京博创兴盛机器人技术有限公司
**                                                       研发部
**                                               http://www.uptech-eod.com
**
**-------------------------------------------------------文件信息---------------------------------------------------------
** 文件名称:			CbDisCtrl.c
** 最后修订日期:		2011-06-21
** 最后版本:			1.0
** 描述:				用于有线与无线控制的协议解析。
**
**------------------------------------------------------------------------------------------------------------------------
** 创建人:			吴琳
** 创建日期:			2011-06-21
** 版本:				1.0
** 描述:				解析来自于控制箱的协议，同时反馈相当的控制信息。
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

#include "Protocol/CbDisCtrl.h"

inline static int8_t CbDisGetSpeed(uint8_t Dir,uint8_t Speed)
{
	int16_t TempSpeed;
	/**************设置电机速*******************/
	if(Dir==0x01)
	{
		TempSpeed = Speed;
		TempSpeed /= 2;
	}
	else if(Dir==0x02)
	{
		TempSpeed = 0-Speed;
		TempSpeed /= 2;
	}
	else
	{
		TempSpeed = 0;
	}
	return TempSpeed;

}
static void XbotCbSendDisCtrl(USART_data_t * usart_data,CB_CTRL_DATA_STRUCT* pDa)
{
	uint8_t SendData[CBDIS_TXD_LEN];
	static uint8_t SendIndex=0x00;
	static uint8_t Index=0x00;

	SendIndex++;
	SendIndex = SendIndex&0x03;

	SendData[0] = CBDIS_TXD_START;					//设置帧头
	SendData[1] = SendIndex;						//设置数据方向、命令字、回传序号

	SendData[2] = CbDisGetSpeed(pDa->LeftMoveCtrl,pDa->LeftMoveSpeed);  	//回传控制速度
	SendData[3] = CbDisGetSpeed(pDa->RightMoveCtrl,pDa->RightMoveSpeed);	//回传控制速度
	if(SendIndex==0x00)
	{
		SendData[4] =pDa->Arm1Angle;
		SendData[5] =pDa->Arm5Angle;
		SendData[6] =pDa->HandWidth;
		SendData[7] =  pDa->Battery_1;;				//电池1电压
		SendData[8] =  pDa->Error_1;				//警告
		SendData[9] =  pDa->Error_2;				//警告
		SendData[10] = pDa->Wirelength;	 			//线长
	}
	else if(SendIndex==0x01)
	{
		SendData[4] =pDa->Arm2Angle;
		SendData[5] =pDa->Arm6Angle;
		SendData[6] = pDa->Arm0Angle;;
		SendData[7] =  pDa->Battery_2;;				//电池2电压
		SendData[8] =  pDa->Error_3;				//警告
		SendData[9] =  pDa->Error_4;				//警告
		SendData[10] = pDa->signal;	 				//信号强度
	}
	else if(SendIndex==0x02)
	{
		SendData[4] =pDa->Arm3Angle;
		SendData[5] =pDa->Arm7Angle;
		SendData[6] =  pDa->CtrlBoxPowerVal/2;		//控制箱电压
//		SendData[6] = (uint8_t)(adc_a_control.ad1&0x00ff);					//回传真实的速度
		SendData[7] =  pDa->Battery_3; 				//电池3电压
		SendData[8] =  pDa->Error_5;				//警告
		SendData[9] =  pDa->Error_6;				//警告
		SendData[10] = pDa->LeftSpeed;				//回传真实的速度

//		SendData[10]	= (uint8_t)(adc_a_control.ad1>>8);					//回传真实的速度
	}
	else if(SendIndex==0x03)
	{
		SendData[4] =pDa->Arm4Angle;
		SendData[5] =pDa->CamPtAngle;
		SendData[6] =pDa->RobotSelfPowerVal;		//本体电压
//		SendData[6]	= (uint8_t)(adc_a_control.ad1>>8);					//回传真实的速度
		SendData[7] =  pDa->Battery_4;; 			//电池4电压
		SendData[8] =  pDa->Error_7;				//警告
		SendData[9] =  pDa->Error_8;				//警告
		SendData[10] = pDa->RightSpeed;					//回传真实的速度
//		SendData[10] = (uint8_t)(adc_a_control.ad1&0x00ff);					//回传真实的速度
	}
	SendData[11] = pDa->FireState;					//开火状态

	SendData[CBDIS_TXD_LEN-1] = 0x00;
	for(Index=0;Index<CBDIS_TXD_LEN-1;Index++)
		SendData[CBDIS_TXD_LEN-1] += SendData[Index];


	for(Index=0;Index<CBDIS_TXD_LEN;Index++)
		while (!USART_TXBuffer_PutByte(usart_data,SendData[Index]));
}

inline static void CbDisSetCtrlData(CBDIS_CTRL_DATA_STRUCT* pDa,CB_CTRL_DATA_STRUCT* pCtrlData)
{
	if((pDa->RxdDataBuf[1]&0x80) != 0x00)
		return;

	if(((pDa->RxdDataBuf[1]>>4)&0x0F) == 0x00)
	{
		pCtrlData->Arm0WorkMode 	= (pDa->RxdDataBuf[2]>>5)&0X07;			//摆腿工作模式
		pCtrlData->Arm18WorkMode 	= (pDa->RxdDataBuf[2]>>2)&0X07;;		//机械臂工作模式
		pCtrlData->YtWorkMode 		= (pDa->RxdDataBuf[2]>>0)&0X03;;		//云台工作模式

	}

	if(pDa->RxdDataBuf[3] == 0x8A)
		pCtrlData->TestMode = TEST_NO_LIMIT;
	else if(pDa->RxdDataBuf[3] == 0x8B)
		pCtrlData->TestMode = TEST_SET_ZERO;
	else if(pDa->RxdDataBuf[3] == 0xA8)
		pCtrlData->TestMode = TEST_FIRE;
	else if(pDa->RxdDataBuf[3] == 0xB8)
		pCtrlData->TestMode = TEST_GUN;
	pCtrlData->KeyVal=pDa->RxdDataBuf[4];									//小液晶屏的按键值
	CbCtrlData.ReceiveFormDisCounter++;
}

static void XbotCbDealRxDisCtrl(USART_data_t * p_usart_data,CBDIS_CTRL_DATA_STRUCT* pDa)
{
	uint8_t TempData,TempCount;

	static uint8_t DataIndex = 0;

	while (USART_RXBufferData_Available(p_usart_data))
	{
		TempData = USART_RXBuffer_GetByte(p_usart_data);

		if (DataIndex == 0X00)
		{
			if(CBDIS_RXD_START != TempData)
			{
				DataIndex = 0;
			}
			else
			{
				pDa->RxdDataBuf[DataIndex] = TempData;
				DataIndex++;
			}
		}
		else if (DataIndex < CBDIS_RXD_LEN-1)
		{
			pDa->RxdDataBuf[DataIndex] = TempData;
			DataIndex++;
		}
		else if (DataIndex == CBDIS_RXD_LEN-1)
		{
			pDa->RxdDataBuf[DataIndex] = TempData;
			DataIndex++;

			/*******    求校验和       *******/
			pDa->CheckSum = 0;

			for(TempCount=0;TempCount<CBDIS_RXD_LEN-1;TempCount++)
			{
				pDa->CheckSum += pDa->RxdDataBuf[TempCount];
			}

			/******* 如果校验和对，解析指令 *******/
			if(pDa->RxdDataBuf[CBDIS_RXD_LEN-1] == pDa->CheckSum )
			{

				/******* 成功解析新的一帧数据 *******/
				CbDisSetCtrlData(pDa,&CbCtrlData);

			}

			/******* 复位，重新开始新的一帧探测 *******/
			DataIndex = 0;
		}
		else
		{
			DataIndex = 0;
		}
	}

	/***  没有成功解析新的一帧数据 ****/

}

CBDIS_CTRL_STRUCT CbDisCtrl =
{
		.pSendDisCtrl = XbotCbSendDisCtrl,
		.pDealRcData  = XbotCbDealRxDisCtrl,
};
CBDIS_CTRL_DATA_STRUCT CbDisCtrlData =
{


};














