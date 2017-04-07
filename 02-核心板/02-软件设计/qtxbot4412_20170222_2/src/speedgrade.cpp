#include <QtGui>
#include <cmath>
#include <assert.h>
#include "speedgrade.h"

using namespace std;
SpeedGrade::SpeedGrade(QWidget *parent)
        : AbstractMeter(parent)
{
        m_max=7;
        m_min=1;

	m_maximum=7; // najpierw rêcznie potem seterem by wywo³a?calcMaxMin
  	setMinimum(1);
	setValue(3);
        //setNominal(5);
	//calcMaxMin(); // bo nie wiemy czym s?zainicjowane limity
	//setCritical(60);
	//setValueOffset(270);
	//setDigitOffset(10);
	//setSuffix(QString("ArmSpeedGrade"));
	m_digitFont.setPointSize(12);
	m_valueFont.setPointSize(18);

	// QWidget
        setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        setWindowTitle(tr("Analog Thermometer"));
	resize(200, 200);
	assert(m_max-m_min != 0);

}

void SpeedGrade::initCoordinateSystem(QPainter & painter)
{
        painter.setRenderHint(QPainter::Antialiasing);
        painter.translate( width()/2.0,height()/2.0);
        painter.scale(width()/100.0,height()/30.0);
}

void SpeedGrade::paintBackground(QPainter & painter)
{
	//initCoordinateSystem(painter);
	//QPainterPath glass;
	//glass.moveTo(-52,-14);
	//glass.quadTo(-54,-13, -55,-11);
	//glass.lineTo(-55,11);
	//glass.quadTo(-54,13 , -52,14);
	//glass.lineTo(52,14);
	//glass.quadTo(54,13,55,11);
	//glass.lineTo(55,-11);
	//glass.quadTo(54,-13, 52,-14);
	//glass.lineTo(-52,-14);
	//painter.setBrush(Qt::NoBrush);
	//painter.setPen(Qt::green);
	//painter.setFont (m_digitFont);
	//painter.drawText( QPointF(-48,12),m_suffix);
	

	//painter.end(); 
}

void SpeedGrade::paintEvent(QPaintEvent * )
{
	QPainter painter(this);
    initCoordinateSystem(painter);
    painter.setBrush(QColor(255,255,255));
	painter.setPen(QPen(Qt::NoPen));
	for(int i=0;i<m_value;i++)
	{
		painter.drawRect(-45+i*14,-10,10,8);
	}
	 painter.setBrush(QColor(100,100,100));
	for(int j=m_value;j<7;j++)
	{
		painter.drawRect(-45+j*14,-10,10,8);
	}
    painter.end(); 
	//drawBackground();
}

