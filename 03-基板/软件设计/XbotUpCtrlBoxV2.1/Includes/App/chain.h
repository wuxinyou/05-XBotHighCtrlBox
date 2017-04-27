#ifndef CHAIN_H
#define CHAIN_H
#include <stdlib.h>		
#include "stm32f10x.h"
#include "STM32_UsartDriver.h"

#define DATATYPE uint8_t
//双向循环链表的结构体
typedef struct CHAIN
{
	DATATYPE data;
	struct CHAIN *last;
	struct CHAIN *next;	
} chain;


//在已知节点后插入一个节点
void insertAfter(DATATYPE,chain *p);


//在已知节点前插入一个节点
void insertBefore(DATATYPE,chain *p);


//删除后继节点，即p的后一个节点
bool deleteAfter(chain *head,chain *p);


//删除前一个节点，即p的前一个节点
bool deleteBefore(chain *head,chain *p);


//删除节点本身
bool deletSelf(chain *head,chain *p);


//创建一个双向循环链表
chain * creatChain(uint16_t len);	 


//删除一个双向循环链表
void deleteChain(chain *head);

//bool receiveData(USART_data_t* p_usart_data, uint8_t* pRXD_DATA);

#endif
