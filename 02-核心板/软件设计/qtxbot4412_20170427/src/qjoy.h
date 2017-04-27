#ifndef QJOY_H
#define QJOY_H

#include "ui_qjoy.h"
#include <QEvent> 
#include <QTimer> 
class Qjoy : public QWidget, public Ui::qjoy
{
	Q_OBJECT
public:
	Qjoy( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~Qjoy();
private slots: 
 void showMsg(QString); 
 void openJoy(); 
 void joyMove(); 
 int calcPos(unsigned int); 
protected: 
// virtual bool winEvent(MSG *, long * ); 
private: 
 QTimer *timer; 
 unsigned int joyXPos, joyYPos, joyZPos, joyRPos, joyUPos, joyVPos, numButtons, numAxes, period; 
 int joyX, joyY, joyZ, joyR, joyU, joyV;  
 bool hasU, hasV; 
};
#endif




