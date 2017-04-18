#include <QtGui>
#include <cmath>
#include <assert.h>
#include <math.h>
#include "battery.h"
//#include <QPointarray> 
//#define  PI 3.14159265 
using namespace std;
Battery::Battery(QWidget *parent): AbstractMeter(parent)
{
	m_max=255;
	m_min=0;
	m_maximum=255;
	m_minimum=0;
	setValue(100);
	setNominal(50);
	setCritical(200);
	m_digitFont.setPointSize(14);
	m_valueFont.setPointSize(18);
	assert(m_max-m_min != 0);
}

void Battery::initCoordinateSystem(QPainter & painter)
{
		//最简单的进度条控件
        painter.setRenderHint(QPainter::Antialiasing);
        painter.scale(width()/ 29.0, height()/ 16.0);//通过(sx, sy)拉伸坐标系统。使长宽比例一致 不变形
}

void Battery::paintBackground(QPainter & painter)
{
	//最简单的进度条控件
	initCoordinateSystem(painter);
	//painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(255,255,255)));//设置画刷
	painter.drawRoundedRect(0,0 ,29, 16,3,3);
	painter.setBrush(QBrush(QColor(100,100,100)));//设置画刷
	painter.setPen(QColor(0,0,0));
	//painter.setPen(Qt::NoPen);
	painter.drawRect(3,3 ,20, 10);
    painter.drawLine(24,6 ,24, 10);
     painter.drawLine(25,6 ,25, 10);
	painter.end(); 
}// paintBackground

void Battery::paintEvent(QPaintEvent * )
{
	drawBackground();//画控件背景
	QPainter painter(this);
    initCoordinateSystem(painter);
    
    QColor color(QColor(255,255,255));
    if(m_value<m_nominal)
    	color=Qt::red;
    //if(m_value>m_critical)
   		//color=Qt::blue;
	double factor =  m_value/ (m_max-m_min);
	int temp = static_cast<int> (18.0 *  factor);
    painter.setPen(Qt::NoPen);
	painter.setBrush(color);
		painter.drawRect(4,4 ,temp, 8);

	painter.end(); 
	
}// paintEvent
