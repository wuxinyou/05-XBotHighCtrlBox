#include "mainwindow.h" 
   
#include "ui_mainwindow.h" 
#include "JOYSTICK.h" 
#include <QMessageBox> 
 
#define POS_MIN 0 
#define POS_MAX 65535 
#define POS_CENTER 32767 
 
MainWindow::MainWindow(QWidget *parent) : 
 QMainWindow(parent),
 ui(new Ui::MainWindow) 
{ 
 ui->setupUi(this); 
 timer = new QTimer(this); 
 connect(timer, SIGNAL(timeout()), this, SLOT(joyMove())); 
 connect(ui->openJoyBtn, SIGNAL(clicked()), this, SLOT(openJoy())); 
 
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
 
MainWindow::~MainWindow() 
{ 
 //释放操纵杆捕获 
 qJoyReleaseCapture(JOYSTICKID1); 
 
 delete ui; 
} 
 
void MainWindow::showMsg(QString str){ 
 ui->label->setText(str); 
} 
 
void MainWindow::openJoy(){ 
 
 unsigned int num = qJoyGetNumDevs(); 
 if(num <= 0){ 
 showMsg(tr("System doesn't support Joystick.")); 
 return; 
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
 if(caps & JOYCAPS_HASPOV) ui->lbl_MSG->setText(QString("has JOYCAPS_HASPOV.")); 
 if(caps & JOYCAPS_POV4DIR) ui->lbl_MSG->setText(QString("has JOYCAPS_POV4DIR.")); 
 if(caps & JOYCAPS_POVCTS) ui->lbl_MSG->setText(QString("has JOYCAPS_POVCTS.")); 
 
// period = joycaps.wPeriodMin; 
 
 ui->lbl_buttonNum->setText("\nNumButtons:" + QString::number(numButtons, 'f',0)); 
 
 timer->start(); 
 
// //捕获游戏操纵杆 
// int joyMsg; 
// HWND hWnd = (HWND)this->winId(); 
// joyMsg = qJoySetCapture(hWnd, JOYSTICKID1 , 0, false); 
// if(joyMsg==JOYERR_NOCANDO){ //捕获失败 
// showMsg(tr("Cannot cap joystick")); 
// }else if(joyMsg==JOYERR_UNPLUGGED){ //没有连接 
// showMsg(tr("The joystick isnt connecting")); 
// }else if(joyMsg==MMSYSERR_NODRIVER){ //没有安装 
// showMsg(tr("joy driver was not installed")); 
// }else if(joyMsg==JOYERR_NOERROR){ //捕获成功 
// showMsg(tr("Cap joystick success.")); 
// }else { 
// showMsg(tr("Cap joystick unamed err.")); 
// } 
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
 
void MainWindow::joyMove(){ // Joystick button action or 
 JOYINFOEX joyInfoEx; 
 joyInfoEx.dwSize = sizeof(typeof(JOYINFOEX)); 
 joyInfoEx.dwFlags = (int)JOY_RETURNBUTTONS; 
 qJoyGetPosEx(JOYSTICKID1, &joyInfoEx); 
 
 if(joyInfoEx.dwButtonNumber){ 
// showMsg(tr("JOY BUTTON1 DOWN.")); 
 switch(joyInfoEx.dwButtons){ 
 case JOY_BUTTON1: ui->lbl_buttonNum->setText("button1 pressed."); break; 
 case JOY_BUTTON2: ui->lbl_buttonNum->setText("button2 pressed."); break; 
 case JOY_BUTTON3: ui->lbl_buttonNum->setText("button3 pressed."); break; 
 case JOY_BUTTON4: ui->lbl_buttonNum->setText("button4 pressed."); break; 
 case JOY_RETURNU: ui->lbl_buttonNum->setText("button5 pressed."); break; 
 case JOY_RETURNV: ui->lbl_buttonNum->setText("button6 pressed."); break; 
 case JOY_RETURNPOV: ui->lbl_buttonNum->setText("button7 pressed."); break; 
 case JOY_RETURNBUTTONS: ui->lbl_buttonNum->setText("button8 pressed."); break; 
 case JOY_BUTTON9: ui->lbl_buttonNum->setText("button9 pressed."); break; 
 case JOY_BUTTON10: ui->lbl_buttonNum->setText("button10 pressed."); break; 
 case JOY_BUTTON11: ui->lbl_buttonNum->setText("button11 pressed."); break; 
 case JOY_BUTTON12: ui->lbl_buttonNum->setText("button12 pressed."); break; 
 case JOY_BUTTON13: ui->lbl_buttonNum->setText("button13 pressed."); break; 
 case JOY_BUTTON14: ui->lbl_buttonNum->setText("button14 pressed."); break; 
 default: ui->lbl_buttonNum->setText(QString::number(joyInfoEx.dwButtons)); 
 } 
 } 
 
 if(1){ // hasPov 
 switch(joyInfoEx.dwPOV){ 
 case JOY_POVCENTERED: ui->lbl_Pov->setText("JOY_POVCENTERED."); break; 
 case JOY_POVFORWARD: ui->lbl_Pov->setText("JOY_POVFORWARD."); break; 
 case JOY_POVRIGHT: ui->lbl_Pov->setText("JOY_POVRIGHT."); break; 
 case JOY_POVBACKWARD: ui->lbl_Pov->setText("JOY_POVBACKWARD."); break; 
 case JOY_POVLEFT: ui->lbl_Pov->setText("JOY_POVLEFT."); break; 
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
 
 if(hasU){ 
 pos = (unsigned int)joyInfoEx.dwUpos; 
 if(joyUPos != pos) 
 { 
 joyUPos = pos; 
 joyU = calcPos(joyUPos); 
 } 
 str.append("\nU=" + QString::number(joyU, 'f', 0)); 
 } 
 
 // V programming has problem 
 if(hasV){ 
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
 
int MainWindow::calcPos(unsigned int joyPos){ 
 double x = 0; 
 x = ((double)joyPos - POS_CENTER)*100 / (POS_MAX - POS_MIN); 
 return (int)x; 
} 
   
 //main.cpp
 //#include <QtGui/QApplication> 
//#include "mainwindow.h" 
 //
//int main(int argc, char *argv[]) 
//{ 
 //QApplication a(argc, argv); 
 //MainWindow w; 
 //w.show(); 
 //return a.exec(); 
//} 
