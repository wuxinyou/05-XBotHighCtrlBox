

/*****************************************************
说明：该类是循环顺序队
作者：吴新有
日期：2016-12-12
备注：主要用于对串口数据接收并转存作用，
因为串口数据是一个一个字符接收的，当需要对数据帧接收时，
需要用到一个链表或者队列转存，然后将数据保存到最终的数据结构中。
队的长度 = 数据帧的长度 + 1	；因为循环队列的front不存放数据

*****************************************************/
#ifndef CYQUEUE_H
#define CYQUEUE_H

#define QUEUESIZE  21
typedef unsigned char ElemType;

typedef struct 
{
	ElemType data[QUEUESIZE];  //保存队列元素
	int front,rear;   //队头和队尾
}SqQueue;


class CyQueue
{
public:
	CyQueue();
	void ClearQueue();
	int EnQueue(ElemType x);  //入队
	int DeQueue(ElemType &x);   //出队
	int GetHead(ElemType &x);   //获取头元素
	int IsEmpty();    //判断为空
	int IsFull();  //判断队满

public:
	SqQueue qu;

};


#endif