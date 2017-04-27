#ifndef COORD_H
#define COORD_H
#include <QWidget>
class Coord : public QWidget
{
	Q_OBJECT 
	public:
		Coord(QWidget *parent = 0);
		bool value;
		bool getValue() const { return value;}
	public slots:
		void setValue(bool);
		void changeValue();
	protected:
		void paintEvent(QPaintEvent *event); 	  // inherited form WidgetWithBackground
};
#endif // COORD_H
