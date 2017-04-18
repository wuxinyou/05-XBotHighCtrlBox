#include <QtGui>
#include <cmath>
#include <assert.h>
#include "signalshow.h"

using namespace std;
SignalShow::SignalShow(QWidget *parent)
        : AbstractMeter(parent)
{
        m_max=8;
        m_min=0;
		m_value=5;
		wiredflag=false;
	//m_maximum=80; // najpierw r阠znie potem seterem by wywo砤?calcMaxMin
  	//setMinimum(0);
	   //setValue(5);
        //setNominal(30);
	//calcMaxMin(); // bo nie wiemy czym s?zainicjowane limity
	//setCritical(60);
	//setValueOffset(270);
	//setDigitOffset(10);
	//setSuffix(QString(" [C]"));
	   m_digitFont.setPointSize(15);
	//m_valueFont.setPointSize(18);

	// QWidget
        //setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        //setWindowTitle(tr("Analog Thermometer"));
	//resize(200, 200);
	//assert(m_max-m_min != 0);

}
void SignalShow::setwiredflag(bool flag)
{
	wiredflag=flag;
	update();
}
void SignalShow::initCoordinateSystem(QPainter & painter)
{
        painter.setRenderHint(QPainter::Antialiasing);
        painter.translate( width()/2.0,height()/2.0);
        painter.scale(width()/110.0,height()/28.0);
}

void SignalShow::paintBackground(QPainter & painter)
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

        //QLinearGradient linearGrad(QPointF(-125.0, 0.0), QPointF(125, 0.0));
		//linearGrad.setSpread(QGradient::ReflectSpread);
        //linearGrad.setColorAt(1.0, QColor(0,150,255,170));
         //linearGrad.setColorAt(0.5, QColor(0,255,150,150));
        //linearGrad.setColorAt(0.0, QColor(255,255,255,10));

	//painter.setBrush(QBrush(linearGrad));
	painter.setBrush(Qt::NoBrush);
	painter.setPen(Qt::green);
	painter.drawPath(glass);
	painter.end(); 
}// paintBackground

void SignalShow::paintEvent(QPaintEvent * )
{

	QPainter painter(this);	
	initCoordinateSystem(painter);
	if(wiredflag)
	{
		//无线
		painter.setPen(QColor(120,255,0)); 
		painter.drawLine(-50,-11,-36,-11);
		painter.drawLine(-50,-11,-43,-2);
		painter.drawLine(-36,-11,-43,-2);
		painter.drawLine(-43,-11,-43,11);
		
		painter.setPen(Qt::NoPen);
		
		painter.setBrush(QColor(120,255,0));
		for(int i=0;i<m_value;i++)
		{
			painter.drawRect(-34+i*11,7-i*2,7, 4+i*2);
		}
		painter.setBrush(QColor(120,120,120,120));
		for(int j=m_value;j<8;j++)
		{
			painter.drawRect(-34+j*11,7-j*2,7, 4+j*2);
		}
	}
	else
	{
		//有线
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(120,255,0));
		painter.drawEllipse(-50,-12,24,24);
		painter.setBrush(QColor(0,0,0));
		painter.drawEllipse(-43,-5,10,10);
		painter.setPen(QColor(120,255,0));
		painter.drawLine(-30,10,50,10);
		painter.setFont (m_digitFont);
		painter.drawText( QPointF(-25,5), "100.00m");		
	}

	painter.end(); 
//	drawBackground();

}// paintEvent

