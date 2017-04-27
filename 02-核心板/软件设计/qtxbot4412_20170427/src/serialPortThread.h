
/********************************************************************************
概述：serialPortThread.h串口数据帧接收线程
作者：吴新有
日期：2017-01-12
备注：串口数据采用循环队列来接收并转存校验

********************************************************************************/

#ifndef __SERIALPORTTHREAD_H__
#define __SERIALPORTTHREAD_H__

#include <QtGui>

#include <QMetaType>   
#include <QThread>
#include <QMutex>

#include <qsocketnotifier.h>


#include "cyQueue.h"
#include "dataType.h"


#define RECEIVE_FRAME_LEN       15
#define RECEIVE_FRAME_HEAD      0XA5
#define RECEIVE_FRAME_COMMAND   0X30

#define SEND_FRAME_LEN          15
#define SEND_FRAME_HEAD         0xA5
#define SEND_FRAME_COMMAND      0XA0

class SerialPortThread : public QThread  
{
Q_OBJECT

public:  
    	SerialPortThread(ReceiveFrame *,SendFrame *); 
    	~SerialPortThread();  
    	void stopSending();
    
Q_SIGNALS:
		void keyDataSignal(ReceiveFrame *);
		void robotDataSignal(ReceiveFrame *);
	
protected:  
   	    void run();


//串口相关的函数
private:
        int openSerialPort();
        bool receiveData(char c);
        QString unicodeToString(QString str);

        QString stringToUnicode(QString str);

private slots:
        void sendData();
        void remoteDataIncoming();

private:
        int m_fd;
        CyQueue *receiveQueue;    //接收数据队列
        ReceiveFrame *receiveKeyFrame;
        ReceiveFrame *receiveRobotFrame;
        SendFrame    *sendFrame;
		QTimer *timerSend;
        QSocketNotifier *m_notifier;

};

#endif // __SERIALPORTTHREAD_H__
