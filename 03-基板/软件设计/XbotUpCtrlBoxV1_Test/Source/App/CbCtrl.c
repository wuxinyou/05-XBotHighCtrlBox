


/*******************************************************Copyright*********************************************************

**
**-------------------------------------------------------文件信息---------------------------------------------------------
** 文件名称:			CbCtrl.c
** 最后修订日期:		2012-06-02
** 最后版本:			1.0
** 描述:				采集所有IO信息并发送给OMAP板
**
**------------------------------------------------------------------------------------------------------------------------
** 创建人:				吴琳
** 创建日期:			2012-06-02
** 版本:				1.0
** 描述:				20120601_XBOT510高端控制盒通讯协议
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
#include "CbCtrl.h"
#include "chain.h"

#define OMAP_DATA_INDEX_KEYA	   	2
#define OMAP_DATA_INDEX_KEYB	  	3
#define OMAP_DATA_INDEX_KEYE		4 		
#define OMAP_DATA_INDEX_KEYF	   	5
#define OMAP_DATA_INDEX_KEYH		6 		
#define OMAP_DATA_INDEX_KEYM	   	6
#define OMAP_DATA_INDEX_KEYHM	   	6
#define OMAP_DATA_INDEX_KEYI	   	7
#define OMAP_DATA_INDEX_KEYJ		7 
#define OMAP_DATA_INDEX_KEYG	   	7
#define OMAP_DATA_INDEX_KEYIJG		7 

#define OMAP_DATA_INDEX_JKADC_LX	8
#define OMAP_DATA_INDEX_JKADC_LY	9
#define OMAP_DATA_INDEX_JKADC_RX	10
#define OMAP_DATA_INDEX_JKADC_RY	11

#define OMAP_DATA_INDEX_BAT1_ADC	12
#define OMAP_DATA_INDEX_BAT2_ADC	13

#define OMAP_DATA_INDEX_COMCTRL		13



#define RXD_LEN 13
#define RXD_START 0xA5
#define RXD_ID_1 0x80
#define RXD_ID_2 0x81
#define RXD_ID_3 0x82
#define RXD_ID_4 0x83





uint8_t OMAP_TXD_DATA[OMAP_TXD_DATA_LEN];
uint8_t OMAP_RXD_DATA[OMAP_RXD_DATA_LEN];

uint8_t XBOT_TXD_DATA[XBOT_TXD_DATA_LEN];
uint8_t XBOT_RXD_DATA[XBOT_RXD_DATA_LEN];



static void KeyAToOmapData(void);
static void KeyBToOmapData(void);
static void KeyEToOmapData(void);
static void KeyFToOmapData(void);
static void KeyHMToOmapData(void);
static void KeyIJGToOmapData(void);
void OmapRxdDataSetXbotTxdData(uint8_t* pOmapRxdDa,uint8_t* pXbotTxdDa);
void XbotRxdDataSetOmapTxdData(uint8_t* pXbotRxdDa,uint8_t* pOmapTxdDa);
bool CbCtrlDealRcOmapData(USART_data_t* p_usart_data, uint8_t* pRXD_DATA);
bool CbCtrlDealRcXbotData(USART_data_t* p_usart_data, uint8_t* pRXD_DATA);
static void KeyToOmapData(void);
static void AdcToOmapData(void);

void CbCtrlInit(void)
{
//	read_xobot_data=creat_chain(13);	
}


/*******  工作在100ms的定时器内  *******/
void CbDealTxdCtrl(USART_data_t* p_usart_data,uint8_t* pTXD_DATA)
{
	uint8_t Index=0x00;

	pTXD_DATA[0]=OMAP_TXD_START;
	pTXD_DATA[1]= 0x30;
	KeyToOmapData();				//	OK
	AdcToOmapData();				//	OK

	pTXD_DATA[OMAP_TXD_DATA_LEN-1] = 0X00;

	for(Index=0;Index<OMAP_TXD_DATA_LEN-1;Index++)
		pTXD_DATA[OMAP_TXD_DATA_LEN-1] += pTXD_DATA[Index];

	for(Index=0;Index<OMAP_TXD_DATA_LEN;Index++)
		while (!USART_TXBuffer_PutByte(&USART_OMAP_CTRL,pTXD_DATA[Index]));
}

