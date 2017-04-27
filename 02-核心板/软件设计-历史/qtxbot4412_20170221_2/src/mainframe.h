#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <qdatetime.h>
#include <qtimer.h>
#include "ui_mainframe.h"


#include "roll.h"
#include "pitch.h"
#include "speed.h"
#include "battery.h"
#include "signalshow.h"
#include "speedgrade.h"
#include "ctrsize.h"

#include "modle_2d.h"
#include "light.h"
#include "coord.h"

#include "videoFlag.h"
#include "change3d.h"
#include "videoDis.h"
#include "virtualDisjunctor.h"	//自定义按钮

#include "dataType.h"
#include "serialPortThread.h"
#include "processImage.h"


//功能控制
//#define USE_3D


extern QMutex mutexflag;
extern bool busyflag;	//接受完成标志
class Mainframe : public QDialog, public Ui::mainframe
{
	Q_OBJECT
	public:
		Mainframe( QWidget * parent = 0, Qt::WindowFlags f = 0 );
		~Mainframe();


		
	private slots:		
		void readyRead(QByteArray);
		void disposejoy(QByteArray);
		void changmodelsize(int);
		void sendcommand();
		
		void setM1();//设置为模式1
		void setM2();//设置为模式2
		void setM3();//设置为模式3
		void setM4();//设置为模式4
		void setM5();//设置为模式5

		void zb_tq();//支臂抬起
		void zb_zd();//支臂支地
		void zb_sp();//支臂水平
		void zb_sq();//支臂收起
		void zb_wz();//支臂微支
		void sb_qg();//手臂前观
		
		
		void sb_qz();//手臂全展
		void sb_sq();//手臂收起
		void sb_qs();//手臂前伸
		void sb_bz();//手臂半展
		
			

		void zmControl();//照明开关
			
		void setCH1();//CH1全屏
		void setCH2();//CH3全屏
		void setCH3();//CH2全屏
		void setCH4();//CH4全屏
		void setCHAll();//综合显示
		void setCHFull();//全屏显示
		void changeVideo(int);//切换视频
		void asgChange();
		void rsgChange();
		void jjChange();
		
		void xb_fy();
		void sw_fy();
		void xj_fy();
		void zb_fy();
		void db_fy();
		void db_xz();
		void sz_kh();
		void sz_xz();	
			
	protected:
		void paintEvent(QPaintEvent *event);
		void keyPressEvent(QKeyEvent *event);
		
	private:
		//<摄像头相关的类声明>
		ProcessImage *cameraProcess;
		//</摄像头相关的类声明>
		Roll *myroll;
		Pitch *mypitch;
		Speed *myspeed;
		// no_use3d mymodel *mywid;               //3D模式
		Battery *mybattery;
		Battery *mybattery_1;
		Battery *mybattery_2;
		Battery *mybattery_3;
		Battery *mybattery_4;
		Battery *mybattery_5;
		SignalShow *mysignalshow;
		SpeedGrade *myarms;
		SpeedGrade *myruns;
		CtrSize *myctrsize;
		int myfocaldis;

		Modle_2d *mywid_2d;             
		Light *lightShow;               //标识灯亮灭的状态
		Coord *coordShow;               //坐标显示，仅仅是显示一个坐标符号而已
		
		VideoFlag *videoFlagShow;       //指示当前分屏显示状态
		Change3d *sizeCtr3d;            //改变2D图像大小的滑块，就类似于滑块
		VideoDis *avideo;               //在视频区显示的边框，以标示分屏状态
		
		VirtualDisjunctor *but_M1;
		VirtualDisjunctor *but_M2;
		VirtualDisjunctor *but_M3;
		VirtualDisjunctor *but_M4;
		VirtualDisjunctor *but_M5;
		
