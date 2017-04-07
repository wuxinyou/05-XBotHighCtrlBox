#include <QtGui>
#include <cmath>
#include <assert.h>
#include <math.h>
#include "roll.h"
//#include <QPointarray> 
//#define  PI 3.14159265 
using namespace std;
Roll::Roll(QWidget *parent)
        : AbstractMeter(parent)
{

	/*
        m_max=80;
        m_min=0;

	m_maximum=80; // najpierw r阠znie potem seterem by wywo砤?calcMaxMin
  	setMinimum(0);
	setValue(0);
        setNominal(30);
	calcMaxMin(); // bo nie wiemy czym s?zainicjowane limity
	setCritical(60);
	setValueOffset(270);
	setDigitOffset(10);
	//setPrefix(QString("温度"));
	setSuffix(QString(" [C]"));
	m_digitFont.setPointSize(15);
	m_valueFont.setPointSize(18);

	// QWidget
        setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        setWindowTitle(tr("Analog Thermometer"));
	resize(200, 200);
	assert(m_max-m_min != 0);
	*/
		//指南针控件
        m_max=300.0;
        m_min=0.0;

	m_maximum=300.0; // First we set manualy to call calcMaxMin 
  	setMinimum(0.0);
	calcMaxMin(); // Extend max and min to have nice step values 

	setValue(0.0);
        setNominal(80.0);
	setCritical(220.0);
	setValueOffset(-100.0);
	setDigitOffset(105.0);
	setSuffix(QString(" [bar]"));
	m_digitFont.setPointSize(25);
	//m_digitFont.setBold(true); 
	m_valueFont.setPointSize(25);

	// QWidget
        setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        setWindowTitle(tr("Analog Barmeter"));
	resize(311, 311);
	assert(m_max-m_min != 0);
}

void Roll::initCoordinateSystem(QPainter & painter)
{
        painter.setRenderHint(QPainter::Antialiasing);
        
        painter.translate(width() / 2, height() / 2);//设置原点
        
        painter.scale(width()/ 342.0, height()/ 342.0);//通过(sx, sy)拉伸坐标系统。使长宽比例一致 不变形
        
}

void Roll::paintBackground(QPainter & painter)
{
	initCoordinateSystem(painter);
	painter.setPen(Qt::NoPen);
	
	QRadialGradient back1(QPointF(0.0,0.0),170.0,QPointF(-62,165.0));
	back1.setColorAt(0.0,QColor(255,255,255));
	back1.setColorAt(1.0,QColor(145,145,145));
	painter.setBrush(QBrush(back1));
	painter.drawEllipse(-170,-170,340,340);
	painter.setBrush(QColor(0,0,0));
	painter.drawEllipse(-164,-164,328,328);
	
	QPen Pen1(QColor(255,255,255));
	painter.setPen(Pen1);
	for (int i=0;i<72;i++)
	{
       if (i % 9)
       	 painter.drawLine(0,161,0,150); 
       else
       	 painter.drawLine(0,161,0,140); 
	  painter.rotate(5);
    }
    painter.setPen(QColor(0,255,0));
    painter.setFont (m_digitFont);
    painter.drawText( QPointF(-28,-70), "Roll");
    //Pen=QColor(0,0,255);
    //painter.setPen(Pen);
    painter.drawText( QPointF(-100,95), "45");
    painter.drawText( QPointF(62,95), "-45");
    painter.drawText( QPointF(-100,-85), "-45");
    painter.drawText( QPointF(62,-85), "45");
    painter.drawText( QPointF(0,85), "deg");
	painter.end();
}// paintBackground



void Roll::paintEvent(QPaintEvent * )
{
	drawBackground();//画控件背景	
	QPainter painter(this);
    initCoordinateSystem(painter);
    painter.setPen(QColor(255,255,0));
    painter.setFont (m_digitFont);
	QString val = QString("%1").arg(m_value);
	painter.drawText( QPointF(-30,85), val);
	
	painter.setPen(Qt::NoPen);
	painter.rotate(m_value);
	painter.setBrush(QColor(180,180,180));
	//画车体
	painter.drawRect(-40,-15,80,30);
	painter.setBrush(QColor(100,100,100));
	painter.drawRect(-75,-26,35,52);
	painter.drawRect(40,-26,35,52);
	//画分割线
	painter.setPen(QColor(255,0,0));
	painter.drawLine(-150,0,-75,0);
	painter.drawLine(75,0,150,0);
	//painter.setPen(QColor(0,255,0));
	//painter.drawLine(0,-15,0,-150);
	painter.end();

    
}// paintEvent
#undef OFFSET
