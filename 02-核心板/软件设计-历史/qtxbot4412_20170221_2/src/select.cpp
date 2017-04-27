#include <QtGui>
#include <cmath>
#include <assert.h>
#include <math.h>
#include "select.h"
//#include <QPointarray> 
//#define  PI 3.14159265 
using namespace std;

 


Selectfalg::Selectfalg(QWidget *parent)
        : AbstractMeter(parent)
{
	full_screen_flag=false;
    m_max=0XFFFFFFFF;
    m_min=0X000000;
	m_maximum=0XFFFFFFFF; // First we set manualy to call calcMaxMin 
  	setMinimum(0X000000);
	setValue(0X000000);
	setValue_2(0);
	setValue_3(0X1000);
	//setValueOffset(-100.0);
}
void Selectfalg::setValue_2(int v)
{
	m_value_2=v;
	update();
}

void Selectfalg::setValue_3(int v)
{
	m_value_3=v;
	update();
}
void Selectfalg::setFull(bool v)
{
	full_screen_flag=v;
	update();
}
void Selectfalg::paintBackground(QPainter & painter)
{

}
void Selectfalg::initCoordinateSystem(QPainter & painter)
{
        painter.setRenderHint(QPainter::Antialiasing);
        painter.scale(width()/ 800.0, height()/ 600.0);//通过(sx, sy)拉伸坐标系统。使长宽比例一致 不变形
}
void Selectfalg::paintflag(QPainter & painter,int x,int y,int x1,int y1)
{
	int l=(x1-x)/6;
	int h=(y1-y)/6;
	//painter.setPen(QColor(255,0,0));
	painter.setPen(QPen(QColor(255,0,0),2));
	painter.drawLine(x,y,x+l,y);	
	painter.drawLine(x,y,x,y+h);
	
	painter.drawLine(x,y1,x+l,y1);	
	painter.drawLine(x,y1,x,y1-h);
	
	painter.drawLine(x1,y,x1-l,y);	
	painter.drawLine(x1,y,x1,y+h);
	
	painter.drawLine(x1,y1,x1-l,y1);	
	painter.drawLine(x1,y1,x1,y1-h);

}
void Selectfalg::paintEvent(QPaintEvent * )
{
	QPainter painter(this);
    initCoordinateSystem(painter);
    int f=0;
    QLinearGradient linearGrad(QPointF(0, 600), QPointF(0,568));//设置渐变颜色
	
    if(full_screen_flag)
    {
    	linearGrad.setSpread(QGradient::ReflectSpread);
    	linearGrad.setColorAt(1.0, QColor(200,200,255));
   	 	linearGrad.setColorAt(0.0, QColor(75,75,200));
    	painter.setPen(Qt::NoPen);
    	painter.setBrush(QBrush(linearGrad));
    	painter.drawRect(0,568,800,32);
    	painter.setPen(QColor(0,0,0));
    	painter.setFont(QFont(("幼圆"),13)); 
 		switch((int)m_value)
	    {
	    	case 0:
	    		painter.drawText( 5,592, "关节直接控制模式");
	    		break;
	    	case 1:
	    		painter.drawText( 5,592, "预置位控制模式");
	    		break;
	    	case 2:
	    		painter.drawText( 5,592, "摄像头控制模式");
	    		break;
	    	default:
	    	
	    		break;	    		
	    }    	
    	return;
    }

    painter.setPen(QColor(255,0,0));
    //painter.setBrush(Qt::NoBrush);
    painter.setBrush(QColor(0,0,255,100));
    switch((int)m_value)
    {
    	case 0:
    		f=(int)m_value_1;
    		break;
    	case 1:
    		f=(int)m_value_2;
    		break;
    	case 2:
    		f=(int)m_value_3;
    		break;
    	default:
    	
    		break;	    		
    }
	for(int i=0;i<8;i++)
	{
		if(f&(0x01<<i))
		{
			painter.drawRoundedRect(1,3+75*i,53,69, 5.0, 5.0);
		}
		if(f&(0x01<<(i+8)))
		{
			painter.drawRoundedRect(746,3+75*i,53,69, 5.0, 5.0);
		}	
	}    

}
#undef OFFSET
