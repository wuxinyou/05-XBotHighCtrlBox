#ifndef MYSERIALPORT_H   
#define MYSERIALPORT_H   
#include <QObject>   
#include <QQueue>   
#include <QMetaType>   
#include <QThread>
#include <QMutex>
#include "Qtcustom/serialport.h"


class SendThread : public QThread  
{  
    Q_OBJECT  
public:  
    SendThread(SerialPort  &adrPort);  
    ~SendThread();  
    void addDataToSend(const QByteArray &dataToAdd);  
    void stopSending();  
protected:  
    void run();  
private:  
    SerialPort &port;  
    QQueue<QByteArray> dataToSend;  
    QMutex mutexSend;  //互斥量定义
    bool stopped;  
};  
class ReceiveThread : public QThread  
{  
    Q_OBJECT  
public:
    ReceiveThread(SerialPort *adrPort);
    ~ReceiveThread();  
    void stopReceiving();
    //void openJoy(); //打开手柄
protected:
    void run();
signals:  
    void dataReceived(QByteArray);
    void dataReceived1(QByteArray);
private :  
    SerialPort *port;
    bool stopped;
};  
#endif // MYSERIALPORT_H  
