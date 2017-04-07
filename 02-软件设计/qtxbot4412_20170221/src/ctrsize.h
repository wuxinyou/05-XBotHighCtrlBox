#ifndef CTRSIZE_H
#define CTRSIZE_H
#include "abstractmeter.h"

class CtrSize : public AbstractMeter
{
	Q_OBJECT 
	public:
		CtrSize(QWidget *parent = 0);
	 Q_SIGNALS:
		void sizeflagchange(int);		
		void sendx(int);
	protected:
		void paintEvent(QPaintEvent *event); 	  // inherited form WidgetWithBackground
		void paintBackground(QPainter & painter); // inherited form WidgetWithBackground
		void initCoordinateSystem(QPainter & painter);
		void mousePressEvent(QMouseEvent *e);
	//public:
	 //Q_SIGNALS:
		//void sizeflagchange(int);
};
#endif // CTRSIZE_H
