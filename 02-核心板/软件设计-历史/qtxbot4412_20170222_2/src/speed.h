#ifndef SPEED_H
#define SPEED_H
#include "abstractmeter.h"

    class Speed : public AbstractMeter
    {
      Q_OBJECT 
      public:
    	Speed(QWidget *parent = 0);
      protected:
        void paintEvent(QPaintEvent *event); 	  // inherited form WidgetWithBackground
	void paintBackground(QPainter & painter); // inherited form WidgetWithBackground
	void initCoordinateSystem(QPainter & painter);
    };
#endif // SPEED_H
