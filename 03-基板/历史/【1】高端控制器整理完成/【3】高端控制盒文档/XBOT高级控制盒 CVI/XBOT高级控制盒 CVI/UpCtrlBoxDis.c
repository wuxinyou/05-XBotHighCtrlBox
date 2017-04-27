#include <rs232.h>
#include <cvirte.h>		
#include <userint.h>
#include "UpCtrlBoxDis.h"
#include "command.h"


typedef unsigned  char uint8_t;

static int ctdis;
void ComInit(void) ;
void OmapDataSetCtrlVal(void);    

int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                       LPSTR lpszCmdLine, int nCmdShow)
{
	if (InitCVIRTE (hInstance, 0, 0) == 0)
		return -1;	/* out of memory */
	if ((ctdis = LoadPanel (0, "UpCtrlBoxDis.uir", CTDIS)) < 0)
		return -1;
	DisplayPanel (ctdis);
	RunUserInterface ();
	DiscardPanel (ctdis);
	return 0;
}



int CVICALLBACK ComStartCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	static unsigned char ComNumVal;
	unsigned int ComBaudRate;
	int ComStartVal;
	char ComOpenError;
	unsigned char TempIndex;
	
	char ComNumString[10][5] = {"COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9"};
			
	GetCtrlVal (CTDIS, CTDIS_ComStart, 	&ComStartVal);
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			if(ComStartVal == 1)
			{
				GetCtrlVal (CTDIS, CTDIS_ComNum, 		&ComNumVal);
				GetCtrlVal (CTDIS, CTDIS_ComBaudRate, 	&ComBaudRate);  
				ComOpenError = OpenComConfig (ComNumVal, ComNumString[ComNumVal-1], ComBaudRate, 0, 8, 1, 512, 512);
		
				if( ComOpenError <0 )
				{
	
					DefaultCtrl (CTDIS, CTDIS_ComStart);  
					switch (ComOpenError)
					{
						case -1:					// Unknown system error.
							MessagePopup ("Com Error", "Unknown system error");
							break;
						case -2: 					//Invalid port number.
							MessagePopup ("Com Error", "Invalid port number");
							break;
						case -3: 					//Port is not open. 
							MessagePopup ("Com Error", "Port is not open");
							break;
						case -4:					//Unknown I/O error. 
							MessagePopup ("Com Error", "Unknown I/O error");
							break;
						case -5:				 	//Unexpected internal error. 
							MessagePopup ("Com Error", "Unexpected internal error");
							break;
						case -6: 					//No serial port found. 
							MessagePopup ("Com Error", "No serial port found");
							break;

					}
				}
				else
				{
					
//                    for(TempIndex=3;TempIndex<=55;TempIndex++ )
//						SetCtrlAttribute (MDr, TempIndex, ATTR_DIMMED, 0); 
//					
//					SetCtrlAttribute (MDr, MDr_ComNum, ATTR_DIMMED, 1);
//					SetCtrlAttribute (MDr, MDr_ComBaudRate, ATTR_DIMMED, 1);
					
					ComInit(); 
						




				}
			}
			else
			{
				CloseCom (ComNumVal);
				
/*				
				for(TempIndex=3;TempIndex<=55;TempIndex++ )
						SetCtrlAttribute (MDr, TempIndex, ATTR_DIMMED, 1); 
				
				SetCtrlAttribute (MDr, MDr_ComNum, 		ATTR_DIMMED, 0);
				SetCtrlAttribute (MDr, MDr_ComBaudRate, ATTR_DIMMED, 0);
				SetCtrlAttribute (MDr, MDr_ComStart, 	ATTR_DIMMED, 0);     
				SetCtrlAttribute (MDr, MDr_SystemReset, ATTR_DIMMED, 0);
*/				
				
		
			}
			
			break;
	}
	

			

	return 0;
}

int CVICALLBACK Tim1Callback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			break;
	}
	return 0;
}



//*******初始化发送与接收缓冲区,并构缓冲区环型链表



uint8_t OMAP_TXD_DATA[OMAP_TXD_DATA_LEN];
uint8_t OMAP_RXD_DATA[OMAP_RXD_DATA_LEN];
void ComCallback(int COMport, int eventMask, void *callbackdata) ;

void ComInit(void)
{
	
	unsigned char portNumberVal;
	int notifyCount = 0; /* Wait for at least 50 bytes in queue. */
	int eventChar = 0; /* Wait for LF. */
	int eventMask = LWRS_RXCHAR;
	
	GetCtrlVal(CTDIS, CTDIS_ComNum, 	&portNumberVal);
	

	InstallComCallback ( portNumberVal, eventMask, notifyCount,eventChar, (ComCallbackPtr)ComCallback, 0);
}



