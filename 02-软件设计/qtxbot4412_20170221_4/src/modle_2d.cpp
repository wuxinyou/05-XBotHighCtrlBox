
/********************************************************************************
概述：modle_2d.cpp显示机器人的2D图像，以及相关的参数.其中关节可以设置旋转
作者：吴新有
日期：2017-01-12
备注：由于4412里的Linux-qt不能显示中文，所以使用贴图的方式。
********************************************************************************/


#include "modle_2d.h"

#include <qimage.h>
#include <qpixmap.h>

Modle_2d::Modle_2d( QWidget* parent)
         :QWidget(parent)         
{
	disflag=false;
	value_1=180;
	value_2=178;
	value_3=0;
	value_4=180;
	value_5=0;
	value_6=0;
	value_7=0;
	value_8=0;
	value_9=0;
	value_10=0;
	value_11=0;
	
	//<背景贴图加载>
	if(!pix.load(":/images/Modle2DWin.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
	{
		QMessageBox::information(this, "", "failed load file");
	}
	update();
	//</背景贴图加载>
	
}

Modle_2d::~Modle_2d()
{
	
}

void Modle_2d::initCoordinateSystem(QPainter & painter)
{
        painter.setRenderHint(QPainter::Antialiasing);
        painter.scale(width()/332.0,height()/164.0);
}
void Modle_2d::setDis(bool f)
{
	disflag=f;
	if(disflag)
		update();
}

void Modle_2d::setValue_1(int val)
{
	value_1=val;
	if(disflag)
		update();
}
void Modle_2d::setValue_2(int val)
{
	value_2=val;
	if(disflag)
		update();
}
void Modle_2d::setValue_3(int val)
{
	value_3=val;
	if(disflag)
		update();
}
void Modle_2d::setValue_4(int val)
{
	value_4=val;
	if(disflag)
		update();
}
void Modle_2d::setValue_5(int val)
{
	value_5=val;
	if(disflag)
		update();
}
void Modle_2d::setValue_6(int val)
{
	value_6=val;
	if(disflag)
		update();
}
void Modle_2d::setValue_7(int val)
{
	value_7=val;
	if(disflag)
		update();
}
void Modle_2d::setValue_8(int val)
{
	value_8=val;
	if(disflag)
		update();
}
void Modle_2d::setValue_9(int val)
{
	value_9=val;
	if(disflag)
		update();
}
void Modle_2d::setValue_10(int val)
{
	value_10=val;
	if(disflag)
		update();
}
void Modle_2d::setValue_11(int val)
{
	value_11=val;
	if(disflag)
		update();
}
int Modle_2d::getValue_1()
{
	return value_1;
}
int Modle_2d::getValue_2()
{
	return value_2;
}
int Modle_2d::getValue_3()
{
	return value_3;
}

int Modle_2d::getValue_4()
{
	return value_4;
}

int Modle_2d::getValue_5()
{
	return value_5;
}

int Modle_2d::getValue_6()
{
	return value_6;
}

int Modle_2d::getValue_7()
{
	return value_7;
}

int Modle_2d::getValue_8()
{
	return value_8;
}

int Modle_2d::getValue_9()
{
	return value_9;
}

int Modle_2d::getValue_10()
{
	return value_10;
}

int Modle_2d::getValue_11()
{
	return value_11;
}

void Modle_2d::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	
	//<绘制背景图片>
	static int s_modelflag=-1;
	
	if(s_modelflag!=0)
	{
		s_modelflag=0;
		painter.drawPixmap ( 0, 0, 259,143,pix);
		
	}
	//</绘制背景图片>
	
	//if(disflag==false)
		//return;
	initCoordinateSystem(painter);
	
	//由于采用贴图，所以不用绘制背景
	/*
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0,0,0));
	
	painter.drawRect( 0, 0, 332, 164);
	*/
	
	//<打印角度信息>
	painter.setPen(QColor(255,255,255));
	
	painter.drawText(70,19,QString::number(value_1*2));//"大臂俯仰:"+
	
	painter.drawText(70,41,QString::number(value_2*2));//"小臂俯仰:"+
	
	painter.drawText(70,63,QString::number(value_3*2));//"手腕俯仰:"+
	
	painter.drawText(70,85,QString::number(value_4*2));//"云台俯仰:"+
	
	painter.drawText(304,19,QString::number(value_5*2));//"手抓捏合:"+
	
	painter.drawText(304,41,QString::number(value_6*2));//"手抓旋转:"+
	
	painter.drawText(304,63,QString::number(value_7*2));//"大臂旋转:"+
	
	painter.drawText(304,85,QString::number(value_8*2));//"云台旋转:"+
	
	painter.setPen(Qt::NoPen);
	//</打印角度信息>
	
	//<画底盘>
	painter.setBrush(QColor(0,255,0));
	painter.drawRoundedRect(142,140,55,10,5,5);
	painter.setBrush(QColor(0,0,255));
	painter.drawEllipse(150, 136, 6, 6);
	//</画底盘>
	
	//<画支臂>
	painter.translate(147, 145);//重新设置原点 画支臂
	painter.rotate(180-value_9);
	QPainterPath glass;
	glass.moveTo(0,-5);
	glass.lineTo(0,5);
	glass.lineTo(-12,3);
	glass.lineTo(-12,-3);
	glass.lineTo(0,-5);
	painter.drawPath(glass);
	painter.drawPie (-6,-5,10,10,270*16,180*16);
	painter.drawEllipse(-15,-3,6,6);
	//</画支臂>
	
	//<画大臂>
	painter.rotate(value_9-180);
	painter.translate(6, -6);//重新设置原点 画大臂
	painter.rotate(180-value_1);
	
	painter.setBrush(QColor(0,0,255));	
	painter.drawRect(-1,0,40,3);
	
	painter.drawEllipse(35, -3, 6, 6);
	//</画大臂>
	
	//<画小臂>
	//painter.rotate(-value_1);
	painter.translate(38, 0);//重新设置原点 画小臂
	painter.rotate(178-value_2);
	
	painter.drawRect(-37,-2,37,3);
	painter.drawEllipse(-38, -4, 5, 5);
	//</画小臂>
	
	//<画手腕>
	//painter.rotate(-7+value_2);
	painter.translate(-36,-2);//重新设置原点 画手腕
	painter.rotate(-value_3);
	
	painter.drawRoundedRect(-12,-2,47,3,2,2);
	painter.drawRoundedRect(-4,-3,15,5,2,2);
	painter.drawEllipse(33, -4, 5,5);
	//</画手腕>
	
	//<画云台>
	painter.translate(35,0);//重新设置原点 画云台	
	painter.rotate(180-value_4);
	
	painter.drawRect(-1,-4,3,4);	
	QPainterPath glass2;
	glass2.moveTo(-3,-10);
	glass2.lineTo(-3,-4);
	glass2.lineTo(0,-4);
	glass2.lineTo(4,-5);
	glass2.lineTo(4,-9);
	glass2.lineTo(0,-10);
	glass2.lineTo(-3,-10);
	painter.drawPath(glass2);
	painter.setPen(QColor(0,0,255));
	painter.drawLine(-3,-10,-7,-10);
	//</画云台>

	
	
	painter.end();
}
