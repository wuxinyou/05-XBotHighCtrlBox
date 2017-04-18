#include <QtGui>
#include "model.h"
#include <math.h>
#define DEFAULT_EYEX		3
#define DEFAULT_EYEY		0
#define DEFAULT_EYEZ		0

//#define DEFAULT_EYEX		1
//#define DEFAULT_EYEY		3
//#define DEFAULT_EYEZ		0.5

#define DEFAULT_EYE_CENTERX	0
#define DEFAULT_EYE_CENTERY	0
#define DEFAULT_EYE_CENTERZ	0

#define ROTATE_DB 	QVector3D(0,0.133,0.2537)
#define ROTATE_DBXZ QVector3D(0,0,0.2537)
#define ROTATE_XB 	QVector3D(0,0.133,0.8037)
#define ROTATE_SW 	QVector3D(0,0.14556,1.30369)
#define ROTATE_YT 	QVector3D(0,0.16056,0.84269)
#define ROTATE_YTXZ QVector3D(0.0335,0,0.84269)
#define ROTATE_SWXZ QVector3D(0.01550,0.14556,0)
#define ROTATE_SZZ1 QVector3D(0.0345,0,1.41319)
#define ROTATE_SZY1 QVector3D(-0.0035,0,1.41319)
#define ROTATE_ZB   QVector3D(0, 0, 0.247)
#define DIRECTION_X QVector3D(1,0,0)
#define DIRECTION_Y QVector3D(0,1,0)
#define DIRECTION_Z QVector3D(0,0,1)








mymodel::mymodel(QWidget *parent, bool inde) : GLViewWidget(parent, inde)
{


	dipan=NULL;
	zhibi=NULL;
	dabi=NULL;
	dabixuanzhuan=NULL;
	qianjinxiangji=NULL;
	xiaobi=NULL;
	shouwan=NULL;
	shouzhuaxuanzhuan=NULL;
	shouzhua1=NULL;

	shouzhua2=NULL;

	yuntaifuyan=NULL;
	yuntaixuanzhuan=NULL;
	
	focalLength=3.0f;
	resetEyeCenterXY();
	resetEyeCenterZ();
	updateview_xz(1.0);
	updateview_y(0.6);

	zhibiRot.setAxis(DIRECTION_X);
	zhibiRot.setOrigin(ROTATE_ZB);
	
	//dipanRot.setAxis(DIRECTION_Y);
	//dipanRot.setOrigin(ROTATE_DB);
	
	dabiRot.setAxis(DIRECTION_X);
	dabiRot.setOrigin(ROTATE_DB);
	
	dabixuanzhuanRot.setAxis(DIRECTION_Y);
	dabixuanzhuanRot.setOrigin(ROTATE_DBXZ);
	
	qianjinxiangjiRot.setAxis(DIRECTION_X);
	qianjinxiangjiRot.setOrigin(ROTATE_DB);
	
	xiaobiRot.setAxis(DIRECTION_X);
	xiaobiRot.setOrigin(ROTATE_XB);
	
	shouwanRot.setAxis(DIRECTION_X);
	shouwanRot.setOrigin(ROTATE_SW);
	
	shouzhuaxuanzhuanRot.setAxis(DIRECTION_Z);
	shouzhuaxuanzhuanRot.setOrigin(ROTATE_SWXZ);
	
	shouzhua1Rot.setAxis(DIRECTION_Y);
	shouzhua1Rot.setOrigin(ROTATE_SZZ1);
	
	shouzhua2Rot.setAxis(DIRECTION_Y);
	shouzhua2Rot.setOrigin(ROTATE_SZY1);
	
	yuntaifuyanRot.setAxis(DIRECTION_X);
	yuntaifuyanRot.setOrigin(ROTATE_YT);
	
	yuntaixuanzhuanRot.setAxis(DIRECTION_Y);
	yuntaixuanzhuanRot.setOrigin(ROTATE_YTXZ);
	
	//camera()->setEye(QVector3D(0,3,0));
	//connect(this, SIGNAL(sendxz(double)), this, SLOT( updateview_xz(double)) );
	//connect(this, SIGNAL(sendy(double)), this, SLOT( updateview_y(double)) );	
}

