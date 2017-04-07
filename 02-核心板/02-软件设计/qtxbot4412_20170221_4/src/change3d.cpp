#include <QtGui>
#include "change3d.h"

using namespace std;

Change3d::Change3d(QWidget *parent)
        : QWidget(parent)
{
	flag=false;
	setValue(480);
	
}
void Change3d::setValue(int v)
{
	if(v>580||v<450)
		return;
	if(value!=v)
	{
		value=v;
		this->move(80,value);
		emit valueChanged(((double)(value-420))/20);//1.5-8
	}
}
void Change3d::setFlag(bool b)
{
	if(flag!=b)
	{
		flag=b;
		update();	
	}
}

void Change3d::paintEvent(QPaintEvent * )
{
	QPainter painter(this);
	QPixmap pix;
	QPixmap pix1;
	if(!pix.load(":/images/3dchange_2.png",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
	{
		QMessageBox::information(this, "", "3dchage failed load file_1");
	}	
	if(!pix1.load(":/images/3dchange_1.png",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
	{
		QMessageBox::information(this, "", "3dchage failed load file_2");
	}
	if(flag)
	{
		if(pix.isNull())
		{
			painter.setBrush(QBrush(QColor(255,0,0)));
			painter.drawRoundedRect(0,0, width(),height(), width()/11>3?width()/11:3,height()/11>3?height()/11:3);
		}
		else
		{
			painter.drawPixmap (0,0, width(),height(),pix);
		}
	}
	else
	{
		if(pix1.isNull())
		{
			painter.setBrush(QBrush(QColor(0,125,55)));
			painter.drawRoundedRect(0,0, width(),height(), width()/11>3?width()/11:3,height()/11>3?height()/11:3);
		}
		else
		{
			painter.drawPixmap (0,0, width(),height(),pix1);
		}
	}
	//initCoordinateSystem(painter);
    //int f=0;
    //QLinearGradient linearGrad(QPointF(0, 600), QPointF(0,568));//设置渐变颜色
	//
    //if(full_screen_flag)
    //{
    	//linearGrad.setSpread(QGradient::ReflectSpread);
    	//linearGrad.setColorAt(1.0, QColor(200,200,255));
   	 	//linearGrad.setColorAt(0.0, QColor(75,75,200));
    	//painter.setPen(Qt::NoPen);
    	//painter.setBrush(QBrush(linearGrad));
    	//painter.drawRect(0,568,800,32);
    	//painter.setPen(QColor(0,0,0));
    	//painter.setFont(QFont(("幼圆"),13)); 
 		//switch((int)m_value)
	    //{
	    	//case 0:
	    		//painter.drawText( 5,592, "关节直接控制模式");
	    		//break;
	    	//case 1:
	    		//painter.drawText( 5,592, "预置位控制模式");
	    		//break;
	    	//case 2:
	    		//painter.drawText( 5,592, "摄像头控制模式");
	    		//break;
	    	//default:
	    	//
	    		//break;	    		
	    //}    	
    	//return;
    //}

    //painter.setPen(QColor(255,0,0));

    //painter.setBrush(QColor(0,0,255,100));
    //switch((int)m_value)
    //{
    	//case 0:
    		//f=(int)m_value_1;
    		//break;
    	//case 1:
    		//f=(int)m_value_2;
    		//break;
    	//case 2:
    		//f=(int)m_value_3;
    		//break;
    	//default:
    	//
    		//break;	    		
    //}
	//for(int i=0;i<8;i++)
	//{
		//if(f&(0x01<<i))
		//{
			//painter.drawRoundedRect(1,3+75*i,53,69, 5.0, 5.0);
		//}
		//if(f&(0x01<<(i+8)))
		//{
			//painter.drawRoundedRect(746,3+75*i,53,69, 5.0, 5.0);
		//}	
	//}    

}
void Change3d::mouseMoveEvent(QMouseEvent *e)
{
	setValue(e->globalY()-lasty);
	//this->move(76,e->globalY()-lasty);
}
void Change3d::mousePressEvent(QMouseEvent *e)
{
	lasty=e->y();
	setFlag(true);
}
void Change3d::mouseReleaseEvent(QMouseEvent *e)
{

	setFlag(false);
}
#undef OFFSET






