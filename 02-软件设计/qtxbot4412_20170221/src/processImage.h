/********************************************************************************
概述：processImage.cpp实现图像显示，调用YUV2RGBThread线程
作者：吴新有
日期：2017-01-11
备注：processImage.cpp调用YUV2RGBThread类，实现图像的采集和转换
********************************************************************************/

#ifndef PROCESSIMAGE_H
#define PROCESSIMAGE_H

#include <QtGui>
#include "YUV2RGBThread.h"


//在需要改变摄像头窗口大小时，只需要修改下面两个参数即可。
//实际上只需要修改Label的尺寸即可，不然会出现转码出错，导致没有图像。
#define Win_width  682
#define Win_height 430

class ProcessImage : public QWidget
{
    Q_OBJECT
public:
    ProcessImage(QWidget *parent=0);
    ~ProcessImage();

private:
    QPainter *painter;
    QLabel *label;
    QImage *frame;
	QImage* imgScaled;
    //QPixmap *frame;
    QTimer *timer;
	YUV2RGBThread * cameraThread;
	//unsigned char image[width*height*2];
	uchar *pp;


private slots:
    void paintEvent(QPaintEvent *);



};

#endif