mymodel::~mymodel()												//析构函数 释放空间
{
	if(dipan)
		delete dipan;

	if(zhibi)
		delete zhibi;
	
	if(dabi)
		delete dabi;
	
	if(dabixuanzhuan)
		delete dabixuanzhuan;
	
	if(qianjinxiangji)
		delete qianjinxiangji;
	
	if(xiaobi)
		delete xiaobi;
	
	if(shouwan)
		delete shouwan;
	
	if(shouzhuaxuanzhuan)
		delete shouzhuaxuanzhuan;
	
	if(shouzhua1)
		delete shouzhua1;
	
	if(shouzhua2)
		delete shouzhua2;
	
	if(yuntaifuyan)
		delete yuntaifuyan;
	
	if(yuntaixuanzhuan)
		delete yuntaixuanzhuan;
}

void mymodel::resetEyeXY()										//重置摄像机的XY 坐标
{
	setEyeXY(QPointF(DEFAULT_EYEX,DEFAULT_EYEY));
}

void mymodel::resetEyeZ()										//重置摄像机的Z坐标
{
	setEyeZ(DEFAULT_EYEZ);
}

void mymodel::resetEyeCenterXY()								//重置视点的XY坐标
{
	setEyeCenterXY(QPointF(DEFAULT_EYE_CENTERX,DEFAULT_EYE_CENTERY));
}

void mymodel::resetEyeCenterZ()									//重置视点的Z坐标
{
	setEyeCenterZ(DEFAULT_EYE_CENTERZ);
}

void mymodel::reset()									//重置此类的所有方法和属性？不明白为什么有这个？？？？？？？？？？？
{
	int i;
	for(i=0; i<metaObject()->propertyCount(); i++){		//QMetaObject * QObject::metaObject () const 
														//返回这个对象的元对象的指针。 元对象包含关于一个继承QObject的类的一些信息，比如，类名称、超类名称、属性、信号和槽。
		metaObject()->property(i).reset(this);			//重置本类的所有属性和方法等?
	}
}
void mymodel::zhibiPitch(int angle) 					//支臂俯仰
{
	//angle = qBound(0, angle, 360);					//设置角度的范围 为0~360 度
	zhibiRot.setAngle((qreal)angle);
	update();
}
void mymodel::dabiPitch(int angle)				//大臂俯仰
{
	//angle = qBound(0, angle, 360);					//设置角度的范围 为0~360 度
	dabiRot.setAngle((qreal)angle);	
	update();										//更新场景（3D模型）
}


void mymodel::dabiRotate(int angle)					//大臂旋转
{
	//angle = qBound(0, angle, 360);					//设置角度的范围 为0~360 度
	dabixuanzhuanRot.setAngle((qreal)angle);	
	update();
}

void mymodel::xiaobiPitch(int angle)				//小臂俯仰
{
	//angle = qBound(0, angle, 360);					//设置角度的范围 为0~360 度
	xiaobiRot.setAngle((qreal)angle);	
	update();
}
	
void mymodel::yuntaiPitch(int angle)				//云台俯仰
{
	//angle = qBound(0, angle, 360);					//设置角度的范围 为0~360 度
	yuntaifuyanRot.setAngle((qreal)angle);
	update();
}
void mymodel::yuntaiRotate(int angle)				//云台旋转
{
	//angle = qBound(0, angle, 360);					//设置角度的范围 为0~360 度
	yuntaixuanzhuanRot.setAngle((qreal)angle);	
	update();
}
void mymodel::shouwanPitch(int angle)				//手腕俯仰
{
	//angle = qBound(0, angle, 360);					//设置角度的范围 为0~360 度
	shouwanRot.setAngle((qreal)angle);	
	update();		
}
void mymodel::shouwanRotate(int angle)				//手腕旋转
{
	//angle = qBound(0, angle, 360);					//设置角度的范围 为0~20 度
	shouzhuaxuanzhuanRot.setAngle((qreal)angle);	
	update();		
}
void mymodel::qianjinxiangjiPitch(int angle)		//前进相机俯仰
{
	//angle = qBound(0, angle, 360);					//设置角度的范围 为0~20 度
	qianjinxiangjiRot.setAngle((qreal)angle);	
	update();		
}	

void mymodel::shouzhuaMediate(int angle)			//手抓捏合
{

	//angle = qBound(0, angle, 360);					//设置角度的范围 为0~360 度
	shouzhua2Rot.setAngle((qreal)(-angle));
	shouzhua1Rot.setAngle((qreal)angle);
	update();		
}

