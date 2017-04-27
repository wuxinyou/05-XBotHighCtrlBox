#include <QtGui>
#include <cmath>
#include <assert.h>
#include "ctrsize.h"

using namespace std;
CtrSize::CtrSize(QWidget *parent)
        : AbstractMeter(parent)
{
        m_max=80;
        m_min=0;

	m_maximum=80; // najpierw rêcznie potem seterem by wywo³a?calcMaxMin
  	setMinimum(0);
	setValue(0);
    //setNominal(30);
	//calcMaxMin(); // bo nie wiemy czym s?zainicjowane limity
	setCritical(60);
	setValueOffset(270);
	setDigitOffset(10);
	setSuffix(QString(" [C]"));
	m_digitFont.setPointSize(15);
	//m_valueFont.setPointSize(18);

	// QWidget
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
	//resize(200, 200);
	assert(m_max-m_min != 0);

}

void CtrSize::initCoordinateSystem(QPainter & painter)
{
        painter.setRenderHint(QPainter::Antialiasing);
        painter.translate( width()/2.0,height()/2.0);
        painter.scale(width()/110.0,height()/28.0);
}

void CtrSize::paintBackground(QPainter & painter)
{
	initCoordinateSystem(painter);
	QPainterPath glass;
	glass.moveTo(-52,-14);
	glass.quadTo(-54,-13, -55,-11);
	glass.lineTo(-55,11);
	glass.quadTo(-54,13 , -52,14);
	glass.lineTo(52,14);
	glass.quadTo(54,13,55,11);
	glass.lineTo(55,-11);
	
	glass.quadTo(54,-13, 52,-14);
	glass.lineTo(-52,-14);
	painter.setBrush(Qt::NoBrush);
	painter.setPen(Qt::green);
	painter.drawPath(glass);
	
	painter.setBrush(QColor(0,120,120));
	painter.setPen(QColor(0,250,50));
	for(int i=0;i<3;i++)
	{
		painter.drawEllipse(-47+i*35,-12,24,24);
	}
	painter.setBrush(QColor(250,250,50));
	painter.setPen(Qt::NoPen);
		painter.drawEllipse(-7,-7,14,14);
		painter.drawRect(-43,-2,16, 4);
		painter.drawRect(-37,-8,4, 16);
		painter.drawRect(27,-2,16, 4);
		//painter.drawEllipse(-47+39,-8,16,16);
		//painter.drawEllipse(-47+39,-8,16,16);
		//painter.drawEllipse(-47+39,-8,16,16);
		//painter.drawEllipse(-47+39,-8,16,16);
	painter.end();
	

}

void CtrSize::paintEvent(QPaintEvent * )
{
	QPainter painter(this);
    initCoordinateSystem(painter);
	painter.end(); 
	drawBackground();
}
void CtrSize::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		int x= e->pos().x();//globalPos
		int w=width();
		if(x<w/3)
			emit sizeflagchange(1);
		if(x>w/3&&x<w*2/3)
			emit sizeflagchange(2);
		if(x>w*2/3)
			emit sizeflagchange(3);
			
		emit sendx(x);
	}
	else
		return;
}