//接收中断函数,其可以自动把接收到的数据报存放在数据缓冲区
//******如果成功接收到一个帧，并把RXD_BUF->state的第0位置1，

void ComCallback(int COMport, int eventMask, void *callbackdata)
{   


	
	unsigned char InputQueueLength;
	unsigned char buffer[256];
	unsigned char ByteRead;
	unsigned char i;
	uint8_t TempData,TempCount;
	uint8_t CheckSum=0;
	

	static uint8_t DataIndex = 0;
	
	InputQueueLength =GetInQLen(COMport);
	ByteRead = ComRd(COMport,buffer,InputQueueLength);
	
	for(i=0;i<ByteRead;i++)
	{
		TempData = buffer[i];					//UART接收数据暂存

		if (DataIndex == 0X00)
		{
			if(OMAP_RXD_START != TempData)
			{
				DataIndex = 0;
			}
			else
			{
				OMAP_RXD_DATA[DataIndex] = TempData;
				DataIndex++;
			}
		}
		else if (DataIndex < OMAP_RXD_DATA_LEN-1)
		{
			OMAP_RXD_DATA[DataIndex] = TempData;
			DataIndex++;
		}
		else if (DataIndex == OMAP_RXD_DATA_LEN-1)
		{
			OMAP_RXD_DATA[DataIndex] = TempData;
			DataIndex++;

			/*******    求校验和       *******/
			CheckSum = 0;

			for(TempCount=0;TempCount<OMAP_RXD_DATA_LEN-1;TempCount++)
			{
				CheckSum += OMAP_RXD_DATA[TempCount];
			}

			/******* 如果校验和对，解析指令 *******/
//			if(OMAP_RXD_DATA[OMAP_RXD_DATA_LEN-1] == CheckSum )
			{
				/******* 成功解析新的一帧数据 *******/
				OmapDataSetCtrlVal();	
				
			}
			/******* 复位，重新开始新的一帧探测 *******/
			DataIndex = 0;
		}
		else
		{
			DataIndex = 0;
		}
		
	}
 	
}

