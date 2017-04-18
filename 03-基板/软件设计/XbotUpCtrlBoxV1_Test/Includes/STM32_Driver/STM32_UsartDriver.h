/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief  XMEGA USART driver header file.
 *
 *      This file contains the function prototypes and enumerator definitions
 *      for various configuration parameters for the XMEGA USART driver.
 *
 *      The driver is not intended for size and/or speed critical code, since
 *      most functions are just a few lines of code, and the function call
 *      overhead would decrease code performance. The driver is intended for
 *      rapid prototyping and documentation purposes for getting started with
 *      the XMEGA ADC module.
 *
 *      For size and/or speed critical code, it is recommended to copy the
 *      function contents directly into your application instead of making
 *      a function call.
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
#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include "stm32f10x.h"
#include "MySysDefine.h"
#include "STM32_GpioInit.h"

//#define USART1_RS485  
#define USART2_RS485  
#define USART3_RS485  
#define USART4_RS485  
//#define USART5_RS485  





#define __GPIO_UART2E_PORT	GPIOA				//
#define __GPIO_UART3E_PORT	GPIOD				//
#define __GPIO_UART4E_PORT	GPIOC

#define __GPIO_UART2E_PIN	GPIO_Pin_8 			//
#define __GPIO_UART3E_PIN	GPIO_Pin_10			//
#define __GPIO_UART4E_PIN	GPIO_Pin_12			//

#define UART2E_ON		GPIO_SetBits(__GPIO_UART2E_PORT, __GPIO_UART2E_PIN)	
#define UART2E_OFF		GPIO_ResetBits(__GPIO_UART2E_PORT, __GPIO_UART2E_PIN)
#define UART3E_ON		GPIO_SetBits(__GPIO_UART3E_PORT, __GPIO_UART3E_PIN)	
#define UART3E_OFF		GPIO_ResetBits(__GPIO_UART3E_PORT, __GPIO_UART3E_PIN)
#define UART4E_ON		GPIO_SetBits(__GPIO_UART4E_PORT, __GPIO_UART4E_PIN)	
#define UART4E_OFF		GPIO_ResetBits(__GPIO_UART4E_PORT, __GPIO_UART4E_PIN)

#ifdef USART1_RS485
	#define USART1_RS485_TX_EN  	UART1E_ON
	#define USART1_RS485_TX_DIS		UART1E_OFF
#endif

	
#ifdef USART2_RS485
	#define USART2_RS485_TX_EN   	UART2E_ON
	#define USART2_RS485_TX_DIS	 	UART2E_OFF
#endif
	
#ifdef USART3_RS485
	#define USART3_RS485_TX_EN  	UART3E_ON
	#define USART3_RS485_TX_DIS		UART3E_OFF
#endif
	
#ifdef USART4_RS485
	#define USART4_RS485_TX_EN   	UART4E_ON
	#define USART4_RS485_TX_DIS		UART4E_OFF
#endif
	
#ifdef USART5_RS485
	#define USART5_RS485_TX_EN 		UART5E_ON 
	#define USART5_RS485_TX_DIS		UART5E_OFF		
#endif

/* USART buffer defines. */

typedef USART_TypeDef USART_t; 

/* \brief  Receive buffer size: 2,4,8,16,32,64,128 or 256 bytes. */
#define USART_RX_BUFFER_SIZE 32
/* \brief Transmit buffer size: 2,4,8,16,32,64,128 or 256 bytes */
#define USART_TX_BUFFER_SIZE 32
/* \brief Receive buffer mask. */
#define USART_RX_BUFFER_MASK ( USART_RX_BUFFER_SIZE - 1 )
/* \brief Transmit buffer mask. */
#define USART_TX_BUFFER_MASK ( USART_TX_BUFFER_SIZE - 1 )


#if ( USART_RX_BUFFER_SIZE & USART_RX_BUFFER_MASK )
#error RX buffer size is not a power of 2
#endif
#if ( USART_TX_BUFFER_SIZE & USART_TX_BUFFER_MASK )
#error TX buffer size is not a power of 2
#endif


/* \brief USART transmit and receive ring buffer. */
typedef struct USART_Buffer
{
	/* \brief Receive buffer. */
	volatile uint8_t RX[USART_RX_BUFFER_SIZE];
	/* \brief Transmit buffer. */
	volatile uint8_t TX[USART_TX_BUFFER_SIZE];
	/* \brief Receive buffer head. */
	volatile uint8_t RX_Head;
	/* \brief Receive buffer tail. */
	volatile uint8_t RX_Tail;
	/* \brief Transmit buffer head. */
	volatile uint8_t TX_Head;
	/* \brief Transmit buffer tail. */
	volatile uint8_t TX_Tail;
} USART_Buffer_t;


/*! \brief Struct used when interrupt driven driver is used.
*
*  Struct containing pointer to a usart, a buffer and a location to store Data
*  register interrupt level temporary.
*/
typedef struct Usart_and_buffer
{
	/* \brief Pointer to USART module to use. */
	USART_t * usart;
	/* \brief Data buffer. */
	USART_Buffer_t buffer;
} USART_data_t;







/*! \brief Check if data register empty flag is set.
 *
 *  \param _usart      The USART module.
 */
#define USART_IsTXDataRegisterEmpty(_usart) (((_usart)->STATUS & USART_DREIF_bm) != 0)



/*! \brief Put data (5-8 bit character).
 *
 *  Use the macro USART_IsTXDataRegisterEmpty before using this function to
 *  put data to the TX register.
 *
 *  \param _usart      The USART module.
 *  \param _data       The data to send.
 */
#define USART_PutChar(_usart, _data) ((_usart)->DATA = _data)



/*! \brief Checks if the RX complete interrupt flag is set.
 *
 *   Checks if the RX complete interrupt flag is set.
 *
 *  \param _usart     The USART module.
 */
#define USART_IsRXComplete(_usart) (((_usart)->STATUS & USART_RXCIF_bm) != 0)




/*! \brief Get received data (5-8 bit character).
 *
 *  This macro reads out the RX register.
 *  Use the macro USART_RX_Complete to check if anything is received.
 *
 *  \param _usart     The USART module.
 *
 *  \retval           Received data.
 */
#define USART_GetChar(_usart)  ((_usart)->DATA)



extern void USART_InterruptDriver_Initialize(USART_data_t * usart_data,
                                      USART_t * usart);


extern bool USART_TXBuffer_FreeSpace(USART_data_t * usart_data);
extern bool USART_TXBuffer_PutByte(USART_data_t * usart_data, uint8_t data);
extern bool USART_RXBufferData_Available(USART_data_t * usart_data);
extern uint8_t USART_RXBuffer_GetByte(USART_data_t * usart_data);
extern bool USART_RXComplete(USART_data_t * usart_data);

extern void USART_DataRegEmpty(USART_data_t * usart_data);
extern void USART1_DataRegEmpty(USART_data_t * usart_data);
extern void USART2_DataRegEmpty(USART_data_t * usart_data);
extern void USART3_DataRegEmpty(USART_data_t * usart_data);
extern void USART4_DataRegEmpty(USART_data_t * usart_data);
extern void USART5_DataRegEmpty(USART_data_t * usart_data);


extern bool USART_TXBuffer_SendAll(USART_data_t * usart_data);


#define USART_CR1_TXEIE_gm 	(uint16_t)(1<<7)




#endif