void mymodel::initializeGL (QGLPainter *painter)	//初始化GL
{
	Q_UNUSED(painter);								//避免编译器警告
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);				//用指定的颜色和透明度来清理背景05172f
	//glClearColor(0.019f, 0.067f, 0.184f, 1.0f);				//用指定的颜色和透明度来清理背景
	
	dipan = QGLAbstractScene::loadScene(QLatin1String("data/dipan.3DS")); //读取3DS文件 赋值给m_bodyscene  INFINITI_TRIANT_3ds_hi.3ds HumanLike_body.3DS
	if(dipan)
		dipanNode = dipan->mainNode();												//获取场景的主网格节点
	else
		QMessageBox::information(this, "", "failed load 1 file");

	zhibi = QGLAbstractScene::loadScene(QLatin1String("data/zhibi.3DS"));
	if(zhibi)
		zhibiNode = zhibi->mainNode();
	else
		QMessageBox::information(this, "", "failed load 2 file");

	dabi = QGLAbstractScene::loadScene(QLatin1String("data/dabi.3DS"));
	if(dabi)
		dabiNode = dabi->mainNode();
	else
		QMessageBox::information(this, "", "failed load 3 file");
		
	dabixuanzhuan = QGLAbstractScene::loadScene(QLatin1String("data/dabixuanzhuan.3DS"));
	if(dabixuanzhuan)
		dabixuanzhuanNode = dabixuanzhuan->mainNode();
	else
		QMessageBox::information(this, "", "failed load 4 file");		
		
	qianjinxiangji = QGLAbstractScene::loadScene(QLatin1String("data/xiangji.3DS"));
	if(qianjinxiangji)
		qianjinxiangjiNode = qianjinxiangji->mainNode();
	else
		QMessageBox::information(this, "", "failed load 5 file");

	xiaobi = QGLAbstractScene::loadScene(QLatin1String("data/xiaobi.3DS"));
	if(xiaobi)
		xiaobiNode = xiaobi->mainNode();
	else
		QMessageBox::information(this, "", "failed load 6 file");

	shouwan = QGLAbstractScene::loadScene(QLatin1String("data/shouwan.3DS"));
	if(shouwan)
		shouwanNode = shouwan->mainNode();
	else
		QMessageBox::information(this, "", "failed load 7 file");

	shouzhuaxuanzhuan = QGLAbstractScene::loadScene(QLatin1String("data/shouzhuaxuanzhuan.3DS"));
	if(shouzhuaxuanzhuan)
		shouzhuaxuanzhuanNode = shouzhuaxuanzhuan->mainNode();
	else
		QMessageBox::information(this, "", "failed load 8 file");

	shouzhua1 = QGLAbstractScene::loadScene(QLatin1String("data/shouzhua1.3DS"));
	if(shouzhua1)
		shouzhua1Node = shouzhua1->mainNode();
	else
		QMessageBox::information(this, "", "failed load 9 file");

		
	shouzhua2 = QGLAbstractScene::loadScene(QLatin1String("data/shouzhua2.3DS"));
	if(shouzhua2)
		shouzhua2Node = shouzhua2->mainNode();
	else
		QMessageBox::information(this, "", "failed load 10 file");		
			
	yuntaifuyan = QGLAbstractScene::loadScene(QLatin1String("data/yuntai.3DS"));
	if(yuntaifuyan)
		yuntaifuyanNode = yuntaifuyan->mainNode();
	else
		QMessageBox::information(this, "", "failed load 11 file");		
		
	yuntaixuanzhuan = QGLAbstractScene::loadScene(QLatin1String("data/yuntaixuanzhuan.3DS"));
	if(yuntaixuanzhuan)
		yuntaixuanzhuanNode = yuntaixuanzhuan->mainNode();
	else
		QMessageBox::information(this, "", "failed load 12 file");

	
	//dipan = QGLAbstractScene::loadScene(QLatin1String("/data/run/dipan.3DS")); //读取3DS文件 赋值给m_bodyscene  INFINITI_TRIANT_3ds_hi.3ds HumanLike_body.3DS
	//if(dipan)
		//dipanNode = dipan->mainNode();												//获取场景的主网格节点
	//else
		//QMessageBox::information(this, "", "failed load 1 file");

	//zhibi = QGLAbstractScene::loadScene(QLatin1String("/data/run/zhibi.3DS"));
	//if(zhibi)
		//zhibiNode = zhibi->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 2 file");

	//dabi = QGLAbstractScene::loadScene(QLatin1String("/data/run/dabi.3DS"));
	//if(dabi)
		//dabiNode = dabi->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 3 file");
		//
	//dabixuanzhuan = QGLAbstractScene::loadScene(QLatin1String("/data/run/dabixuanzhuan.3DS"));
	//if(dabixuanzhuan)
		//dabixuanzhuanNode = dabixuanzhuan->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 4 file");		
		//
	//qianjinxiangji = QGLAbstractScene::loadScene(QLatin1String("/data/run/xiangji.3DS"));
	//if(qianjinxiangji)
		//qianjinxiangjiNode = qianjinxiangji->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 5 file");

	//xiaobi = QGLAbstractScene::loadScene(QLatin1String("/data/run/xiaobi.3DS"));
	//if(xiaobi)
		//xiaobiNode = xiaobi->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 6 file");

	//shouwan = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouwan.3DS"));
	//if(shouwan)
		//shouwanNode = shouwan->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 7 file");

	//shouzhuaxuanzhuan = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouzhuaxuanzhuan.3DS"));
	//if(shouzhuaxuanzhuan)
		//shouzhuaxuanzhuanNode = shouzhuaxuanzhuan->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 8 file");

	//shouzhua1 = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouzhua1.3DS"));
	//if(shouzhua1)
		//shouzhua1Node = shouzhua1->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 9 file");

		//
	//shouzhua2 = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouzhua2.3DS"));
	//if(shouzhua2)
		//shouzhua2Node = shouzhua2->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 10 file");		
			//
	//yuntaifuyan = QGLAbstractScene::loadScene(QLatin1String("/data/run/yuntai.3DS"));
	//if(yuntaifuyan)
		//yuntaifuyanNode = yuntaifuyan->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 11 file");		
		//
	//yuntaixuanzhuan = QGLAbstractScene::loadScene(QLatin1String("/data/run/yuntaixuanzhuan.3DS"));
	//if(yuntaixuanzhuan)
		//yuntaixuanzhuanNode = yuntaixuanzhuan->mainNode();
	//else
		//QMessageBox::information(this, "", "failed load 12 file");	
	//
	//
	
	
	
	
	
	
