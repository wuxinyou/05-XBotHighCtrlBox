
/*****************************************************
说明：该类是循环顺序队
作者：吴新有
日期：2016-12-12
备注：主要用于对串口数据接收并转存作用，
因为串口数据是一个一个字符接收的，当需要对数据帧接收时，
需要用到一个链表或者队列转存，然后将数据保存到最终的数据结构中。	
队的长度 = 数据帧的长度 + 1	；因为循环队列的front不存放数据
对于循环顺序队列而言，遍历队列数组数据是没有意义的，因为总有一个
数据是无效的。
*****************************************************/
#include"cyQueue.h"

CyQueue::CyQueue()
{
	qu.front =0;
	qu.rear=0;

}

void CyQueue::ClearQueue()
{
	qu.front =0;
	qu.rear=0;
}

int CyQueue::EnQueue(ElemType x)
{
	if((qu.rear+1)%QUEUESIZE==qu.front)
		return 0;
	qu.rear=(qu.rear+1)%QUEUESIZE;
	qu.data[qu.rear]=x;
	return 1;
}

int CyQueue::DeQueue(ElemType &x)
{
	if(qu.rear==qu.front)
		return 0;
	qu.front=(qu.front+1)%QUEUESIZE;
	x=qu.data[qu.front];
	return 1;
}

int CyQueue::GetHead(ElemType &x)
{
	if(qu.rear==qu.front)
		return 0;
	x=qu.data[(qu.front+1)%QUEUESIZE];
	return 1;
}

int CyQueue::IsEmpty()
{
	if(qu.rear==qu.front)  //队空
		return 1;
	else
		return 0;

}

int CyQueue::IsFull()
{
	if((qu.rear+1)%QUEUESIZE==qu.front)  //队满
		return 1;
	else 
		return 0;
}