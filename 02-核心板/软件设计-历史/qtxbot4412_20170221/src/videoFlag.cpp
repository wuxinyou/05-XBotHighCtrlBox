#include <QtGui>
#include "videoFlag.h"

VideoFlag::VideoFlag(QWidget *parent)
        : QWidget(parent)
{
	setValue(0);
}
void VideoFlag::setValue(int b)
{
	if(value!=b)
	{
		value=b;
		update();
	}
}

void VideoFlag::paintEvent(QPaintEvent * )
{
	QPainter painter(this);
	//painter.setPen(Qt::NoPen);
	painter.setPen(QColor(0,0,0));
	switch(value)
	{
		case 0:
			painter.setBrush(QBrush(QColor(255,255,255)));//ÉèÖÃ»­Ë¢
			painter.drawRect(0,0 ,8, 8);
			painter.drawRect(9,0 ,8, 8);
			painter.drawRect(0,9 ,8, 8);
			painter.drawRect(9,9,8, 8);
			break;
			
		case 1:
			painter.setBrush(QBrush(QColor(255,255,255)));//ÉèÖÃ»­Ë¢
			painter.drawRect(0,0 ,8, 8);
			painter.setBrush(QBrush(QColor(136,136,136)));//ÉèÖÃ»­Ë¢
			painter.drawRect(9,0 ,8, 8);
			painter.drawRect(0,9 ,8, 8);
			painter.drawRect(9,9,8, 8);		
			break;
		
		case 2:
			painter.setBrush(QBrush(QColor(255,255,255)));//ÉèÖÃ»­Ë¢
			painter.drawRect(9,0 ,8, 8);
			painter.setBrush(QBrush(QColor(136,136,136)));//ÉèÖÃ»­Ë¢
			painter.drawRect(0,0 ,8, 8);
			painter.drawRect(0,9 ,8, 8);
			painter.drawRect(9,9,8, 8);		
			break;

		case 3:
			painter.setBrush(QBrush(QColor(255,255,255)));//ÉèÖÃ»­Ë¢
			painter.drawRect(0,9 ,8, 8);
			painter.setBrush(QBrush(QColor(136,136,136)));//ÉèÖÃ»­Ë¢
			painter.drawRect(0,0 ,8, 8);
			painter.drawRect(9,0 ,8, 8);
			painter.drawRect(9,9,8, 8);		
			break;
		case 4:
			painter.setBrush(QBrush(QColor(255,255,255)));//ÉèÖÃ»­Ë¢
			painter.drawRect(9,9,8, 8);	
			painter.setBrush(QBrush(QColor(136,136,136)));//ÉèÖÃ»­Ë¢
			painter.drawRect(0,0 ,8, 8);
			painter.drawRect(9,0 ,8, 8);
			painter.drawRect(0,9 ,8, 8);
			break;
		
	}
	//{
		//if(pix.isNull())
		//{
			//painter.setBrush(QBrush(QColor(255,0,0)));
			//painter.drawRoundedRect(0,0, width(),height(), width()/11>3?width()/11:3,height()/11>3?height()/11:3);
		//}
		//else
		//{
			//painter.drawPixmap (0,0, width(),height(),pix);
		//}
	//}
	//else
	//{
		//if(pix1.isNull())
		//{
			//painter.setBrush(QBrush(QColor(0,125,55)));
			//painter.drawRoundedRect(0,0, width(),height(), width()/11>3?width()/11:3,height()/11>3?height()/11:3);
		//}
		//else
		//{
			//painter.drawPixmap (0,0, width(),height(),pix1);
		//}
	//}
	painter.end();

}
#undef OFFSET
