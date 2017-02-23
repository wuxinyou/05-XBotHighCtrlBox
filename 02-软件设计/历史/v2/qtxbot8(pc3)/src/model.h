#ifndef __MODEL_H__
#define __MODEL_H__
#include <QTime>
//#include <QGLWidget>
#include <qgraphicsrotation3d.h>
#include <qglabstractscene.h>
//#include <QVector3D>
#include "glviewwidget.h"

class mymodel: public GLViewWidget
{
 Q_OBJECT
 public:
 
 	QPoint last,pos0;
 	
	mymodel(QWidget *parent = 0, bool inde=false);			//构造函数
	~mymodel();												//析构函数
	void reset();											//重新设置？
	int boxAngle() const{return -zhibiRot.angle();}			//获取车厢的角度
	//void resetBoxAngle(){setBoxAngle(0);}					//车厢的角度归零
	void resetEyeXY();										//归位摄像头的XY位置
	void resetEyeZ();										//归位摄像头的Z位置
	void resetEyeCenterXY();								//归位视点XY坐标
	void resetEyeCenterZ();									//归位视点的Z坐标
	virtual void resetAngle(){setAngle(45);}				//设置车厢的倾斜角度为45°
	double getangle_v(void)
	{
		return vAngle;
	}
	double getangle_h(void)
	{
		return hAngle;
	}	
public Q_SLOTS:
	double getfocalLength(void);

	void dabiPitch(int angle);					//大臂俯仰
	void dabiRotate(int angle);					//大臂旋转
	
	void xiaobiPitch(int angle);				//小臂俯仰
	
	void yuntaiPitch(int angle);				//云台俯仰
	void yuntaiRotate(int angle);				//云台旋转
	
	void shouwanPitch(int angle);				//手腕俯仰
	void shouwanRotate(int angle);				//手腕旋转
	
	void zhibiPitch(int angle);					//支臂俯仰
	
	void qianjinxiangjiPitch(int angle);		//前进相机俯仰

	void shouzhuaMediate(int angle);			//手抓捏合

	void updateview_xz(double x); 								//槽函数，设置场景的X轴旋转角度
	void updateview_y(double y);
	void updatesize(double size);

protected:
	void initializeGL(QGLPainter* painter);					//初始化GL
	void paintGL(QGLPainter* painter);						//GL重画
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	//void paintEvent(QPaintEvent *event);
	void wheelEvent(QWheelEvent *e);
private:
	QGraphicsRotation3D dipanRot; 
	QGraphicsRotation3D zhibiRot;															
	QGraphicsRotation3D dabiRot;
	QGraphicsRotation3D dabixuanzhuanRot;
	QGraphicsRotation3D qianjinxiangjiRot;
	QGraphicsRotation3D xiaobiRot;
	QGraphicsRotation3D shouwanRot;
	QGraphicsRotation3D shouzhuaxuanzhuanRot;
	QGraphicsRotation3D shouzhua1Rot;

	QGraphicsRotation3D shouzhua2Rot;

	QGraphicsRotation3D yuntaifuyanRot;
	QGraphicsRotation3D yuntaixuanzhuanRot;//
	
	
	QGLAbstractScene *dipan;							//存储车体 QGLAbstractScene类表示的由零个或多个QGLSceneNode组成的3 D场景？
	QGLAbstractScene *zhibi;
	QGLAbstractScene *dabi;
	QGLAbstractScene *dabixuanzhuan;
	QGLAbstractScene *qianjinxiangji;
	QGLAbstractScene *xiaobi;
	QGLAbstractScene *shouwan;
	QGLAbstractScene *shouzhuaxuanzhuan;
	QGLAbstractScene *shouzhua1;

	QGLAbstractScene *shouzhua2;

	QGLAbstractScene *yuntaifuyan;
	QGLAbstractScene *yuntaixuanzhuan;
	
	QGLSceneNode *dipanNode;								//车体 的网格节点？
	QGLSceneNode *zhibiNode;								//车厢 的网格节点？
	QGLSceneNode *dabiNode;
	QGLSceneNode *dabixuanzhuanNode;
	QGLSceneNode *qianjinxiangjiNode;
	QGLSceneNode *xiaobiNode;
	QGLSceneNode *shouwanNode;
	QGLSceneNode *shouzhuaxuanzhuanNode;
	QGLSceneNode *shouzhua1Node;

	QGLSceneNode *shouzhua2Node;

	QGLSceneNode *yuntaifuyanNode;
	QGLSceneNode *yuntaixuanzhuanNode;

	double  hAngle;												//球面坐标经度备份
	double  vAngle;												//球面坐标的纬度备份
	double focalLength;										//焦距 即球的直径
	double  VA;												//球面坐标经度
	double  HA;												//球面坐标的纬度
												
	
	
};














#endif // __MODEL_H__