/*		
	dipan = QGLAbstractScene::loadScene(QLatin1String("/data/run/dipan.3DS")); //读取3DS文件 赋值给m_bodyscene  INFINITI_TRIANT_3ds_hi.3ds HumanLike_body.3DS
	if(dipan)
		dipanNode = dipan->mainNode();												//获取场景的主网格节点
	else
		QMessageBox::information(this, "", "failed load 1 file");

	zhibi = QGLAbstractScene::loadScene(QLatin1String("/data/run/zhibi.3DS"));
	if(zhibi)
		zhibiNode = zhibi->mainNode();
	else
		QMessageBox::information(this, "", "failed load 2 file");

	dabi = QGLAbstractScene::loadScene(QLatin1String("/data/run/dabi.3DS"));
	if(dabi)
		dabiNode = dabi->mainNode();
	else
		QMessageBox::information(this, "", "failed load 3 file");
		
	dabixuanzhuan = QGLAbstractScene::loadScene(QLatin1String("/data/run/dabixuanzhuan.3DS"));
	if(dabixuanzhuan)
		dabixuanzhuanNode = dabixuanzhuan->mainNode();
	else
		QMessageBox::information(this, "", "failed load 4 file");		
		
	qianjinxiangji = QGLAbstractScene::loadScene(QLatin1String("/data/run/qianjinxiangji.3DS"));
	if(qianjinxiangji)
		qianjinxiangjiNode = qianjinxiangji->mainNode();
	else
		QMessageBox::information(this, "", "failed load 5 file");

	xiaobi = QGLAbstractScene::loadScene(QLatin1String("/data/run/xiaobi.3DS"));
	if(xiaobi)
		xiaobiNode = xiaobi->mainNode();
	else
		QMessageBox::information(this, "", "failed load 6 file");

	shouwan = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouwan.3DS"));
	if(shouwan)
		shouwanNode = shouwan->mainNode();
	else
		QMessageBox::information(this, "", "failed load 7 file");

	shouzhuaxuanzhuan = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouzhuaxuanzhuan.3DS"));
	if(shouzhuaxuanzhuan)
		shouzhuaxuanzhuanNode = shouzhuaxuanzhuan->mainNode();
	else
		QMessageBox::information(this, "", "failed load 8 file");

	shouzhua11 = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouzhua11.3DS"));
	if(shouzhua11)
		shouzhua11Node = shouzhua11->mainNode();
	else
		QMessageBox::information(this, "", "failed load 9 file");

	shouzhua12 = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouzhua12.3DS"));
	if(shouzhua12)
		shouzhua12Node = shouzhua12->mainNode();
	else
		QMessageBox::information(this, "", "failed load 10 file");
		
	shouzhua13 = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouzhua13.3DS"));
	if(shouzhua13)
		shouzhua13Node = shouzhua13->mainNode();
	else
		QMessageBox::information(this, "", "failed load 11 file");		
		
	shouzhua21 = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouzhua21.3DS"));
	if(shouzhua21)
		shouzhua21Node = shouzhua21->mainNode();
	else
		QMessageBox::information(this, "", "failed load 12 file");		
		
	shouzhua22 = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouzhua22.3DS"));
	if(shouzhua22)
		shouzhua22Node = shouzhua22->mainNode();
	else
		QMessageBox::information(this, "", "failed load 13 file");		
		
	shouzhua23 = QGLAbstractScene::loadScene(QLatin1String("/data/run/shouzhua23.3DS"));
	if(shouzhua23)
		shouzhua23Node = shouzhua23->mainNode();
	else
		QMessageBox::information(this, "", "failed load 14 file");		
		
	gaizi = QGLAbstractScene::loadScene(QLatin1String("/data/run/gaizi.3DS"));
	if(gaizi)
		gaiziNode = gaizi->mainNode();
	else
		QMessageBox::information(this, "", "failed load 15 file");		
		
	yuntaifuyan = QGLAbstractScene::loadScene(QLatin1String("/data/run/yuntaifuyan.3DS"));
	if(yuntaifuyan)
		yuntaifuyanNode = yuntaifuyan->mainNode();
	else
		QMessageBox::information(this, "", "failed load 16 file");		
		
	yuntaixuanzhuan = QGLAbstractScene::loadScene(QLatin1String("/data/run/yuntaixuanzhuan.3DS"));
	if(yuntaixuanzhuan)
		yuntaixuanzhuanNode = yuntaixuanzhuan->mainNode();
	else
		QMessageBox::information(this, "", "failed load 17 file");		
	
*/
				
	if(dipanNode)
		dipanNode->addTransform(&dipanRot);
						
	if(zhibiNode)
		zhibiNode->addTransform(&zhibiRot);
						
	if(dabiNode)
	{
		dabiNode->addTransform(&dabiRot);
		dabiNode->addTransform(&dabixuanzhuanRot);
	}

	if(dabixuanzhuanNode)
	{
		dabixuanzhuanNode->addTransform(&dabixuanzhuanRot);
	}

	if(qianjinxiangjiNode)
	{
		qianjinxiangjiNode->addTransform(&qianjinxiangjiRot);
		qianjinxiangjiNode->addTransform(&dabixuanzhuanRot);		
	}

	if(xiaobiNode)
	{
		xiaobiNode->addTransform(&xiaobiRot);
		xiaobiNode->addTransform(&dabiRot);
		xiaobiNode->addTransform(&dabixuanzhuanRot);		
	}

	if(shouwanNode)
	{
		shouwanNode->addTransform(&shouwanRot);	
		shouwanNode->addTransform(&xiaobiRot);
		shouwanNode->addTransform(&dabiRot);
		shouwanNode->addTransform(&dabixuanzhuanRot);		
	}

	if(shouzhuaxuanzhuanNode)
	{
		shouzhuaxuanzhuanNode->addTransform(&shouzhuaxuanzhuanRot);
		shouzhuaxuanzhuanNode->addTransform(&shouwanRot);	
		shouzhuaxuanzhuanNode->addTransform(&xiaobiRot);
		shouzhuaxuanzhuanNode->addTransform(&dabiRot);
		shouzhuaxuanzhuanNode->addTransform(&dabixuanzhuanRot);	
	}

	if(shouzhua1Node)
	{
		shouzhua1Node->addTransform(&shouzhua1Rot);
		shouzhua1Node->addTransform(&shouzhuaxuanzhuanRot);
		shouzhua1Node->addTransform(&shouwanRot);	
		shouzhua1Node->addTransform(&xiaobiRot);
		shouzhua1Node->addTransform(&dabiRot);
		shouzhua1Node->addTransform(&dabixuanzhuanRot);	
	}

	if(shouzhua2Node)
	{
		shouzhua2Node->addTransform(&shouzhua2Rot);	
		shouzhua2Node->addTransform(&shouzhuaxuanzhuanRot);
		shouzhua2Node->addTransform(&shouwanRot);	
		shouzhua2Node->addTransform(&xiaobiRot);
		shouzhua2Node->addTransform(&dabiRot);
		shouzhua2Node->addTransform(&dabixuanzhuanRot);	
	}

	if(yuntaifuyanNode)
	{
		yuntaifuyanNode->addTransform(&yuntaifuyanRot);
		yuntaifuyanNode->addTransform(&shouwanRot);	
		yuntaifuyanNode->addTransform(&xiaobiRot);
		yuntaifuyanNode->addTransform(&dabiRot);
		yuntaifuyanNode->addTransform(&dabixuanzhuanRot);
	}

	if(yuntaixuanzhuanNode)
	{
		yuntaixuanzhuanNode->addTransform(&yuntaixuanzhuanRot);		
		yuntaixuanzhuanNode->addTransform(&yuntaifuyanRot);
		yuntaixuanzhuanNode->addTransform(&shouwanRot);	
		yuntaixuanzhuanNode->addTransform(&xiaobiRot);
		yuntaixuanzhuanNode->addTransform(&dabiRot);
		yuntaixuanzhuanNode->addTransform(&dabixuanzhuanRot);
	}
}
void mymodel::updateview_xz(double v_angle)								
{
	if(v_angle>6.28)
    	v_angle-=6.28;
   	if(v_angle<-6.28)
   		v_angle+=6.28;
	float initx=focalLength*cos(hAngle)*sin(v_angle);
	float initz=focalLength*cos(hAngle)*cos(v_angle);
	float inity=focalLength*sin(hAngle);
	QVector3D pos;
	pos = QVector3D(initx,inity,initz);
	camera()->setEye(pos);
	vAngle=v_angle;
}

