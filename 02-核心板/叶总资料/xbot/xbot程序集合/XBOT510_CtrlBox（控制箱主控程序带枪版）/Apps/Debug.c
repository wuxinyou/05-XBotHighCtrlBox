/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief  XMEGA USART interrupt driven driver example source.
 *
 *      This file contains an example application that demonstrates the
 *      interrupt driven USART driver. The code example sends three bytes, waits
 *      for three bytes to be received and tests if the received data equals the
 *      sent data.
 *
 * \par Application note:
 *      AVR1307: Using the XMEGA USART
 *
 * \par Documentation
 *      For comprehensive code documentation, supported compilers, compiler
 *      settings and supported devices see readme.html
 *
 * \author
 *      Atmel Corporation: http://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 * $Revision: 1694 $
 * $Date: 2008-07-29 14:21:58 +0200 (ti, 29 jul 2008) $  \n
 *
 * Copyright (c) 2008, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#define FALSE 	0x00
#define TRUE 	0x01


#include "avr_compiler.h"

#include "Apps/SystemInit.h"

#include "Drivers/port_driver.h"

#include "Protocol/CbCtrl.h"
#include "Protocol/CbDisCtrl.h"



void DealRcRecData(void);
void DealArmRecData(void);


void TestIC(void);

int main(void)
{

	CbCtrl.p_InitDev();



//	PC0  	IN_Aim   		瞄准控制
//	PC1		IN_Aim_Lock		开火钥匙
//	PC4		IN_Fire			开火控制

//	PORTC.DIRSET  = PIN1_bm|PIN4_bm;
//	_delay_ms(1000);
//	PORTC.OUTCLR  = PIN1_bm|PIN4_bm;
//	_delay_ms(1000);
//	PORTC.OUTSET  = PIN1_bm|PIN4_bm;

	//

	while(1)
	{

//		CBIOCTRL_TXD_EN;
//		while (!USART_TXBuffer_PutByte(&USART_data_D0,0X55));

		_delay_ms(200);
		//PORTC.OUTTGL  = PIN1_bm| PIN4_bm;
		//PORTC.OUTCLR  = PIN1_bm|PIN4_bm;

		//while (!USART_TXBuffer_PutByte(&USART_data_C0,0x55));

	}

//	TestIC();

	return 0;

}




/*	定时器D0中断，周期为1ms 用于串口处理*/
ISR(TCD0_OVF_vect)
{


	static uint8_t MMM;

	/* Toggle PD0 output after 5 switch presses. */
	TC0_ConfigClockSource( &TCD0, TC_CLKSEL_OFF_gc );

	CbDisCtrl.pDealRcData(&USART_data_C1,&CbDisCtrlData);
	if(CbCtrlData.SendToDisCounter==10)
	{
		if(CbCtrlData.ReceiveFormDisCounter==0)//发送了10帧，接收到0帧
		{
			CbCtrlData.Arm0WorkMode=0;			//摆腿工作模式
			CbCtrlData.Arm18WorkMode=0;			//机械臂工作模式
			CbCtrlData.YtWorkMode=0;				//云台工作模式

			CbCtrlData.TestMode=0;				//测试模式
		}
	}
	else if(CbCtrlData.SendToDisCounter==0)
	{
		CbCtrlData.ReceiveFormDisCounter=0;
	}

	MMM = CbCtrlData.ComSwState;

	if(CbCtrlData.ComSwState == COM_WIRELESS_EN)
		CbCtrl.pDearRcData(&USART_data_C0,&CbCtrlData);
	else if(CbCtrlData.ComSwState == COM_WIRE_EN)
		CbCtrl.pDearRcData(&USART_data_D0,&CbCtrlData);
	if(CbCtrlData.SendToXbotCounter==7)
	{
		CbCtrlData.signal=CbCtrlData.ReceiveFormXbotCounter;
	}
	else if(CbCtrlData.SendToXbotCounter==0)
	{
		CbCtrlData.ReceiveFormXbotCounter=0;
	}

	TC0_ConfigClockSource( &TCD0, TC_CLKSEL_DIV64_gc );
}


/*	定时器D1中断，周期为4ms	*/
ISR(TCD1_OVF_vect)
{


	/* Toggle PD0 output after 5 switch presses. */
	TC1_ConfigClockSource( &TCD1, TC_CLKSEL_OFF_gc );

		CbCtrl.p_DealCtrl();

	TC1_ConfigClockSource( &TCD1, TC_CLKSEL_DIV64_gc );
}