#define CB_CTRL_MODE_WIRE		0X00
#define CB_CTRL_MODE_WIRELESS	0X01
/*******  工作在1ms的定时器内  *******/
void CbDealRxdCtrl(void)
{
	static uint8_t CtrlModeFlag=!CB_CTRL_MODE_WIRE;
	uint8_t Index=0;
	//接收核心板数据，并处理
	if(true == CbCtrlDealRcOmapData(&USART_OMAP_CTRL,OMAP_RXD_DATA))
	{
	  	if((OMAP_RXD_DATA[OMAP_DATA_INDEX_COMCTRL]&0X80) == 0X80)
			CtrlModeFlag = CB_CTRL_MODE_WIRE;
		else
			CtrlModeFlag = CB_CTRL_MODE_WIRELESS;
			
		OmapRxdDataSetXbotTxdData(OMAP_RXD_DATA,XBOT_TXD_DATA);	
		
		if(CtrlModeFlag == CB_CTRL_MODE_WIRE)
		{
			//通过有线给机器人发送数据
			for(Index=0;Index<XBOT_TXD_DATA_LEN;Index++)
				while (!USART_TXBuffer_PutByte(&USRT_XBOT_WIRE_CTRL,XBOT_TXD_DATA[Index]));			
		}
		else
		{
			//通过无线发送给机器人数据
			for(Index=0;Index<XBOT_TXD_DATA_LEN;Index++)
				while (!USART_TXBuffer_PutByte(&USRT_XBOT_WIRELESS_CTRL,XBOT_TXD_DATA[Index]));	
		}	
	}
	//机器人控制方法为有线
	if(CtrlModeFlag == CB_CTRL_MODE_WIRE)
	{
		//接收机器人数据，并转发至核心板
		if(true == CbCtrlDealRcXbotData(&USRT_XBOT_WIRE_CTRL,XBOT_RXD_DATA))
		{
			//转发数据
			XbotRxdDataSetOmapTxdData(XBOT_RXD_DATA,OMAP_TXD_DATA);
			//将数据发送至核心板
			for(Index=0;Index<OMAP_TXD_DATA_LEN;Index++)
				while (!USART_TXBuffer_PutByte(&USART_OMAP_CTRL,OMAP_TXD_DATA[Index]));			
		}
	}
	//机器人控制方法为无线
	else
	{//接收机器人无线数据
		if(true == CbCtrlDealRcXbotData(&USRT_XBOT_WIRELESS_CTRL,XBOT_RXD_DATA))
		{//转发数据至核心板
			XbotRxdDataSetOmapTxdData(XBOT_RXD_DATA,OMAP_TXD_DATA);
			//发送
			for(Index=0;Index<OMAP_TXD_DATA_LEN;Index++)
				while (!USART_TXBuffer_PutByte(&USART_OMAP_CTRL,OMAP_TXD_DATA[Index]));			
		}
	}
}


void OmapRxdDataSetCbOtherCtrl(uint8_t* pOmapRxdDa)
{
	if(pOmapRxdDa[OMAP_DATA_INDEX_COMCTRL]&(1<<6) == 0)
		CB_MOTOR_WORK_STOP;
	else
		CB_MOTOR_WORK_START;

	if(pOmapRxdDa[OMAP_DATA_INDEX_COMCTRL]&(1<<5) == 0)
		CB_GLED1_OFF;
	else
		CB_GLED1_ON;

	if(pOmapRxdDa[OMAP_DATA_INDEX_COMCTRL]&(1<<4) == 0)
		CB_GLED2_OFF;
	else
		CB_GLED2_ON;
}

