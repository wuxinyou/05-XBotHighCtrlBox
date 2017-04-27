#include <QtGui>
#include "light.h"

Light::Light(QWidget *parent)
        : QWidget(parent)
{
	setValue(false);
}
void Light::setValue(bool b)
{
	if(value!=b)
	{
		value=b;
		update();
	}
}

void Light::paintEvent(QPaintEvent * )
{
	QPainter painter(this);
	QPixmap pix;
	QPixmap pix1;
	if(!pix.load(":/images/light_2.png",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
	{
		QMessageBox::information(this, "", "Light failed load file_1");
	}	
	if(!pix1.load(":/images/light_1.png",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
	{
		QMessageBox::information(this, "", "Light failed load file_2");
	}
	if(value)
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
	painter.end();

}
#undef OFFSET
