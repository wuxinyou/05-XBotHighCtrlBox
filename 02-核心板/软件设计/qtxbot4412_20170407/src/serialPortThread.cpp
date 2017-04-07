
/********************************************************************************
概述：serialPortThread.cpp串口数据帧接收线程
作者：吴新有
日期：2017-01-12
备注：串口数据采用循环队列来接收并转存校验

********************************************************************************/

//Linux相关的头文件
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>
#include <termio.h>

//Qt相关的头文件
#include <qtextedit.h>
#include <qprogressbar.h>
#include <qtimer.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qstringlist.h>


#include "serialPortThread.h"


SerialPortThread::SerialPortThread(ReceiveFrame *recData,SendFrame *sendData)
{
	receiveFrame=recData;    //父子类 实现共享数据
	sendFrame   =sendData;
	sendFrame->controlData.head=SEND_FRAME_HEAD;
	sendFrame->controlData.command=SEND_FRAME_COMMAND;	
		
	receiveQueue = new CyQueue();    
    
    m_fd = openSerialPort();
    if (m_fd < 0) {
          //  QMessageBox::warning(this, tr("Error"), tr("Fail to open serial port!"));
            return ;
    }

    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
  //  connect (m_notifier, SIGNAL(activated(int)), this, SLOT(remoteDataIncoming()));
	
	timerSend = new QTimer(this);
    connect(timerSend,SIGNAL(timeout()),this,SLOT(sendData()));
    timerSend->start(100);
}


SerialPortThread::~SerialPortThread()
{
	 if (m_notifier) {
            delete m_notifier;
            m_notifier = 0;
        }

        if (m_fd >= 0) {
            ::close(m_fd);
            m_fd = -1;
        }
}


// Thread  Loop   
void SerialPortThread::run()
{

    forever
    {  

	
	remoteDataIncoming();    //将接收放到线程中
    QThread::msleep (2);
    }
} 


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SerialPortThread::openSerialPort()
{
        int fd = -1;
        const char *devName = "/dev/ttySAC3";
        fd = ::open(devName, O_RDWR|O_NONBLOCK);
        if (fd < 0) {
                return -1;
        }
        termios serialAttr;
        memset(&serialAttr, 0, sizeof serialAttr);
        serialAttr.c_iflag = IGNPAR;
        serialAttr.c_cflag = B115200 | HUPCL | CS8 | CREAD | CLOCAL;
        serialAttr.c_cc[VMIN] = 1;
        if (tcsetattr(fd, TCSANOW, &serialAttr) != 0) {
                return -1;
        }
        return fd;
}
        

void SerialPortThread::remoteDataIncoming()
{
        char c;
        //读取串口字符并保存到c中
        if (read(m_fd, &c, sizeof c) != 1) {
               // QMessageBox::warning(this, tr("Error"), tr("Receive error!"));
                return;
        }
        
        
        //接收数据并显示
        receiveData(c);
        

       
}

bool SerialPortThread::receiveData(char c)
{
	unsigned char tempData[RECEIVE_FRAME_LEN]={0};
	
	static bool isHeadEntry=false;	

    //入队
	if(c==RECEIVE_FRAME_HEAD || isHeadEntry)      //如果是帧头或者帧头已经入队，数据才可以入队，否则一概不能入队。
	{
		isHeadEntry=true;     //标记帧头已经入队
		receiveQueue->EnQueue(c);
	}
	//<队满操作>
	if(receiveQueue->IsFull())  //如果队满，就全部出队
	{	
		//出队,临时保存		
		for(int i=0;i<QUEUESIZE-1;i++)
		{
			receiveQueue->DeQueue(tempData[i]);  //出队临时保存
		}			
		
		isHeadEntry=false;  //帧头已经出队		

		//求校验和
		unsigned char checkSum=0;
		for(int icheck=0;icheck<QUEUESIZE-2;icheck++)
		{
			checkSum+=tempData[icheck];			
		}

		//如果校验正确则，保存数据
		if(checkSum==tempData[RECEIVE_FRAME_LEN-1])
		{
			for(int i=0;i<QUEUESIZE-1;i++)
			{
				receiveFrame->byte[i]=tempData[i];				
			}
			if(receiveFrame->byte[1]==0x10)    //收到的是机器人数据
			{
				emit robotDataSignal();
			}
			else// if(receiveFrame->byte[1]==0x30)//收到的是按键数据
			{
				emit keyDataSignal();
			}
			return true;
		}
		//校验处理完


	}
	//</队满操作>
	return false;
	
}

void SerialPortThread::sendData()
{
    //QString text;
	//text="wuXY serialPortThread!  /n";
    //if (text.isEmpty()) {
            //return ;
    //}
    
    ::write(m_fd, sendFrame->byte, SEND_FRAME_LEN);// 缁忓疄楠 寰楄鍙栧埌鐨勯暱搴︿箻2鎵嶈兘鏀跺緱鍏    //ui->m_sendEdit->setText("");

}
        
        