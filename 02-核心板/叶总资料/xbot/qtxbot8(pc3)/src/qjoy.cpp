#include "qjoy.h"
//#include "ui_mainwindow.h" 
#include "joystick.h" 
#include <QMessageBox> 
#define POS_MIN 0 
#define POS_MAX 65535 
#define POS_CENTER 32767 
Qjoy::Qjoy( QWidget * parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	setupUi(this);
	timer = new QTimer(this); 
	connect(timer, SIGNAL(timeout()), this, SLOT(joyMove())); 
	connect(openJoyBtn, SIGNAL(clicked()), this, SLOT(openJoy())); 
	
	joyXPos = 0; 
	joyYPos = 0; 
	joyZPos = 0; 
	joyRPos = 0; 
	joyUPos = 0; 
	joyVPos = 0; 
	
	joyX = 0; 
	joyY = 0; 
	joyZ = 0; 
	joyR = 0; 
	joyU = 0; 
	joyV = 0; 
	hasV = false; 
	
	numButtons = 0; 
	numAxes = 0; 	
	
}

Qjoy::~Qjoy()
{ 
 //释放操纵杆捕获 
	//qJoyReleaseCapture(JOYSTICKID1);
	delete timer;
} 
 
void Qjoy::showMsg(QString str)
{ 
	label->setText(str); 
} 
 
void Qjoy::openJoy()
{ 
	unsigned int num = qJoyGetNumDevs(); 
	if(num <= 0)
	{ 
		label_7->setText(tr("System doesn't support Joystick.")); 
		return; 
	}else
	{
		label_7->setText(tr("System support Joystick.")); 
	}
	JOYCAPS joycaps; 
	UINT size = (UINT)sizeof(joycaps); 
	qJoyGetDevCaps(JOYSTICKID1, &joycaps, size); // run err 
	// xMin = joycaps.wXmin; 
	// xMax = joycaps.wXmax; 
	// yMin = joycaps.wYmin; 
	// yMax = joycaps.wYmax; 
	// xCenter = (xMax - xMin)/2; 
	// yCenter = (yMax - yMin)/2; 
	numButtons = joycaps.wNumButtons; 
	numAxes = joycaps.wNumAxes; 
	unsigned int caps = joycaps.wCaps; 
	if(caps & JOYCAPS_HASV) hasV = true; 
	if(caps & JOYCAPS_HASU) hasU = true; 
	if(caps & JOYCAPS_HASPOV)  lbl_MSG->setText(QString("has JOYCAPS_HASPOV.")); 
	if(caps & JOYCAPS_POV4DIR) lbl_MSG->setText(QString("has JOYCAPS_POV4DIR.")); 
	if(caps & JOYCAPS_POVCTS)  lbl_MSG->setText(QString("has JOYCAPS_POVCTS.")); 
	
	// period = joycaps.wPeriodMin; 
	
	lbl_buttonNum->setText("\nNumButtons:" + QString::number(numButtons, 'f',0)); 
	
	timer->start(); 
	
	 //捕获游戏操纵杆 
	 //int joyMsg; 
	 //HWND hWnd = (HWND)this->winId(); 
	 //joyMsg = qJoySetCapture(hWnd, JOYSTICKID1 , 0, false); 
	 
	//joyMsg = qJoySetCapture();
	
	
	 //if(joyMsg==JOYERR_NOCANDO)
	 //{ //捕获失败 
	 	//label_7->setText(tr("Cannot cap joystick")); 
	 //}
	 //else
	 //{
	 	//label_7->setText(tr("joystick OK")); 
 	 //}

	 //else if(joyMsg==JOYERR_UNPLUGGED){ //没有连接 
	 //showMsg(tr("The joystick isnt connecting")); 
	 //}else if(joyMsg==MMSYSERR_NODRIVER){ //没有安装 
	 //showMsg(tr("joy driver was not installed")); 
	 //}else if(joyMsg==JOYERR_NOERROR){ //捕获成功 
	 //showMsg(tr("Cap joystick success.")); 
	 //}else { 
	 //showMsg(tr("Cap joystick unamed err.")); 
	 //} 
} 
 
  
//bool MainWindow::winEvent(MSG *msg, long *result){ 
// if(msg->message == MM_JOY1MOVE){ 
// joyMove(); 
// return true; 
// }else if(msg->message == WM_MOUSEMOVE){ 
//// showMsg(tr("mouse move")); 
// }else if(msg->message == WM_LBUTTONDOWN){ 
//// showMsg(tr("LButton down now")); 
// } 
// return QWidget::winEvent(msg, result); 
 
//} 
 
