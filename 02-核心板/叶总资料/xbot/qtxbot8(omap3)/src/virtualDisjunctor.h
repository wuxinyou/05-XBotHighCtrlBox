#ifndef VIRTUALDISJUNCTOR_H
#define VIRTUALDISJUNCTOR_H

#include <QPushButton>
#include <qevent.h>
#include <qpainter.h>
#include <qstring.h>
#include <qtextcodec.h>
#include <qnamespace.h>
#include <qtimer.h>
#include <QPoint>

class VirtualDisjunctor: public QWidget
{
    Q_OBJECT
public:
     VirtualDisjunctor( QWidget * parent = 0); 
    ~VirtualDisjunctor();
	 bool  pressedFlag;
	 bool getValue();
	 
private:	 
	 bool value;
	 QPixmap pix;
	 QPixmap pix1;
	
public Q_SLOTS:
    void setValue(bool);
	void setPressIco(QString);
	void setReleaseIco(QString);
	void resetValue();
Q_SIGNALS:
	void pressed();
	void released();	
	
protected:

	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
  	void paintEvent(QPaintEvent *event); 	
};
#endif // VIRTUALDISJUNCTOR_H
