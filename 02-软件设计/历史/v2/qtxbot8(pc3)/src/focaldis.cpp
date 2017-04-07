#include <QtGui>
#include <cmath>
#include <assert.h>
#include "focaldis.h"

using namespace std;
FocalDis::FocalDis(QWidget *parent)
        : AbstractMeter(parent)
{
        m_max=30;
        m_min=0;

	m_maximum=30; // 
  	setMinimum(0);
	setValue(0);
    //setNominal(30);
	//calcMaxMin(); // bo nie wiemy czym s?zainicjowane limity
	//setCritical(60);
	//setValueOffset(270);
	//setDigitOffset(10);
	//setSuffix(QString(" [C]"));
	m_digitFont.setPointSize(10);
	//m_valueFont.setPointSize(18);

	// QWidget
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
	//resize(200, 200);
	assert(m_max-m_min != 0);

}

void FocalDis::initCoordinateSystem(QPainter & painter)
{
        painter.setRenderHint(QPainter::Antialiasing);
        painter.translate( width()/2.0,height()/2.0);
        painter.scale(width()/70.0,height()/70.0);
}

void FocalDis::paintBackground(QPainter & painter)
{
	initCoordinateSystem(painter);
	painter.setBrush(QColor(0,80,180,50));
	painter.setPen(Qt::NoPen);
	painter.drawEllipse(-32,-32,64,64);
	painter.setFont (m_digitFont);
	painter.setPen(Qt::white);
	painter.drawText( QPointF(-35,34), "½ü");
	painter.drawText( QPointF(24,34), "Ô¶");
	
	QPen Pen(QColor(150,150,150));
	Pen.setWidth(4);
	painter.setPen(Pen);
	painter.drawArc (-32,-32,64,64,16*280,16*340);
	painter.end();
}

void FocalDis::paintEvent(QPaintEvent * )
{
	drawBackground();
	QPainter painter(this);
    initCoordinateSystem(painter);
    
	QPen Pen(QColor(0,0,150));
	Pen.setWidth(5);
	painter.setPen(Pen);
	int l=(m_value/m_maximum)*340;
	painter.drawArc (-32,-32,64,64,16*280,l*16);//»­À¶É«Ô²»¡
	int r=(m_value/m_maximum)*32;//»­»Ò°×É«ÄÚÔ²
	painter.setBrush(QColor(180,180,180));
	painter.setPen(Qt::NoPen);
	painter.drawEllipse(-r,-r,2*r,2*r);
	
	painter.setPen(Qt::red);
	if(m_value<10)
		painter.drawText( QPointF(-3,34),QString("%1").arg(m_value));
	else
		painter.drawText( QPointF(-6,34),QString("%1").arg(m_value));
	
	painter.end(); 

}
