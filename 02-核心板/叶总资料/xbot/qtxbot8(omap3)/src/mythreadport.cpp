#include "mythreadport.h"   
//#include <QThread>
#include <QMessageBox>

//#include "joystick.h"


using namespace std;

typedef struct ricedata//定义接受一个数据的结构体
{
    unsigned char data;
    ricedata *next;
    ricedata *last;
}RICEDATA;

QMutex mutexflag;
bool busyflag=false;	//信号处理完成标志
/****************************** SENDTHREAD ************************************ 
 ******************************************************************************/  
SendThread::SendThread(SerialPort  &adrPort): port(adrPort)  
{  
    dataToSend.clear();  
    stopped = false;  
}  
/******************************* Distructor ***********************************/  
SendThread::~SendThread()  
{  
    if (isRunning())  
    {  
        stopSending();//停止发送数据 等待线程退出  
        wait();  
    }  
}  
/******************************* Methods **************************************/  
// Add the data to the Send Queue   
void SendThread::addDataToSend(const QByteArray &dataToAdd)  
{  
    QMutexLocker locker(&mutexSend);  
    for (int i=0; i<dataToAdd.size(); i++)  
        dataToSend.enqueue(QByteArray(1,dataToAdd.at(i)));  
    if (!isRunning())  
        start();  
}  
// Stop the sending operation   
void SendThread::stopSending()  
{  
    stopped = true;  
}  
// Thread Send Loop   
void SendThread::run()
{  
    QByteArray byteArray;  
    forever  // while(1)？？？？？？？？？ 
    {  
        mutexSend.lock();  
        if (dataToSend.isEmpty() || stopped)  
        {  
            mutexSend.unlock();  
            stopped = false;  
            break;  
        }  
        byteArray = dataToSend.dequeue();  
        mutexSend.unlock();  
        port.write(byteArray);  
    }  
}  

/******************************************************************************* 
 ******************************* RECEIVETHREAD ********************************* 
 ******************************************************************************/  
 
//void ReceiveThread::openJoy() //打开手柄 
//{
	//unsigned int num = qJoyGetNumDevs(); 
	//if(num <= 0)
	//{ 
		//QMessageBox::information(NULL,"Warning","系统不支持游戏杆!");
		//return; 
	//} 
//}

ReceiveThread::ReceiveThread(SerialPort *adrPort): port(adrPort)  
{
	//port=adrPort;
    stopped = false;  
}  
/******************************* Distructor ***********************************/  
ReceiveThread::~ReceiveThread()  
{  
    if (isRunning())  
    {  
        stopReceiving();  
        wait();  
    }  
}  
/******************************* Methods **************************************/  
// Stop the sending operation   
void ReceiveThread::stopReceiving()  
{  
    stopped = true;  
}  