void mymodel::updateview_y(double h_angle)							
{
	if(h_angle<-1.57)
    	h_angle=-1.57;
   	if(h_angle>1.57)
   		h_angle=1.57;
	float initx=focalLength*cos(h_angle)*sin(vAngle);
	float initz=focalLength*cos(h_angle)*cos(vAngle);
	float inity=focalLength*sin(h_angle);
	QVector3D pos;
	pos = QVector3D(initx,inity,initz);
	camera()->setEye(pos);
	hAngle=h_angle;
}
double mymodel::getfocalLength()
{
	return focalLength;
}
void mymodel::updatesize(double size)
{
	focalLength=size;
	float initx=focalLength*cos(hAngle)*sin(vAngle);
	float initz=focalLength*cos(hAngle)*cos(vAngle);
	float inity=focalLength*sin(hAngle);
	QVector3D pos;
	pos = QVector3D(initx,inity,initz);
	camera()->setEye(pos);
}
void mymodel::paintGL(QGLPainter* painter)						//gl重画				
{

	if(!dipanNode||!zhibiNode || !dabiNode || !dabixuanzhuanNode || !qianjinxiangjiNode || !xiaobiNode || !shouwanNode || !shouzhuaxuanzhuanNode
	 || !shouzhua1Node || !shouzhua2Node || !yuntaifuyanNode 
	|| !yuntaixuanzhuanNode)
		return;

	dipanNode				->draw(painter);
	zhibiNode				->draw(painter);
	dabiNode				->draw(painter);
	dabixuanzhuanNode		->draw(painter);
	qianjinxiangjiNode		->draw(painter);
	xiaobiNode				->draw(painter);
	shouwanNode				->draw(painter);
	shouzhuaxuanzhuanNode	->draw(painter);
	shouzhua1Node			->draw(painter);

	shouzhua2Node			->draw(painter);

	yuntaifuyanNode			->draw(painter);
	yuntaixuanzhuanNode		->draw(painter);

}
void mymodel::mouseMoveEvent(QMouseEvent *e)
{
	if (!(e->buttons() & Qt::LeftButton))
    return;
    pos0 = e->globalPos();
    QPoint upleft = pos0 - last;
    double v_angle,h_angle;
    v_angle=VA-2*((double)upleft.x()/width());
    h_angle=HA+2*((double)upleft.y()/height());
	updateview_xz(v_angle);
	updateview_y(h_angle);
}
void mymodel::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
	    last = e->globalPos();
	    VA=vAngle;
		HA=hAngle;	
	}
}
void mymodel::wheelEvent(QWheelEvent *e)
{
	double numDegrees = (double)(e->delta()) / 1000;
	double l=getfocalLength()+numDegrees;
	if(l>1.5&&l<8)
		updatesize(l);
}