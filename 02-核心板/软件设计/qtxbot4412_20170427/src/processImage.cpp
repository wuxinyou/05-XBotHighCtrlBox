/********************************************************************************
概述：processImage.cpp实现图像显示，调用YUV2RGBThread线程
作者：吴新有
日期：2017-01-11
备注：processImage.cpp调用YUV2RGBThread类，实现图像的采集和转换
********************************************************************************/


#include <QtGui>
#include "processImage.h"
#include "camera.h"


ProcessImage::ProcessImage(QWidget *parent):QWidget(parent)
{
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    pp = (unsigned char *)malloc(720 * 576/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));
    //1201 painter = new QPainter(this);
    frame = new QImage(pp,720,576,QImage::Format_RGB888);
   // frame = new QPixmap(640,320);
    label = new QLabel(this);
    label->setGeometry(0,0,Win_width,Win_height);
	//label->resize(Win_width,Win_height);
	imgScaled = new QImage;

	
	cameraThread=new YUV2RGBThread(pp);
	connect(cameraThread,SIGNAL(readySignal()),this,SLOT(update()));  //鏇存柊
	cameraThread->start();

    //QHBoxLayout *hLayout = new QHBoxLayout();
    //hLayout->addWidget(label);
    //setLayout(hLayout);
    
    //setWindowTitle(tr("Capture"));
}

ProcessImage::~ProcessImage()
{

}

void ProcessImage::paintEvent(QPaintEvent *e)
{
	//painter = new QPainter(this);

    frame->loadFromData((unsigned char *)pp,/*len*/720*576 * 3 * sizeof(char));


	//缂╂斁鏄剧ず

	//IgnoreAspectRatio是自由伸缩，KeepAspectRatio是等比例伸缩
	*imgScaled=frame->scaled(640,416,Qt::IgnoreAspectRatio);

    label->setPixmap(QPixmap::fromImage(*imgScaled,Qt::AutoColor));

}

