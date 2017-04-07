#ifndef VIDEOFLAG_H
#define VIDEOFLAG_H
#include <QWidget>
class VideoFlag : public QWidget
{
	Q_OBJECT 
	public:
		VideoFlag(QWidget *parent = 0);
		int value;
		void setValue(int);
		int getValue() const { return value;}
	protected:
		void paintEvent(QPaintEvent *event); 	  // inherited form WidgetWithBackground
};
#endif // VIDEOFLAG_H
