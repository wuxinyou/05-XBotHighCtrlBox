#include <QtGui>
#include "virtualDisjunctor.h"
#include <qimage.h>
#include <qpixmap.h>
#include <cmath>
VirtualDisjunctor::VirtualDisjunctor( QWidget* parent)
         :QWidget(parent)         
{
	value=false;	
	pressedFlag=false;
}

VirtualDisjunctor::~VirtualDisjunctor()
{

}

bool VirtualDisjunctor::getValue()
{
	return value;
}

void VirtualDisjunctor::setValue(bool val)
{
	if(val==value)
		return;
	value=val;
	update();
}

void VirtualDisjunctor::resetValue()
{
	if(value)
		setValue(false);
}

void VirtualDisjunctor::setPressIco(QString s)
{
	if(!pix.load(s,0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
	{
		QMessageBox::information(this, "", "failed load file");
	}	
}
void VirtualDisjunctor::setReleaseIco(QString s)
{
	if(!pix1.load(s,0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
	{
		QMessageBox::information(this, "", "failed load file");
	}
}
void VirtualDisjunctor::mousePressEvent(QMouseEvent *)
{
	pressedFlag=true;
	emit(pressed ());
}

void VirtualDisjunctor::mouseReleaseEvent(QMouseEvent *e)
{
	pressedFlag=false;
	emit(released ());
}

void VirtualDisjunctor::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QColor(0,0,0));

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

