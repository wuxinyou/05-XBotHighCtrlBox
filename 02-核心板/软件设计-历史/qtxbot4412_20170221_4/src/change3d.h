#ifndef CHANGE3D_H
#define CHANGE3D_H
#include <QWidget>
class Change3d : public QWidget
{
	Q_OBJECT 
	public:
		Change3d(QWidget *parent = 0);
		int value;
		int getValue() const         { return value;}
	private:
		bool flag;
		void setFlag(bool);
		int lasty;
	public slots:
		void setValue(int);
	signals:  
   		void valueChanged(double);		
	protected:
		void paintEvent(QPaintEvent *);
		void mouseMoveEvent(QMouseEvent *);
		void mousePressEvent(QMouseEvent *);
		void mouseReleaseEvent(QMouseEvent *);
};
#endif // CHANGE3D_H
