

/*******************************************************Copyright*********************************************************
**                                            北京博创兴盛机器人技术有限公司
**                                                       研发部
**                                               http://www.uptech-eod.com
**
**-------------------------------------------------------文件信息---------------------------------------------------------
** 文件名称:			CbDisCtrl.h
** 最后修订日期:		2011-06-21
** 最后版本:			1.0
** 描述:				应用于排爆机器人
**
**------------------------------------------------------------------------------------------------------------------------
** 创建人:			吴琳
** 创建日期:			2011-06-21
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


#ifndef CBDISCTRL_H_
#define CBDISCTRL_H_

#include "avr_compiler.h"
#include "ConfigTypes.h"

#include "Apps/UsartInit.h"



#include "Apps/SystemInit.h"

#include "Drivers/port_driver.h"
#include "Apps/AdcControl.h"
#include "Protocol/CbCtrlData.h"

#define		XBOT_CBDISCTRL_GLOBALS

#ifndef   XBOT_CBDISCTRL_GLOBALS
     #define XBOT_CBDISCTRL_EXT
#else
     #define XBOT_CBDISCTRL_EXT  extern
#endif


/*************************************************************************************************************************
**                                                    协议相关控制字
*************************************************************************************************************************/


#define CBDIS_TXD_START 			0xA5
#define CBDIS_RXD_START 			0xA5




#define CBDIS_TXD_LEN				13			// 通讯数据发送长度
#define CBDIS_RXD_LEN				13			// 通讯数据接收长度


#define CBDIS_NEW_FRAME				0X01
#define CBDIS_NONE_FRAME			0X00

#define CBDIS_NC_DATA 				0xCC








/*************************************************************************************************************************
**                                                     结构体定义
*************************************************************************************************************************/
typedef struct S_CbDisCtrlData
{
	uint8_t TxdDataBuf[CBDIS_TXD_LEN];
	uint8_t RxdDataBuf[CBDIS_RXD_LEN];

	uint8_t TxdCheckSum;
	uint8_t RxdCheckSum;
	uint8_t CheckSum;


}CBDIS_CTRL_DATA_STRUCT;							// Raptor从控制箱接收到的控制信息





typedef struct S_CbDisCtrl
{
	void (*pSendDisCtrl)(USART_data_t * usart_data,CB_CTRL_DATA_STRUCT* pDa);
	void (*pDealRcData)(USART_data_t * p_usart_data,CBDIS_CTRL_DATA_STRUCT* pDa);



}CBDIS_CTRL_STRUCT;

XBOT_CBDISCTRL_EXT CBDIS_CTRL_STRUCT CbDisCtrl;
XBOT_CBDISCTRL_EXT CBDIS_CTRL_DATA_STRUCT CbDisCtrlData;



#endif /* CBDISCTRL_H */








