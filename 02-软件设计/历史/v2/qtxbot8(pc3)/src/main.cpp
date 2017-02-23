#ifdef quick_start
#include<QtPlugin>
Q_IMPORT_PLUGIN(qsqlite)
Q_IMPORT_PLUGIN(qmng)
Q_IMPORT_PLUGIN(qgif)
Q_IMPORT_PLUGIN(qjpeg)
#endif

#include <QApplication>
#include "mainframe.h"

int main(int argc, char ** argv)
{
	QApplication app( argc, argv );
	QFont font;
	font.setPointSize(9);
	QApplication::setFont(font);
	Mainframe win;
	win.show();
	//Qjoy w; 
	//w.show(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec();
}
