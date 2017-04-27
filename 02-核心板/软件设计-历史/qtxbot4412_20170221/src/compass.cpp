#include <QtGui>
#include <cmath>
#include <assert.h>
#include <math.h>
#include "compass.h"
#define  PI 3.14159265 
using namespace std;
Compass::Compass(QWidget *parent): AbstractMeter(parent)
{
	//指南针控件
	m_max=360.0;
	m_min=0.0;
	lightflag=0;
	m_maximum=360.0; // First we set manualy to call calcMaxMin 
  	setMinimum(0.0);
	//calcMaxMin(); // Extend max and min to have nice step values 
	setValue(0.0);
    //setNominal(80.0);
	//setCritical(220.0);
	//setValueOffset(-100.0);
	//setDigitOffset(105.0);
	//setSuffix(QString(" [bar]"));
	m_digitFont.setPointSize(40);
	//m_digitFont.setBold(true); 
	m_valueFont.setPointSize(25);
	// QWidget
    //setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setWindowTitle(tr("Analog Barmeter"));
	//resize(311, 311);
	assert(m_max-m_min != 0);
}

void Compass::setlightflag(bool flag)
{
	lightflag=flag;
	update();
}
void Compass::initCoordinateSystem(QPainter & painter)
{
	//指南针控件
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width() / 2, height() / 2);//设置原点
	painter.scale(width()/ 342.0, height()/ 342.0);//通过(sx, sy)拉伸坐标系统。使长宽比例一致 不变
}

void Compass::paintBackground(QPainter & painter)
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
	
	
	//QRadialGradient back1(QPointF(0.0,0.0),170.0,QPointF(-62,165.0));
	//back1.setColorAt(0.0,QColor(255,255,255));
	//back1.setColorAt(1.0,QColor(45,45,45));
	//
	//painter.setPen(Qt::NoPen);
  //
    //painter.setBrush(QBrush(back1));
	//painter.drawEllipse(-170,-170,340,340);

	//QRadialGradient back3(QPointF(0.0,0.0),170.0,QPointF(-62,160.0));
	//back3.setColorAt(0.0,QColor(0,0,255));
	//back3.setColorAt(1.0,QColor(0,0,80));
		//
	//painter.setBrush(back3);
	//painter.drawEllipse(-164,-164,328,328);

	//QRadialGradient back2(QPointF(0.0,0.0),152.0,QPointF(62,-115.0));
	//back2.setColorAt(0.0,QColor(10,10,10));
	//back2.setColorAt(1.0,QColor(180,180,180));

    //painter.setBrush(QBrush(back2));
    //painter.drawEllipse(-152,-152,304,304);
    //QRadialGradient shield(QPointF(0,0),142,QPointF(-12,-25.0)); 
	//shield.setColorAt(0.0,Qt::white);
	//shield.setColorAt(1.0,QColor(0,0,200));
	//painter.setBrush(QBrush(shield));
	//painter.drawEllipse(-142,-142,284,284);

	painter.setBrush(QColor(180,180,180));
	painter.drawRect(-18,-30,36,90);
	painter.setBrush(QColor(100,100,100));
	painter.drawRect(-30,-40,12,110);
	painter.drawRect(18,-40,12,110);
	
	painter.drawRect(-40,-60,10,45);
	painter.drawRect(30,-60,10,45);
	
	//QPen Pen(QColor(255,0,0));
	//Pen.setWidth(15);
	//painter.setPen(QColor(255,0,0));
	//painter.drawLine(-2,-163,4,-163); 
	painter.end(); 
	
	
}// paintBackground

void Compass::paintEvent(QPaintEvent * )
{
	drawBackground();//画控件背景
	QPainter painter(this);
    initCoordinateSystem(painter);
   
    painter.rotate(m_value);
    painter.setPen(Qt::NoPen);
    QColor color=QColor(0,0,255);
    if(lightflag)
    	color=QColor(255,0,0);	
    QLinearGradient linearGrad(0.0,0.0,0.0,-120.0);			//线性渐变
    linearGrad.setSpread(QGradient::ReflectSpread);
	color.setHsv(color.hue(),color.saturation(),color.value());
    linearGrad.setColorAt(1.0,color);
    color.setHsv(color.hue(),color.saturation()-200,color.value());
    linearGrad.setColorAt(0.0,color);
	painter.setBrush(linearGrad);
	painter.drawPie (-162,-162,324,324,60*16,60*16);
	//painter.end(); 
	painter.rotate(m_value_1-m_value);
	QPen Pen(QColor(255,255,255));
    painter.setPen(Pen);
	for (int i=0;i<72;i++)
	{
       if (i % 9)
       	 painter.drawLine(0,161,0,150); 
       else
       	 painter.drawLine(0,161,0,140); 
	  painter.rotate(5);
    }
    QPen Pen2(QColor(0,255,0));
    painter.setPen(Pen2);
    painter.setFont (m_digitFont);
    painter.drawText( QPointF(-12,140), "S");
    painter.rotate(90);
    painter.drawText( QPointF(-12,140), "W");
    painter.rotate(90);
    painter.drawText( QPointF(-12,140), "N");
    painter.rotate(90);
    painter.drawText( QPointF(-12,140), "E");
    
   
	painter.end(); 

}// paintEvent

