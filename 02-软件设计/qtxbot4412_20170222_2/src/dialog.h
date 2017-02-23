#ifndef DIALOG_H
#define DIALOG_H

#include "ui_dialog.h"
class Dialog : public QDialog, public Ui::dialog
{
	Q_OBJECT
public:
	Dialog( QWidget * parent = 0);
private slots:
	 Q_SIGNALS:
	 void showmainwin();
protected:
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
private:	
	QPoint last;
	QPoint pos0;
};
#endif




