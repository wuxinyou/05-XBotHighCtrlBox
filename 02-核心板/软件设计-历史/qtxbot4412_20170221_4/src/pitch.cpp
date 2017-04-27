#include <QtGui>
#include <cmath>
#include <assert.h>
#include <math.h>
#include "pitch.h"
using namespace std;
Pitch::Pitch(QWidget *parent)
        : AbstractMeter(parent)
{
    m_max=360.0;
    m_min=-360.0;

	m_maximum=360.0; // First we set manualy to call calcMaxMin 
  	setMinimum(-360);
	//calcMaxMin(); // Extend max and min to have nice step values 
	setValue(0);
	setValue_1(0);
        //setNominal(80.0);
	//setCritical(220.0);
	//setValueOffset(-100.0);
	//setDigitOffset(105.0);
	//setSuffix(QString(" [bar]"));
	m_digitFont.setPointSize(25);
	//m_digitFont.setBold(true); 
	m_valueFont.setPointSize(25);
	// QWidget
        setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        setWindowTitle(tr("Analog Barmeter"));
	resize(311, 311);
	assert(m_max-m_min != 0);
}

void Pitch::initCoordinateSystem(QPainter & painter)
{
        painter.setRenderHint(QPainter::Antialiasing);
        painter.translate(width() / 2, height() / 2);//设置原点
        painter.scale(width()/ 350.0, height()/ 350.0);//通过(sx, sy)拉伸坐标系统。使长宽比例一致 不变形
}

void Pitch::paintBackground(QPainter & painter)
{
	initCoordinateSystem(painter);
	QPen Pen(QColor(0,0,25));
	Pen.setWidth(6);
    painter.setPen(Qt::NoPen);	
    QRadialGradient back1(QPointF(0.0,0.0),285.0,QPointF(-35.0,145.0));
	back1.setColorAt(0.0,QColor(255,255,255));
	back1.setColorAt(1.0,QColor(0,0,0));

	QRadialGradient back2(QPointF(0.0,0.0),350.0,QPointF(76.5,135.0));
	back2.setColorAt(0.0,QColor(0,0,0));
	back2.setColorAt(1.0,QColor(255,255,255));

	painter.setBrush(QBrush(back1));
	painter.drawEllipse(-175,-175,350,350);
	
   painter.setBrush(QBrush(back2));
   painter.drawEllipse(-170,-170,340,340);

    QRadialGradient shield(QPointF(0,0),150,QPointF(-12.0,-15.0));
	shield.setColorAt(0.0,QColor(25,25,25));
	shield.setColorAt(1.0,QColor(0,0,0));
	painter.setBrush(QBrush(shield));
	painter.setPen(Pen);
	painter.drawEllipse(-160,-160,320,320);
	
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
   painter.setPen(QColor(12,255,255)); 
    painter.setFont (m_digitFont);
    painter.drawText( QPointF(-40,-70), "Pitch");
    //Pen=QColor(0,0,255);
    //painter.setPen(Pen);
    painter.drawText( QPointF(-100,95), "45");
    painter.drawText( QPointF(62,95), "-45");
    painter.drawText( QPointF(-100,-85), "-45");
    painter.drawText( QPointF(62,-85), "45");
    painter.drawText( QPointF(0,85), "deg");
	painter.end();
}// paintBackground

void Pitch::paintEvent(QPaintEvent * )
{
	drawBackground();//画控件背景
	QPainter painter(this);
    initCoordinateSystem(painter);
    painter.setPen(QColor(12,255,255)); 
    painter.setFont (m_digitFont);
	QString val = QString("%1").arg(m_value);
	painter.drawText( QPointF(-47,85), val);
	
	painter.setPen(Qt::NoPen);
	painter.rotate(m_value);

	painter.setBrush(QColor(100,100,100));
	painter.drawPie (-75,-20,40,40,90*16,180*16);
	painter.drawRect(-57,-20,114,40);
	painter.drawPie (35,-20,40,40,270*16,180*16);
		//画分割线
	painter.setPen(QColor(255,0,0));
	painter.drawLine(-150,0,-75,0);
	painter.drawLine(75,0,150,0);
	//painter.setPen(QColor(0,255,0));
	//painter.drawLine(0,-15,0,-150);
	

	painter.translate(55, 0);//重新设置原点
	painter.rotate(m_value_1);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0,0,255));
	QPainterPath glass;
	glass.moveTo(0,-20);
	glass.lineTo(55,-10);
	glass.lineTo(55,10);
	glass.lineTo(0,20);
	glass.lineTo(0,-20);
	painter.drawPath(glass);
	painter.drawPie (43,-10,20,20,270*16,180*16);
	painter.drawPie (-18,-20,40,40,90*16,180*16);
	painter.end();

    
}// paintEvent
#undef OFFSET