// Thread Receive Loop   
void ReceiveThread::run()  
{  
	RICEDATA *sp=new RICEDATA[15];//接受十三个数据位一个循环
	QByteArray tem=NULL;			 //临时接受区
    unsigned char checksum=0;		 //校验和
	QByteArray recedata=NULL;     	 //接受区
	QByteArray backupdata[4]={NULL,NULL,NULL,NULL};     //备份
	QByteArray backjoydata=NULL;		 //按键备份
	bool backupsentflag=false;			 //备份是否发送标志 对应发送backupdata 0 1 2 3
	bool freeflag=false;
	
	bool backupsentflag1=false;			 //按键备份是否发送标志 对应发送backupdata 0 1 2 3
		
	int backupflag=0;
    for(int i=0;i<15;i++)//构建双向环形链表，每个节点的数据初始化为 0
    {
        sp[i].data=0;
        if(i==14)
        {
            sp[i].next=sp;
        }
        else
        {
            sp[i].next=&sp[i+1];
        }
        
        if(i==0)
        {
            sp[i].last=&sp[i+14];
        }
        else
        {
            sp[i].last=&sp[i-1];
        }
    }//结束链表创建
    RICEDATA *pos=sp;
    
    
    //int joybot=0;
	//int joyposx1=0;
	//int joyposy1=0;
	//int joyposx2=0;
	//int joyposy2=0;
	//int joypov=0;
	//
	//int joydata[6]={0,0,0,0,0,0};//备份
    //
	//JOYINFOEX joyInfoEx; 							//定义接受游戏杆数据的结构体
	//joyInfoEx.dwSize = sizeof(typeof(JOYINFOEX));   //计算结构体的大小（各个系统的大小不一样）
	//joyInfoEx.dwFlags = (int)JOY_RETURNBUTTONS;		//标志位，表示接受哪些数据 
	
    forever
	{
		if (stopped)  
        {  
            stopped = false; 
            break;  							//跳出循环
        }
        tem=port->read(1);
		if (!tem.isEmpty())  				    //不为空 有数据
        {
        	 pos->data=(char)(tem.at(0));
        	 pos=pos->next;
        	 if(pos->data==0xa5)				//下个数据是否和帧头数据相同
        	 {
        	 	checksum+=pos->data;
       	 		pos=pos->next;
       	 		if(pos->data==0x10)				//机器人数据
       	 		{
       	 			checksum+=pos->data;
       	 			pos=pos->next;
       	 			if((pos->data==0x80)||(pos->data==0x81)||(pos->data==0x82)||(pos->data==0x83))
	       	 		{
	       	 			int bf=((pos->data)&0x03);
		        	 	for(int i=0;i<11;i++)
		        	 	{
		        	 		recedata.append(pos->data);//加入到发送字节数组,有用的数据
		        	 		checksum+=pos->data;
		        	 		pos=pos->next;
		       	 		}
		       	 		checksum+=pos->data;			//NC 0x66
		        	 	pos=pos->next;
		       			if(checksum==pos->data)//检查校验和正确，当做正确帧处理
		       			{
		       				backupflag=bf;
		       				if(!backupdata[backupflag].isNull())			//备份不为空，检查和备份帧的区别，有区别，就发送，并且重新备份
		       				{
		       					for(int i=0;i<11;++i)
		       					{
		       						if(backupdata[backupflag].at(i)!=recedata.at(i))
		       						{
						        		backupdata[backupflag]=recedata;		//重新备份
						        		mutexflag.lock(); //互斥量锁定 
						        		freeflag=busyflag;
						        		mutexflag.unlock(); //互斥量解锁 
										if(!freeflag)					//UI线程不忙
										{
											emit dataReceived(recedata);//发送信号
											backupsentflag=true;
										}	
		       							else
		       								backupsentflag=false;   //信号未发送，置备份发送标志为假，表示备份下次循环遇到条件满足可以发送
		       							break;					//跳出for循环
		      						}
		      					}
		       				}
		       				else								//备份为空，直接发送，并备份
		       				{
		       					backupdata[backupflag]=recedata;		//备份
		       					mutexflag.lock(); //互斥量锁定 
				        		freeflag=busyflag;
				        		mutexflag.unlock(); //互斥量解锁 
								if(!freeflag)					//UI线程不忙
								{
						        	emit dataReceived(recedata);//发送信号
						        	backupsentflag=true;
								}		       					backupdata[backupflag]=recedata;		//备份
		       					mutexflag.lock(); //互斥量锁定 
				        		freeflag=busyflag;
				        		mutexflag.unlock(); //互斥量解锁 
								if(!freeflag)					//UI线程不忙
								{
						        	emit dataReceived(recedata);//发送信号
						        	backupsentflag=true;
								}
						        else
						        {
		       						backupsentflag=false;   //信号未发送，置备份发送标志为假，表示备份下次循环遇到条件满足可以发送					        	
					        	}
		   					}       	 			
		   	 			}
		   	 			else									//校验和错误，发送备份数据
	        			{
				        	if(!backupsentflag && !backupdata[backupflag].isNull())//备份发送标志为假，并且备份不为空
							{
				        		mutexflag.lock(); //互斥量锁定 
				        		freeflag=busyflag;
				        		mutexflag.unlock(); //互斥量解锁 
								if(!freeflag)					//UI线程不忙
								{
									emit dataReceived(backupdata[backupflag]);//发送备份数据
									backupsentflag=true;		  //备份数据已经发送，置标志为真
								}
																	//UI线程忙，不发送备份，自动进入下次循环
				        	}
	        			}
	        			recedata=NULL;					//该帧清零
	        			checksum=0;						//校验和清零
						pos=pos->next;                  //指针指向下个节点
	      	 		}
	      	 		else//非命令数据，
	      	 		{
	      	 			checksum=0;						//校验和清零
	      	 			pos=pos->last;//指针指向上个节点
	      	 			pos=pos->last;
     	 			}
       	 		}
      	 		else if(pos->data==0x30)//按键数据
      	 		{
      	 			checksum+=pos->data;
					pos=pos->next;
					for(int i=0;i<12;i++)
					{
						recedata.append(pos->data);//加入到发送字节数组,有用的数据
						checksum+=pos->data;
						pos=pos->next;
					}
					if(checksum==pos->data)//检查校验和正确，当做正确帧处理
		       		{
	       				if(!backjoydata.isNull())			//备份不为空，检查和备份帧的区别，有区别，就发送，并且重新备份
	       				{
	       					for(int i=0;i<12;++i)
	       					{
	       						if(backjoydata.at(i)!=recedata.at(i))
	       						{
					        		mutexflag.lock(); //互斥量锁定 
					        		freeflag=busyflag;
					        		mutexflag.unlock(); //互斥量解锁 
									if(!freeflag)					//UI线程不忙
									{
										if(((recedata.at(5)&0x02)!=0x02)||((backjoydata.at(5)&0x02)!=0x02))
										{
											emit dataReceived1(recedata);//发送信号	
										}
										backupsentflag1=true;
									}	
	       							else
	       								backupsentflag1=false;   	//信号未发送，置备份发送标志为假，表示备份下次循环遇到条件满足可以发送
	       							backjoydata=recedata;		//重新备份
	       							break;							//跳出for循环
	      						}
	      					}
	       				}
	       				else			//备份为空，直接发送
	       				{
	       					
	       					mutexflag.lock(); //互斥量锁定 
			        		freeflag=busyflag;
			        		mutexflag.unlock(); //互斥量解锁 
							if(!freeflag)					//UI线程不忙
							{
								if(((recedata.at(5)&0x02)!=0x02)||((backjoydata.at(5)&0x02)!=0x02))
								{
									emit dataReceived1(recedata);//发送信号	
								}
					        	backupsentflag1=true;
							}
					        else
					        {
	       						backupsentflag1=false;   //信号未发送，置备份发送标志为假，表示备份下次循环遇到条件满足可以发送					        	
				        	}	       					
	       				}
	       				backjoydata=recedata;		//备份
		       		}
		       		else									//校验和错误，发送备份数据
        			{
			        	if(!backupsentflag1 && !backjoydata.isNull())//备份发送标志为假，并且备份不为空
						{
			        		mutexflag.lock(); //互斥量锁定 
			        		freeflag=busyflag;
			        		mutexflag.unlock(); //互斥量解锁 
							if(!freeflag)					//UI线程不忙
							{
								if(((recedata.at(5)&0x02)!=0x02)||((backjoydata.at(5)&0x02)!=0x02))
								{
									emit dataReceived1(recedata);//发送信号
								}
								backupsentflag1=true;		  //备份数据已经发送，置标志为真
							}
																//UI线程忙，不发送备份，自动进入下次循环
			        	}
        			}
        			recedata=NULL;					//该帧清零
	        		checksum=0;						//校验和清零
					pos=pos->next;//指针指向下个节点
     	 		}
      	 		else
      	 		{
      	 			pos=pos->last;
     	 		}

        	 }
        }
        else
        	QThread::usleep(1); 
        tem.clear();    	
	}
	delete [] sp; 

}