//数据转存
void OmapRxdDataSetXbotTxdData(uint8_t* pOmapRxdDa,uint8_t* pXbotTxdDa)
{
	uint8_t Index=0,CheckSum=0;
	
	pXbotTxdDa[0] = XBOT_TXD_START;

	for(Index=1;Index<XBOT_TXD_DATA_LEN-1;Index++)
	   pXbotTxdDa[Index] = pOmapRxdDa[Index+1];

	for(Index=0;Index<XBOT_TXD_DATA_LEN-1;Index++)
		CheckSum += pXbotTxdDa[Index];
	
	pXbotTxdDa[XBOT_TXD_DATA_LEN-1] = CheckSum; 
}

//数据转存
void XbotRxdDataSetOmapTxdData(uint8_t* pXbotRxdDa,uint8_t* pOmapTxdDa)	 
{
	uint8_t Index=0,CheckSum=0;
	
	pOmapTxdDa[0] = OMAP_TXD_START;
	pOmapTxdDa[1] = CB_COM_XBOT_CTRL;
	pOmapTxdDa[OMAP_TXD_DATA_LEN-2] = OMAP_NC_DATA;

	for(Index=1;Index<XBOT_RXD_DATA_LEN-1;Index++)
	   pOmapTxdDa[Index+1] = pXbotRxdDa[Index];

	for(Index=0;Index<OMAP_TXD_DATA_LEN-1;Index++)
		CheckSum += pOmapTxdDa[Index];
			
	pOmapTxdDa[OMAP_TXD_DATA_LEN-1] = CheckSum; 
}

/*******  工作在1ms的定时器内  *******/
//接收核心板的数据
bool CbCtrlDealRcOmapData(USART_data_t* p_usart_data, uint8_t* pRXD_DATA)
{
	uint8_t TempData,TempCount;
	uint8_t CheckSum=0;
	bool RxdFlag=false;

	static uint8_t DataIndex = 0;

	while (USART_RXBufferData_Available(p_usart_data))
	{
		TempData = USART_RXBuffer_GetByte(p_usart_data);

		if (DataIndex == 0X00)
		{
			if(OMAP_RXD_START != TempData)
			{
				DataIndex = 0;
			}
			else
			{
				pRXD_DATA[DataIndex] = TempData;
				DataIndex++;
			}
		}
		else if (DataIndex < OMAP_RXD_DATA_LEN-1)
		{
			pRXD_DATA[DataIndex] = TempData;
			DataIndex++;
		}
		else if (DataIndex == OMAP_RXD_DATA_LEN-1)
		{
			pRXD_DATA[DataIndex] = TempData;
			DataIndex++;

			/*******    求校验和       *******/
			CheckSum = 0;

			for(TempCount=0;TempCount<OMAP_RXD_DATA_LEN-1;TempCount++)
			{
				CheckSum += pRXD_DATA[TempCount];
			}

			/******* 如果校验和对，解析指令 *******/
			if(pRXD_DATA[OMAP_RXD_DATA_LEN-1] == CheckSum )
			{
				/******* 成功解析新的一帧数据 *******/
				RxdFlag=true;
			}
			/******* 复位，重新开始新的一帧探测 *******/
			DataIndex = 0;
		}
		else
		{
			DataIndex = 0;
		}
	}
	return RxdFlag;

}








