
#ifndef GLViewWIDGET_H
#define GLViewWIDGET_H

#include <QTime>
#include <QGLWidget>
#include <QVector3D>
#include "qglpainter.h"

class GLViewWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLViewWidget(QWidget *parent = 0, bool inde=false);//构造函数，初始化类
	~GLViewWidget();								   //析构函数，释放内存空间
    QGLCamera *camera() const;						   //设置摄像头函数，返回指针 （加const为了防止修改成员变量或调用非const成员函数）

	void autoRotate(QRect &rect);                      //自动旋转函数
	bool autoRotate() const{return m_autorotate;}		//判断是否启动自动旋转
	void setAutoRotate(bool autorotate){m_autorotate=autorotate;}//设置是否自动旋转
	virtual void resetAutoRotate(){setAutoRotate(true);}		//设置为自动旋转

	QPointF eyeXY() const{return camera()->eye().toPointF();}//返回摄像头的XY坐标？
	
	void setEyeXY(QPointF eye);		//设置摄像头的XY坐标？
	virtual void resetEyeXY();		//摄像头坐标归位？
	qreal eyeZ() const{return camera()->eye().z();}//返回摄像头的Z坐标？
	void setEyeZ(qreal eyeZ);		//设置摄像头的Z坐标
	virtual void resetEyeZ();		//摄像头的Z坐标归位？

	QPointF eyeCenterXY() const{return camera()->center().toPointF();}//返回摄像头对准点XY方向向量？
	void setEyeCenterXY(QPointF eye);								  //设置摄像头对准点的XY方向向量？
	virtual void resetEyeCenterXY();								  //归位摄像头对准点的XY方向的向量
	qreal eyeCenterZ() const{return camera()->center().z();}		  //返回摄像头对准点的Z方向
	void setEyeCenterZ(qreal eyeZ);									  //设置摄像头对准点的Z方向
	virtual void resetEyeCenterZ();								      //归位摄像头对准点的Z方向？

	qreal angle() const;                                              //获取车厢角度
	virtual void setAngle(qreal a);									  //设置车厢角度
	virtual void resetAngle(){setAngle(0);}							  //归位车厢角度

	int rotInterval() const{return m_rotinterval;}					  //获取自动选装的间隔度数
	//void setRotInterval(int interval);							  //设置自动旋转的间隔度数
	//virtual void resetRotInterval(){setRotInterval(100);}			  //归位间隔度数为100度？
	

	qreal rotepX() const{return m_rotepX;}							  //获取旋转方向的X向量?
	void setRotepX(qreal a){m_rotepX = a;}						  	  //设置旋转方向的X向量？
	virtual void resetRotepX(){setRotepX(0);}						  //归位旋转方向的X向量
	qreal rotepY() const{return m_rotepY;}
	void setRotepY(qreal a){m_rotepY = a;}
	virtual void resetRotepY(){setRotepY(1);}
	qreal rotepZ() const{return m_rotepZ;}
	void setRotepZ(qreal a){m_rotepZ = a;}
	virtual void resetRotepZ(){setRotepZ(0);}

public Q_SLOTS:														//以下定义槽函数
    void cameraChanged();											//摄像头位置改变的函数
	void moveView(QVector3D delta);									//视野移动
	void scaleView(qreal scale);									//视野缩放
	void rorateView(qreal anglex, qreal angley, qreal anglez);		//视野旋转
	//void start();	//start rotate
	//void stop();

protected:
	//void timerEvent(QTimerEvent *event);
	//void showEvent (QShowEvent*);

	bool m_indesigner;		//是否在绘制中？
	bool m_autorotate;		//是否自动旋转
	int m_timerid;			//定时器参数？？？
	int m_rotinterval;		//旋转间隔（度数）
	qreal m_rotepX;			//绕x轴旋转的度数
	qreal m_rotepY;			//绕y轴旋转的度数
	qreal m_rotepZ;			//绕z轴旋转的度数

protected:
	void initializeGL();	//初始化GL
	void paintGL();			//GL重绘

	virtual void resizeGL(int w, int h);          	//	GL窗口变化时发生
    virtual void initializeGL(QGLPainter *painter); //
    virtual void earlyPaintGL(QGLPainter *painter);
    virtual void paintGL(QGLPainter *painter) = 0;

private:
    QGLCamera *m_camera;	//定义一个私有的摄像头类

};

#endif
