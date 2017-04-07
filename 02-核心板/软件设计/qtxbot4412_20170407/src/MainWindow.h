 #ifndef MAINWINDOW_H 
#define MAINWINDOW_H 
 
#include <QMainWindow> 
#include <QEvent> 
#include <QTimer> 
namespace Ui { 
 class MainWindow; 
} 
 
class MainWindow : public QMainWindow 
{ 
 Q_OBJECT 
 
public: 
 explicit MainWindow(QWidget *parent = 0); 
 ~MainWindow(); 
private slots: 
 void showMsg(QString); 
 void openJoy(); 
 void joyMove(); 
 int calcPos(unsigned int); 
protected: 
// virtual bool winEvent(MSG *, long * ); 
 
private: 

 Ui::MainWindow *ui; 
 QTimer *timer; 
 unsigned int joyXPos, joyYPos, joyZPos, joyRPos, joyUPos, joyVPos, numButtons, numAxes, period; 
 int joyX, joyY, joyZ, joyR, joyU, joyV;  
 bool hasU, hasV; 
 
 
}; 
 
#endif // MAINWINDOW_H 
