
/********************************************************************************
概述：modle_2d.h显示机器人的2D图像，以及相关的参数.其中关节可以设置旋转
作者：吴新有
日期：2017-01-12
备注：由于4412里的Linux-qt不能显示中文，所以使用贴图的方式。
********************************************************************************/

#ifndef MYMODULE_H
#define MYMODULE_H
#include <QtGui>
#include <qwidget.h>
#include <qevent.h>
#include <qpainter.h>
#include <qstring.h>
#include <qtextcodec.h>
#include <qnamespace.h>
#include <QPoint>

class Modle_2d : public QWidget
{
    Q_OBJECT

public:
     Modle_2d( QWidget* parent);
    ~Modle_2d();
	bool disflag;
public Q_SLOTS:
    void setDis(bool);
    void setValue_1(int);
    void setValue_2(int);
    void setValue_3(int);
    void setValue_4(int);
    void setValue_5(int);
    void setValue_6(int);
    void setValue_7(int);
    void setValue_8(int);
    void setValue_9(int);
    void setValue_10(int);
    void setValue_11(int);              
    int getValue_1();
    int getValue_2();
    int getValue_3();
    int getValue_4();
    int getValue_5();
    int getValue_6();
    int getValue_7();
    int getValue_8();
    int getValue_9();
    int getValue_10();
    int getValue_11();


protected:
	void initCoordinateSystem(QPainter & painter);
  	void paintEvent(QPaintEvent *event); 
  	
private:

	int value_1;
	int value_2;
	int value_3;
	int value_4;
	int value_5;
	int value_6;
	int value_7;
	int value_8;
	int value_9;
	int value_10;
	int value_11;  
	//背景贴图
	QPixmap pix;
   
};

#endif // MYMODULE_H