/*******  工作在1ms的定时器内  *******/
bool CbCtrlDealRcXbotData(USART_data_t* p_usart_data, uint8_t* pRXD_DATA)
{
	uint8_t TempData,TempCount;
	uint8_t CheckSum=0;
	bool RxdFlag=false;

	static uint8_t DataIndex = 0;

	while (USART_RXBufferData_Available(p_usart_data))
	{
		TempData = USART_RXBuffer_GetByte(p_usart_data);

		if (DataIndex == 0X00)
		{
			if(XBOT_RXD_START != TempData)
			{
				DataIndex = 0;
			}
			else
			{
				pRXD_DATA[DataIndex] = TempData;
				DataIndex++;
			}
		}
		else if (DataIndex < XBOT_RXD_DATA_LEN-1)
		{
			pRXD_DATA[DataIndex] = TempData;
			DataIndex++;
		}
		else if (DataIndex == XBOT_RXD_DATA_LEN-1)
		{
			pRXD_DATA[DataIndex] = TempData;
			DataIndex++;

			/*******    求校验和       *******/
			CheckSum = 0;

			for(TempCount=0;TempCount<XBOT_RXD_DATA_LEN-1;TempCount++)
			{
				CheckSum += pRXD_DATA[TempCount];
			}

			/******* 如果校验和对，解析指令 *******/
			if(pRXD_DATA[XBOT_RXD_DATA_LEN-1] == CheckSum )
			{
				/******* 成功解析新的一帧数据 *******/
				RxdFlag=true;
			}
			/******* 复位，重新开始新的一帧探测 *******/
			DataIndex = 0;
		}
		else
		{
			DataIndex = 0;
		}
	}
	return RxdFlag;

}

static void KeyToOmapData(void)
{
	KeyAToOmapData();
	KeyBToOmapData();
	KeyEToOmapData();
	KeyFToOmapData();
	KeyHMToOmapData();
	KeyIJGToOmapData();
	
}

static void AdcToOmapData(void)
{
	OMAP_TXD_DATA[OMAP_DATA_INDEX_JKADC_LX] = (uint8_t)JK_GetValue_LX();
	OMAP_TXD_DATA[OMAP_DATA_INDEX_JKADC_LY] = (uint8_t)JK_GetValue_LY();
	OMAP_TXD_DATA[OMAP_DATA_INDEX_JKADC_RX] = (uint8_t)JK_GetValue_RX();
	OMAP_TXD_DATA[OMAP_DATA_INDEX_JKADC_RY] = (uint8_t)JK_GetValue_RY();
	
	OMAP_TXD_DATA[OMAP_DATA_INDEX_BAT1_ADC] = BAT1_GetValue();
	OMAP_TXD_DATA[OMAP_DATA_INDEX_BAT2_ADC] = BAT2_GetValue();		
		
}

static void KeyAToOmapData(void)
{
	OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYA]=0X00;
	if(KEY_DATA[KEY_A1].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYA] |= (1<<0); 
			
	if(KEY_DATA[KEY_A2].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYA] |= (1<<1); 
			
	if(KEY_DATA[KEY_A3].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYA] |= (1<<2); 
			
	if(KEY_DATA[KEY_A4].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYA] |= (1<<3);
		 	
	if(KEY_DATA[KEY_A5].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYA] |= (1<<4); 
			
	if(KEY_DATA[KEY_A6].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYA] |= (1<<5); 
			
	if(KEY_DATA[KEY_A7].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYA] |= (1<<6); 
			
	if(KEY_DATA[KEY_A8].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYA] |= (1<<7); 	

}

static void KeyBToOmapData(void)
{
	OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYB]=0X00;
	if(KEY_DATA[KEY_B1].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYB] |= (1<<0); 
			
	if(KEY_DATA[KEY_B2].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYB] |= (1<<1); 
			
	if(KEY_DATA[KEY_B3].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYB] |= (1<<2); 
			
	if(KEY_DATA[KEY_B4].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYB] |= (1<<3);
		 	
	if(KEY_DATA[KEY_B5].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYB] |= (1<<4); 
			
	if(KEY_DATA[KEY_B6].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYB] |= (1<<5); 
			
	if(KEY_DATA[KEY_B7].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYB] |= (1<<6); 
			
	if(KEY_DATA[KEY_B8].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYB] |= (1<<7); 	

}