void OmapDataSetCtrlVal(void)
{
	
//******************* KEY_A DIS****************************
	if(OMAP_RXD_DATA[2]&(1<<0))
		SetCtrlVal (CTDIS, CTDIS_A1, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_A1, 0);  	
	
	if(OMAP_RXD_DATA[2]&(1<<1))
		SetCtrlVal (CTDIS, CTDIS_A2, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_A2, 0);  
	
	if(OMAP_RXD_DATA[2]&(1<<2))
		SetCtrlVal (CTDIS, CTDIS_A3, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_A3, 0);  	
	
	if(OMAP_RXD_DATA[2]&(1<<3))
		SetCtrlVal (CTDIS, CTDIS_A4, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_A4, 0);  	
	
	if(OMAP_RXD_DATA[2]&(1<<4))
		SetCtrlVal (CTDIS, CTDIS_A5, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_A5, 0);  	
	
	if(OMAP_RXD_DATA[2]&(1<<5))
		SetCtrlVal (CTDIS, CTDIS_A6, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_A6, 0);  	
	
	if(OMAP_RXD_DATA[2]&(1<<6))
		SetCtrlVal (CTDIS, CTDIS_A7, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_A7, 0);  	
	
	if(OMAP_RXD_DATA[2]&(1<<7))
		SetCtrlVal (CTDIS, CTDIS_A8, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_A8, 0); 
	
//******************* KEY_B DIS****************************    
	if(OMAP_RXD_DATA[3]&(1<<0))
		SetCtrlVal (CTDIS, CTDIS_B1, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_B1, 0);  	
	
	if(OMAP_RXD_DATA[3]&(1<<1))
		SetCtrlVal (CTDIS, CTDIS_B2, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_B2, 0);  
	
	if(OMAP_RXD_DATA[3]&(1<<2))
		SetCtrlVal (CTDIS, CTDIS_B3, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_B3, 0);  	
	
	if(OMAP_RXD_DATA[3]&(1<<3))
		SetCtrlVal (CTDIS, CTDIS_B4, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_B4, 0);  	
	
	if(OMAP_RXD_DATA[3]&(1<<4))
		SetCtrlVal (CTDIS, CTDIS_B5, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_B5, 0);  	
	
	if(OMAP_RXD_DATA[3]&(1<<5))
		SetCtrlVal (CTDIS, CTDIS_B6, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_B6, 0);  	
	
	if(OMAP_RXD_DATA[3]&(1<<6))
		SetCtrlVal (CTDIS, CTDIS_B7, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_B7, 0);  	
	
	if(OMAP_RXD_DATA[3]&(1<<7))
		SetCtrlVal (CTDIS, CTDIS_B8, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_B8, 0); 
	
	
	
	//******************* KEY_H DIS****************************    
	if(OMAP_RXD_DATA[6]&(1<<0))
		SetCtrlVal (CTDIS, CTDIS_H1, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_H1, 0);  	
	
	if(OMAP_RXD_DATA[6]&(1<<1))
		SetCtrlVal (CTDIS, CTDIS_H2, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_H2, 0);  
	
	if(OMAP_RXD_DATA[6]&(1<<2))
		SetCtrlVal (CTDIS, CTDIS_H3, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_H3, 0);  	
	
	if(OMAP_RXD_DATA[6]&(1<<3))
		SetCtrlVal (CTDIS, CTDIS_H4, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_H4, 0);  	
	
	if(OMAP_RXD_DATA[6]&(1<<4))
		SetCtrlVal (CTDIS, CTDIS_H5, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_H5, 0);  	
	
	
		//******************* KEY_E DIS****************************    
	if(OMAP_RXD_DATA[4]&(1<<0))
		SetCtrlVal (CTDIS, CTDIS_EU, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_EU, 0);  	
	
	if(OMAP_RXD_DATA[4]&(1<<1))
		SetCtrlVal (CTDIS, CTDIS_ED, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_ED, 0);  
	
	if(OMAP_RXD_DATA[4]&(1<<2))
		SetCtrlVal (CTDIS, CTDIS_EL, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_EL, 0);  	
	
	if(OMAP_RXD_DATA[4]&(1<<3))
		SetCtrlVal (CTDIS, CTDIS_ER, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_ER, 0);  	
	
	if(OMAP_RXD_DATA[4]&(1<<4))
		SetCtrlVal (CTDIS, CTDIS_EM, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_EM, 0);  	
	

	
			//******************* KEY_F DIS****************************    
	if(OMAP_RXD_DATA[5]&(1<<0))
		SetCtrlVal (CTDIS, CTDIS_FU, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_FU, 0);  	
	
	if(OMAP_RXD_DATA[5]&(1<<1))
		SetCtrlVal (CTDIS, CTDIS_FD, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_FD, 0);  
	
	if(OMAP_RXD_DATA[5]&(1<<2))
		SetCtrlVal (CTDIS, CTDIS_FL, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_FL, 0);  	
	
	if(OMAP_RXD_DATA[5]&(1<<3))
		SetCtrlVal (CTDIS, CTDIS_FR, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_FR, 0);  	
	
	if(OMAP_RXD_DATA[5]&(1<<4))
		SetCtrlVal (CTDIS, CTDIS_FM, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_FM, 0); 
	
	
			//******************* KEY_I DIS****************************    
	if(OMAP_RXD_DATA[7]&(1<<0))
		SetCtrlVal (CTDIS, CTDIS_I1, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_I1, 0);  	
	
	if(OMAP_RXD_DATA[7]&(1<<1))
		SetCtrlVal (CTDIS, CTDIS_I2, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_I2, 0);  
				//******************* KEY_J DIS****************************  
	
	if(OMAP_RXD_DATA[7]&(1<<2))
		SetCtrlVal (CTDIS, CTDIS_J1, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_J1, 0);  	
	
	if(OMAP_RXD_DATA[7]&(1<<3))
		SetCtrlVal (CTDIS, CTDIS_J2, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_J2, 0);  
	
				//******************* KEY_M DIS****************************  
	
	if(OMAP_RXD_DATA[6]&(1<<5))
		SetCtrlVal (CTDIS, CTDIS_M2, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_M2, 0); 
	
	
	if(OMAP_RXD_DATA[6]&(1<<6))
		SetCtrlVal (CTDIS, CTDIS_M3, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_M3, 0); 
		
		
	if(OMAP_RXD_DATA[6]&(1<<7))
		SetCtrlVal (CTDIS, CTDIS_M4, 1); 
	else
		SetCtrlVal (CTDIS, CTDIS_M4, 0); 
	
	
	SetCtrlVal (CTDIS, CTDIS_JK_LeftX, 	OMAP_RXD_DATA[8]);  
	SetCtrlVal (CTDIS, CTDIS_JK_LeftY, 	OMAP_RXD_DATA[9]); 
	SetCtrlVal (CTDIS, CTDIS_JK_RightX, OMAP_RXD_DATA[10]); 
	SetCtrlVal (CTDIS, CTDIS_JK_RightY, OMAP_RXD_DATA[11]); 
	

	
	
	
	
	
	
		
}





	

