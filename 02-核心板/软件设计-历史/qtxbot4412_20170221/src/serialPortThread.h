
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


#define RECEIVE_FRAME_LEN       20
#define RECEIVE_FRAME_HEAD      0XA4
#define RECEIVE_FRAME_ADDRESS   0X01
#define RECEIVE_FRAME_COMMAND   0X80

class SerialPortThread : public QThread  
{
Q_OBJECT

public:  
    	SerialPortThread(ReceiveFrame *); 
    	~SerialPortThread();  
    	void stopSending();
    
Q_SIGNALS:
		void readySignal();
	
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
        ReceiveFrame *receiveFrame;
		QTimer *timerSend;
        QSocketNotifier *m_notifier;

};

#endif // __SERIALPORTTHREAD_H__
