#ifndef VIDEODIS_H
#define VIDEODIS_H
#include <QtGui>
#include "ui_videoDis.h"
#include <qtimer.h>
class VideoDis : public QWidget, public Ui::videoDis
{
	Q_OBJECT
public:
	VideoDis( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	void setPosition(int);
    int mold;
	bool changeFlag;
	QPoint last;
	QPoint backPoint;
	bool lockFlag;
	bool type;
	void setType();
	void resetType();
	void setLock();
	void resetLock();
	void stopVideo();
	void startVideo();
	void setMold(int);
private slots:
	//void changeCount();//定时器事件
signals:
	void mouseChange(int);
	void sendXY(int,int);
protected:
	//void mouseDoubleClickEvent ( QMouseEvent * event );
	void mouseMoveEvent ( QMouseEvent * event );
	void mousePressEvent ( QMouseEvent * event );
	//void mouseReleaseEvent ( QMouseEvent * event );
  	//void paintEvent(QPaintEvent *event);
private:
	int positionFlag;
	QTimer *timer;//定时器防止抖动
	int count;	  //计数器
};
#endif