void Qjoy::joyMove()
{ // Joystick button action or 
	JOYINFOEX joyInfoEx; 
	joyInfoEx.dwSize = sizeof(typeof(JOYINFOEX)); 
	joyInfoEx.dwFlags = (int)JOY_RETURNBUTTONS; 
	qJoyGetPosEx(JOYSTICKID1, &joyInfoEx); 
	if(joyInfoEx.dwButtonNumber)
	{ 
		 //showMsg(tr("JOY BUTTON1 DOWN.")); 
		switch(joyInfoEx.dwButtons)
		{ 
			case JOY_BUTTON1: lbl_buttonNum->setText("button1 pressed."); break; 
			case JOY_BUTTON2: lbl_buttonNum->setText("button2 pressed."); break; 
			case JOY_BUTTON3: lbl_buttonNum->setText("button3 pressed."); break; 
			case JOY_BUTTON4: lbl_buttonNum->setText("button4 pressed."); break; 
			case JOY_RETURNU: lbl_buttonNum->setText("button5 pressed."); break; 
			case JOY_RETURNV: lbl_buttonNum->setText("button6 pressed."); break; 
			case JOY_RETURNPOV: lbl_buttonNum->setText("button7 pressed."); break; 
			case JOY_RETURNBUTTONS: lbl_buttonNum->setText("button8 pressed."); break; 
			case JOY_BUTTON9: lbl_buttonNum->setText("button9 pressed."); break; 
			case JOY_BUTTON10: lbl_buttonNum->setText("button10 pressed."); break; 
			case JOY_BUTTON11: lbl_buttonNum->setText("button11 pressed."); break; 
			case JOY_BUTTON12: lbl_buttonNum->setText("button12 pressed."); break; 
			case JOY_BUTTON13: lbl_buttonNum->setText("button13 pressed."); break; 
			case JOY_BUTTON14: lbl_buttonNum->setText("button14 pressed."); break; 
			default: lbl_buttonNum->setText(QString::number(joyInfoEx.dwButtons)); 
		} 
	} 
	
	label_5->setText(QString::number(joyInfoEx.dwReserved1)); 
	label_6->setText(QString::number(joyInfoEx.dwReserved2)); 
	if(1)
 	{ // hasPov 
		switch(joyInfoEx.dwPOV)
		{ 
			case JOY_POVCENTERED: lbl_Pov->setText("JOY_POVCENTERED."); break; 
			case JOY_POVFORWARD: lbl_Pov->setText("JOY_POVFORWARD."); break; 
			case JOY_POVRIGHT: lbl_Pov->setText("JOY_POVRIGHT."); break; 
			case JOY_POVBACKWARD: lbl_Pov->setText("JOY_POVBACKWARD."); break; 
			case JOY_POVLEFT: lbl_Pov->setText("JOY_POVLEFT."); break; 
			default: lbl_Pov->setText(QString::number(joyInfoEx.dwPOV));  break; 
		} 
 	} 

	QString str; 
	unsigned int pos = (unsigned int)joyInfoEx.dwXpos; 
	if(joyXPos != pos) 
	{ 
		joyXPos = pos; 
		joyX = calcPos(joyXPos); 
 	} 
	str = "\nX=" + QString::number(joyX, 'f', 0); 
	
	pos = (unsigned int)joyInfoEx.dwYpos; 
	if(joyYPos != pos) 
	{ 
		joyYPos = pos; 
		joyY = calcPos(joyYPos); 
	} 
	str.append("\nY=" + QString::number(joyY, 'f', 0)); 
	
	pos = (unsigned int)joyInfoEx.dwZpos; 
	if(joyZPos != pos) 
	{ 
		joyZPos = pos; 
		joyZ = calcPos(joyZPos); 
	} 
	str.append("\nZ=" + QString::number(joyZ, 'f', 0)); 
	
	pos = (unsigned int)joyInfoEx.dwRpos; 
	if(joyRPos != pos) 
	{ 
		joyRPos = pos; 
		joyR = calcPos(joyRPos); 
	} 
	str.append("\nR=" + QString::number(joyR, 'f', 0)); 
	
	if(hasU)
	{ 
		pos = (unsigned int)joyInfoEx.dwUpos; 
		if(joyUPos != pos) 
		{ 
			joyUPos = pos; 
			joyU = calcPos(joyUPos); 
		} 
		str.append("\nU=" + QString::number(joyU, 'f', 0)); 
	} 
	if(hasV)
	{ 
		pos = (unsigned int)joyInfoEx.dwVpos; 
		if(joyVPos != pos) 
		{ 
			joyVPos = pos; 
			joyV = calcPos(joyVPos); 
		} 
		str.append("\nV=" + QString::number(joyV, 'f', 0) ); 
	} 
	showMsg(str); 
} 
 
int Qjoy::calcPos(unsigned int joyPos)//按比例缩放摇杆坐标
{ 
	double x = 0; 
	x = ((double)joyPos - POS_CENTER)*100 / (POS_MAX - POS_MIN); 
	return (int)x; 
} 
