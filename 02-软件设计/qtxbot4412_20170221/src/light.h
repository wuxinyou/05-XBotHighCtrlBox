#ifndef LIGHT_H
#define LIGHT_H
#include <QWidget>
class Light : public QWidget
{
	Q_OBJECT 
	public:
		Light(QWidget *parent = 0);
		bool value;
		void setValue(bool);
		bool getValue() const { return value;}
	protected:
		void paintEvent(QPaintEvent *event); 	  // inherited form WidgetWithBackground
};
#endif // LIGHT_H
