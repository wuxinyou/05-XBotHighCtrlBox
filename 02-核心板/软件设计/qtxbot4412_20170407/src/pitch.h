#ifndef PITCH_H
#define PITCH_H
#include "abstractmeter.h"
    class Pitch : public AbstractMeter
    {
      Q_OBJECT 
      public:
    	Pitch(QWidget *parent = 0);
      protected:
        void paintEvent(QPaintEvent *event); 	  // inherited form WidgetWithBackground
	void paintBackground(QPainter & painter); // inherited form WidgetWithBackground
	void initCoordinateSystem(QPainter & painter);
    };
#endif // PITCH_H
