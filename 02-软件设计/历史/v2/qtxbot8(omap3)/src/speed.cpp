#include <QtGui>
#include <cmath>
#include <assert.h>
#include <math.h>
#include "speed.h"
//#include <QPointarray> 
//#define  PI 3.14159265 
using namespace std;
Speed::Speed(QWidget *parent): AbstractMeter(parent)
{
	m_max=160;
	m_min=-160;
	m_maximum=160;
	m_minimum=-160;
  	//setMinimum(0);
	setValue(0);
	setValue_1(0);
	
	
	
	//setPrefix(QString("min -2"));
	//setSuffix(QString("max +2"));
	m_digitFont.setPointSize(25);
	m_valueFont.setPointSize(35);
	m_valueFont.setBold(true); 
    //setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setWindowTitle(tr("Analog Thermometer"));
	//resize(200, 200);
	assert(m_max-m_min != 0);
}

void Speed::initCoordinateSystem(QPainter & painter)
{
        painter.setRenderHint(QPainter::Antialiasing);
        
        painter.translate(width() / 2, height() / 2);//设置原点
        
        painter.scale(width()/ 342.0, height()/ 342.0);//通过(sx, sy)拉伸坐标系统。使长宽比例一致 不变形
}
void Speed::paintBackground(QPainter & painter)
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
	
	painter.setPen(QColor(255,255,255));
	for (int i=0;i<72;i++)
	{
		if(i%18)
			painter.drawLine(0,161,0,150); 
	  	painter.rotate(5);
    }
	painter.setPen(QColor(0,255,0));
	painter.drawLine(0,-110,0,110); 
	painter.setPen(QColor(255,0,0));
	painter.drawLine(-100,0,-20,0); 
	painter.drawLine(20,0,100,0); 
	painter.drawLine(0,161,0,135);
	painter.drawLine(0,-161,0,-135); 
	painter.drawLine(-161,0,-135,0); 
	painter.drawLine(161,0,135,0);
	
	painter.setPen(QColor(0,255,0)); 
    painter.setFont (m_valueFont);
    painter.drawText( QPointF(-100,-20), "LS");
    painter.drawText( QPointF(50,-20), "RS");
    //Pen=QColor(0,0,255);
    //painter.setPen(Pen);
    //painter.drawText( QPointF(-100,95), "45");
    //painter.drawText( QPointF(62,95), "-45");
    //painter.drawText( QPointF(-100,-95), "-45");
    //painter.drawText( QPointF(62,-95), "45");
    //painter.drawText( QPointF(0,85), "deg");
	painter.end(); 
}// paintBackground



void Speed::paintEvent(QPaintEvent * )
{
	//最简单的进度条控件
	drawBackground();//画控件背景  
	QPainter painter(this);
 
    initCoordinateSystem(painter);

	QPen Pen(QColor(0,255,0));
	Pen.setWidth(15);
	painter.setPen(Pen);
	int l=(m_value/m_maximum)*90;
	int r=(m_value_1/m_maximum)*90;

    painter.drawArc (-158,-158,316,316,180*16,-l*16);
    painter.drawArc(-158,-158,316,316,0,r*16);
	painter.setFont (m_digitFont);
    painter.setPen(QColor(12,255,255));
    painter.drawText( QPointF(-130,40),QString("%1").arg(m_value*0.01)+"M/S");
    painter.drawText( QPointF(20,40),QString("%1").arg(m_value_1*0.01)+"M/S");
    
	painter.end(); 

}// paintEvent