static void KeyEToOmapData(void)
{
	OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYE]=0X00;
	if(KEY_DATA[KEY_EU].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYE] |= (1<<0); 
			
	if(KEY_DATA[KEY_ED].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYE] |= (1<<1); 
			
	if(KEY_DATA[KEY_EL].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYE] |= (1<<2); 
			
	if(KEY_DATA[KEY_ER].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYE] |= (1<<3);
		 	
	if(KEY_DATA[KEY_EM].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYE] |= (1<<4); 
}

static void KeyFToOmapData(void)
{
	OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYF]=0X00;
	if(KEY_DATA[KEY_FU].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYF] |= (1<<0); 
			
	if(KEY_DATA[KEY_FD].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYF] |= (1<<1); 
			
	if(KEY_DATA[KEY_FL].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYF] |= (1<<2); 
			
	if(KEY_DATA[KEY_FR].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYF] |= (1<<3);
		 	
	if(KEY_DATA[KEY_FM].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYF] |= (1<<4); 
}

static void KeyHMToOmapData(void)
{
	OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYHM]=0X00;
	if(KEY_DATA[KEY_H1].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYH] |= (1<<0); 
			
	if(KEY_DATA[KEY_H2].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYH] |= (1<<1); 
			
	if(KEY_DATA[KEY_H3].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYH] |= (1<<2); 
			
	if(KEY_DATA[KEY_H4].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYH] |= (1<<3);
		 	
	if(KEY_DATA[KEY_H5].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYH] |= (1<<4); 
			
	if(KEY_DATA[KEY_M2].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYM] |= (1<<5); 
			
	if(KEY_DATA[KEY_M3].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYM] |= (1<<6); 
			
	if(KEY_DATA[KEY_M4].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYM] |= (1<<7); 	

}

static void KeyIJGToOmapData(void)
{
	OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYIJG]=0X00;
	if(KEY_DATA[KEY_I1].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYI] |= (1<<0); 
			
	if(KEY_DATA[KEY_I2].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYI] |= (1<<1); 
			
	if(KEY_DATA[KEY_J1].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYJ] |= (1<<2); 
			
	if(KEY_DATA[KEY_J2].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYJ] |= (1<<3);
		 	
	if(KEY_DATA[KEY_G1].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYG] |= (1<<4); 
			
	if(KEY_DATA[KEY_G2].NowState == KEY_PRESS_DOWN)
		OMAP_TXD_DATA[OMAP_DATA_INDEX_KEYG] |= (1<<5); 

}


 //一个通用的利用环形链表结构接受串口数据的函数
 //
bool receiveData(USART_data_t* p_usart_data, uint8_t* pRXD_DATA)
{
	static uint8_t flag=0;
		
	static chain *readData;	
	
	uint8_t CheckSum=0;

	bool RxdFlag=false;

	uint8_t Index=0;
	
 	if(flag==0)
	{
	   readData=creatChain(RXD_LEN);
	   flag=1;
	}

	while (USART_RXBufferData_Available(p_usart_data))
	{
		readData->data = USART_RXBuffer_GetByte(p_usart_data);

		readData = readData->next;//链表跳至下个节点

		if(readData->data==RXD_START)//检测帧头
		{			
			readData=readData->next;
			CheckSum+=RXD_LEN;
			if(readData->data==RXD_ID_1||readData->data==RXD_ID_2||readData->data==RXD_ID_3||readData->data==RXD_ID_4)//检测命令字
			{
				//命令字正确
				for(Index=0;Index<RXD_LEN-2;Index++)
				{
				   CheckSum+= readData->data;
				   readData=readData->next;
				}
				if(CheckSum==readData->data)//校验和正确
				{
					//将数据存入数组
					for(Index=0;Index<RXD_LEN;Index++)
					{
					   readData = readData->next;
					   pRXD_DATA[Index]=readData->data;
					}
					RxdFlag=true;	
				}
				readData=readData->next; 	
			}
			else
			{
				readData=readData->last;//跳至上个节点	
			}			
		 	CheckSum=0;
		}
	}
	return 	RxdFlag;
}				    