		VirtualDisjunctor *but_M1_A1;
		VirtualDisjunctor *but_M1_A2;
		VirtualDisjunctor *but_M1_A3;
		VirtualDisjunctor *but_M1_A4;
		VirtualDisjunctor *but_M1_A5;
		VirtualDisjunctor *but_M1_A6;
		VirtualDisjunctor *but_M1_A7;
		VirtualDisjunctor *but_M1_A8;
		VirtualDisjunctor *but_M1_B1;
		VirtualDisjunctor *but_M1_B2;
		VirtualDisjunctor *but_M1_B3;
		VirtualDisjunctor *but_M1_B4;
		VirtualDisjunctor *but_M1_B5;
		VirtualDisjunctor *but_M1_B6;
		VirtualDisjunctor *but_M1_B7;
		VirtualDisjunctor *but_M1_B8;
		
		VirtualDisjunctor *but_M2_A1;
		VirtualDisjunctor *but_M2_A2;
		VirtualDisjunctor *but_M2_A3;
		VirtualDisjunctor *but_M2_A4;
		VirtualDisjunctor *but_M2_A5;
		VirtualDisjunctor *but_M2_A6;
		VirtualDisjunctor *but_M2_A7;
		VirtualDisjunctor *but_M2_A8;
		VirtualDisjunctor *but_M2_B1;
		VirtualDisjunctor *but_M2_B2;
		VirtualDisjunctor *but_M2_B3;
		VirtualDisjunctor *but_M2_B4;


		VirtualDisjunctor *but_M3_A1;
		VirtualDisjunctor *but_M3_A2;
		VirtualDisjunctor *but_M3_A3;
		VirtualDisjunctor *but_M3_A4;
		VirtualDisjunctor *but_M3_A5;
		VirtualDisjunctor *but_M3_A6;
		VirtualDisjunctor *but_M3_A7;
		VirtualDisjunctor *but_M3_A8;
		VirtualDisjunctor *but_M3_B1;
		VirtualDisjunctor *but_M3_B2;
		VirtualDisjunctor *but_M3_B3;
		VirtualDisjunctor *but_M3_B4;
		VirtualDisjunctor *but_M3_B5;
		VirtualDisjunctor *but_M3_B6;
		VirtualDisjunctor *but_M3_B7;
		VirtualDisjunctor *but_M3_B8;

		VirtualDisjunctor *but_asg1;
		VirtualDisjunctor *but_asg2;
		VirtualDisjunctor *but_rsg1;
		VirtualDisjunctor *but_rsg2;
		
	    //ReceiveThread *receiveThread;   //接收线程
	    bool mouseOK;
		double w;
		double h;
		QTimer *timer;
		QPoint last;
		int winposflag;
		
		ReceiveFrame *receiveFrame;          //串口数据帧接收类
		SerialPortThread *serialPortThread;  //串口数据接收线程
		unsigned char *backdata;      //定义数组 机器人数据备份，也就是用于保存基板转发的机器人数据
		//QByteArray senddata;        //直接使用commanddata发送，而不用senddata来转换
		char *commanddata;            //发送的数据
		
		int ctrsizeflag;
		int verticalflag;
		int horizontalflag;
		int armspeedflag;
		int runapeedflag;
		int armsp;
		int runsp;
		int focflag;
		int focsp;

		bool videoflag;
		bool hide_flag;
		int modelflag;    	         //模式标志 主要有直接控制、预置位控制，摄像头控制

		unsigned char *backjoy;	     //按键备份，用于记录保存按键值
		
		QPixmap pix;
		QPixmap pix1;
		QPixmap pix2;
		
		void initComponent();//初始化部件
		void initData();	 //初始化全局变量
		void initPix();	 	 //初始化界面背景
		void initConnect();	 //初始化信号和槽的关联
		void updateModel();  //设置模式
		
		void jjUp();//焦距拉长
		void jjDown();//焦距缩小
		void xbUp();//小臂上仰
		void xbDown();//小臂下俯
		void swUp();//手腕上仰
		void swDown();//手腕下俯
		void xjUp();//相机上仰
		void xjDown();//相机下俯
		void zbDown();//支臂下俯
		void zbUp();//支臂上仰
		
		void dbUp();//大臂上仰
		void dbDown();//大臂下俯
		void dbleft();//大臂左旋
		void dbright();//大臂右旋
		void szClose();//手抓捏紧
		void szOpen();//手抓松开
		void szright();//手抓右旋
		void szleft();//手抓左旋		
};
 //#endif
#endif