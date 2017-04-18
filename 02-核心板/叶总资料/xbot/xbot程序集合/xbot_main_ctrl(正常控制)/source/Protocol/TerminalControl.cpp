/**
  ******************************************************************************
	*文件：TerminalControl.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：Xbot和终端交互的协议类实现
	*备注：数据长度和超时参数用宏控制，超时参数建议在200以内，太大可能会导致机器人失去信号后不能很及时的停止
  ******************************************************************************  
	*/ 


/* 头文件包含 ------------------------------------------------------------------*/
#include "TerminalControl.h"

/* 类型定义 --------------------------------------------------------------------*/

/* 宏定义-----------------------------------------------------------------------*/ 
//数据帧长度宏
#define SEND_BUF_LEN 13
#define RECIVE_BUF_LEN 13

//帧头定义
#define FRAME_HEADER 0XA5

//超时参数
#define WIRELESS_TIME_TICK_MAX	500
#define WIRE_TIME_TICK_MAX	500

//构造函数
TerminalControl::TerminalControl(SerialPort * p1,SerialPort * p2)
{
	terminalWirePort=p1;
	terminalWireLessPort=p2;
	serialWorkMode=NOSIGNAL_WORK_MODE;
	reciveChin=new RingChain(RECIVE_BUF_LEN);
	sendBuf=new uint8_t[SEND_BUF_LEN];
	reciveBuf=new uint8_t[RECIVE_BUF_LEN];
	for(int i=0;i<SEND_BUF_LEN;i++)
	{
		sendBuf[i]=0;
	}
	for(int i=0;i<RECIVE_BUF_LEN;i++)
	{
		reciveBuf[i]=0;
	}	
}


//析构函数
TerminalControl::~TerminalControl()
{
	delete reciveChin;
	delete [] sendBuf;
	delete [] reciveBuf;
}

/**
  * 功  能：发送数据到控制终端
  * 参  数：无
  * 返回值：无
	* 备  注: 如果是有线并且无发送功能的光纤通信情况下应该关闭发送，避免干扰
  */
void TerminalControl::sendcommand()
{
	if(serialWorkMode==WIRE_WORK_MODE)
		terminalWirePort->write(sendBuf,SEND_BUF_LEN);
	else// if(serialWorkMode==WIRELESS_WORK_MODE)
		terminalWireLessPort->write(sendBuf,SEND_BUF_LEN);
}

/**
  * 功  能：接收控制终端的数据
  * 参  数：接收数据的串口
  * 返回值：
			true:成功接收一帧
			false:没有接收到一帧数据
  */
bool TerminalControl::reciveData(SerialPort *port)
{
	uint8_t checkSum=0;
	bool readFlag=false;
  //接收串行数据
	while (port->readAllow()&&(readFlag==false))
	{
		reciveChin->setData(port->getChar());
		reciveChin->next();
		if(reciveChin->getData()==FRAME_HEADER)//检测帧头	
		{	
			checkSum+=FRAME_HEADER;
			reciveChin->next();
			if((reciveChin->getData()&0X80)==0x00)//方向位正确
			{
				for(int i=0;i<RECIVE_BUF_LEN-2;i++)
				{
				   checkSum+=reciveChin->getData();
				   reciveChin->next();
				}
				if(checkSum==reciveChin->getData())//校验和正确
				{
					//将数据存入数组
					for(int i=0;i<RECIVE_BUF_LEN;i++)
					{
					   reciveChin->next();
					   reciveBuf[i]=reciveChin->getData();
					}
					readFlag=true;
				}
				reciveChin->next();
			}
			else
			{
				 reciveChin->previous();//跳至上个节点	
			}			
		 	checkSum=0;
		}	
	}
	return 	readFlag;
}

/**
  * 功  能：接收控制终端的数据并自动判断是有线还是无线
  * 参  数：无
  * 返回值：
			true:成功接收一帧
			false:没有接收到一帧数据
  */
bool TerminalControl::reciveData()
{
	bool tempFlag = false;
	static uint16_t wireRcTimeTick = 0;
	static uint16_t wirelessTimeTick = 0;
	//接收有线的数据

	tempFlag = reciveData(terminalWirePort);
	if(tempFlag == true)									//有线数据收到
	{
		wireRcTimeTick = 0;
		serialWorkMode =  WIRE_WORK_MODE;
	}
	else
	{
		if (wireRcTimeTick<WIRE_TIME_TICK_MAX)				//无有效数据帧计时，直到超过WIRE_TIME_TICK_MAX毫秒
		{
			wireRcTimeTick++;
		}
		else													//如果WIRE_TIME_TICK_MAX毫秒后，有线无信号，开始无线接收
		{
			//接收控制箱的数据
			tempFlag = reciveData(terminalWireLessPort);
			if(tempFlag == true)								// 无线数据收到
			{
				wirelessTimeTick = 0;
				serialWorkMode =  WIRELESS_WORK_MODE;
			}
			else if (wirelessTimeTick<WIRELESS_TIME_TICK_MAX)	//无有效数据帧计时，直到超过WIRELESS_TIME_TICK_MAX毫
			{
				wirelessTimeTick++;
			}
			else												//如果WIRELESS_TIME_TICK_MAX毫秒后，无线无信号
			{
				serialWorkMode = NOSIGNAL_WORK_MODE;
			}
		}
	}
	return tempFlag;
}

/**
  * 功  能：更新发送的数组
  * 参  数：更新的数据
  * 返回值：无
  */
void TerminalControl::updateSendBuf(uint8_t * temBuf)
{
	for(int i=0;i<SEND_BUF_LEN;i++)
		sendBuf[i]=temBuf[i];
}









