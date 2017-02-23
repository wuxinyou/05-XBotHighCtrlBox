#include <QPainter>
#include <QPaintEngine>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <qgraphicsscale3d.h>
#include "glviewwidget.h"
#include <math.h>

GLViewWidget::GLViewWidget(QWidget *parent, bool inde)
	:QGLWidget(parent)
{
	m_indesigner = inde;//是否在绘制中？

	m_camera = new QGLCamera(parent);//实例化摄像头类
	m_rotinterval = 0;				 //设置旋转间隔（度数）为0
	m_timerid = 0;					 //定时时间为0

	QObject::connect(m_camera, SIGNAL(projectionChanged()),
		this, SLOT(cameraChanged()));					//设置信号和槽，信号：投影改变
	QObject::connect(m_camera, SIGNAL(viewChanged()),
		this, SLOT(cameraChanged()));					//设置信号和槽，信号：视野改变
}

GLViewWidget::~GLViewWidget() //析构函数,构造函数里面没任何NEW 
{
	//stop();
}

void GLViewWidget::setEyeXY(QPointF eye)//设置摄像头xy坐标
{
	QVector3D pos;						//定义三维坐标？
	pos = QVector3D(eye);				//参数传递，强制类型转换
	pos.setZ(camera()->eye().z());		//Z保留
	camera()->setEye(pos);				//设置
}

void GLViewWidget::setEyeZ(qreal eyeZ)	//设置摄像头位置的z坐标？
{
	QVector3D pos;					  	//定义三维坐标？
	pos = QVector3D(camera()->eye().toVector2D(),eyeZ);		//保留XY
	camera()->setEye(pos);				//设置
}

void GLViewWidget::setEyeCenterXY(QPointF eye)//设置视点xy 
{
	QVector3D pos;
	pos = QVector3D(eye);
	pos.setZ(camera()->center().z());
	camera()->setCenter(pos);
}

void GLViewWidget::setEyeCenterZ(qreal eyeZ)//设置视点z
{
	QVector3D pos;
	pos = QVector3D(camera()->center().toVector2D(),eyeZ);
	camera()->setCenter(pos);
}

void GLViewWidget::resetEyeXY() //归位摄像头？
{
	setEyeXY(QPointF(0,0));
}

void GLViewWidget::resetEyeZ()
{
	setEyeZ(0);
}

void GLViewWidget::resetEyeCenterXY()
{
	setEyeCenterXY(QPointF(0,0));
}

void GLViewWidget::resetEyeCenterZ()
{
	setEyeCenterZ(0);
}

//void GLViewWidget::showEvent ( QShowEvent * )
//{
	//if(m_autorotate && !m_indesigner)
		//start();
//}

//void GLViewWidget::start()
//{
	//m_timerid = startTimer(m_rotinterval);
//}

//void GLViewWidget::stop()
//{
	//if(m_timerid){
		//killTimer(m_timerid);
		//m_timerid=0;
	//}
//}

//void GLViewWidget::setRotInterval(int interval)
//{
	//m_rotinterval = interval;
	//if(m_timerid){
		//stop();
		//start();
	//}
//}

//void GLViewWidget::timerEvent(QTimerEvent *event)
//{
	//if(m_timerid!=event->timerId())
		//return;

	//rorateView(m_rotepX, m_rotepY, m_rotepZ);
//}

#define PI 3.14159265

qreal GLViewWidget::angle() const
{
	//rotate around y axis,  angle=acrtan(z/x)
	return atan2(m_camera->eye().x(), m_camera->eye().z())*180/PI;
}

void GLViewWidget::setAngle(qreal a)
{
	rorateView(0, a-angle(), 0);
}

void GLViewWidget::cameraChanged()
{
	// Queue an update for the next event loop.
	update();
}

QGLCamera *GLViewWidget::camera() const
{
	return m_camera;
}

void GLViewWidget::initializeGL()
{
	QGLPainter painter;
	painter.begin();

	// Set the default depth buffer options.设置默认的深度缓冲的选择。
	
	glEnable(GL_DEPTH_TEST);//glEnable()和glDisable()是一对功能相反的函数,其中glEnable的作用是打开服务器端的GL功能。
							//glEnable这个函数主要是开启OPENGL的功能，好歹算是个控制枢纽。GL_DEPTH_TEST,表示打开深度测试。
	glDepthFunc(GL_LESS);						//深度小的时候才渲染。
	//glDepthFunc(GL_GREATER  );
	glDepthMask(GL_TRUE);						//深度缓存可写
#if defined(QT_OPENGL_ES)						//条件编译 编译器我交叉编译器则执行下面的函数（与x和y窗口坐标不同，在OpenGL中，z坐标总是被认为位于0.0~1.0的范围之间。）
	glDepthRangef(0.0f, 1.0f);	
#else
	glDepthRange(0.0f, 1.0f);  					//本机编译器则执行此函数
#endif

	// Set the default blend options. 设置默认的混合选项。
	if (painter.hasOpenGLFeature(QOpenGLFunctions::BlendColor))
		painter.glBlendColor(0, 0, 0, 0);//颜色混合？
		
		
		
//大概就是这样：第一个参数指出源图元的alpha的取值计算方法，第二个参数指出目标处的alpha的计算方法。 

//------ 
//我个人理解： 
//两个参数的取值都可以是如下常量之一： 
//GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, and GL_SRC_ALPHA_SATURATE 
//比如GL_ZERO表示alpha取值为0，GL_ONE表示1，GL_DST_COLOR表示取目标区域的颜色值，GL_SRC_ALPHA表示取源区域的alpha值等等。例如： 

//glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
//表示把渲染的图像叠加到目标区域，也就是说源的每一个像素的alpha都等于自己的alpha，目标的每一个像素的alpha等于1。这样叠加次数越多，叠加的图元的alpha越高，得到的结果就越亮。因此这种融合用于表达光亮效果。

//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
//表示把渲染的图像融合到目标区域。也就是说源的每一个像素的alpha都等于自己的alpha，目标的每一个像素的alpha等于1减去该位置源像素的alpha。 因此不论叠加多少次，亮度是不变的。

//如此等等。自己试一试才会明白。 

//这个函数是制作很多特技效果的核心，变幻无穷，我这里说的只是皮毛，要完整地理解就必须看官方文档（MSDN就是一个很全面的文档），英语不好也要硬看，其实谁刚开始看的时候都会头疼，看多了英语自然就练出来了...		
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //表示把渲染的图像融合到目标区域。也就是说源的每一个像素的alpha都等于自己的alpha，目标的每一个像素的alpha等于1减去该位置源像素的alpha。 因此不论叠加多少次，亮度是不变的。
	
	if (painter.hasOpenGLFeature(QOpenGLFunctions::BlendEquation))
		painter.glBlendEquation(GL_FUNC_ADD);//指定混合操作
	else if (painter.hasOpenGLFeature(QOpenGLFunctions::BlendEquationSeparate))
		painter.glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_CULL_FACE);
	
	m_camera-> setFarPlane((qreal)10.0f);
	//m_camera-> setEyeSeparation((qreal)0.01); 
	m_camera-> setNearPlane(qreal(1.0f)); 
	m_camera-> setViewSize(QSizeF(0.4,0.4));
	 
	initializeGL(&painter);

}

void GLViewWidget::paintGL()
{
	// Paint the scene contents.渲染场景的内容。
	QGLPainter painter;
	
	QGLAbstractSurface *surface=NULL;
	//glLoadIdentity();
	painter.begin();

	// No camera separation, so render the same image into both buffers.没有相机分离,因此往两个相同的图像渲染缓冲。

	painter.pushSurface(surface);
	
	painter.setEye(QGL::NoEye);
	
	earlyPaintGL(&painter);
	
	painter.setCamera(m_camera);
	
	//gluPerspective(45,1,0,1000);
	//
	//gluLookAt(0,0,10,0,0,0,0,1,0);

	paintGL(&painter);
	
	painter.popSurface();
}

/*!
	\internal内部
*/
void GLViewWidget::resizeGL(int w, int h)
{
	// Set up the standard viewport for the new window size.建立了新标准视图窗口尺寸。
	int side = qMin(w, h);
	glViewport((w - side) / 2, (h - side) / 2, side, side);
}

/*!
	Initializes the current GL context represented by \a painter.

	\sa paintGL()
*/
void GLViewWidget::initializeGL(QGLPainter *painter)//重载
{
	Q_UNUSED(painter);								//禁止编译器警告
}

/*!
	Performs early painting operations just after \a painter
	is initialized but before the camera is set up.  The default
	implementation clears the color buffer and depth buffer.

	This function is typically overridden to draw scene backdrops
	on the color buffer before the rest of the scene is drawn
	by paintGL().

	\sa paintGL()
*/
void GLViewWidget::earlyPaintGL(QGLPainter *painter)//初步重画GL窗口
{
	Q_UNUSED(painter);								//禁止编译器警告
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void GLViewWidget::moveView(QVector3D delta)		//移动场景，实际上市移动摄像头和视点位置
{
	m_camera->setEye(m_camera->eye() - delta);
	m_camera->setCenter(m_camera->center() - delta);
}

void GLViewWidget::scaleView(qreal scale)//缩放场景
{
/*	qreal fov = m_camera->fieldOfView();
	if (fov != 0.0f)
		m_camera->setFieldOfView(m_camera->fieldOfView() / scale);
	else
		m_camera->setViewSize(m_camera->viewSize() / scale);
*/
	QVector3D viewVector= camera()->eye() - camera()->center();
	qreal zoomMag = viewVector.length();//应该是摄像头与所拍物体中心点的距离
	qreal zoomIncrement = scale;
	if (!qFuzzyIsNull(zoomIncrement))
	{
		zoomMag = zoomIncrement;
		if (zoomMag < 0.01f)
			zoomMag = 0.01f;
		QRay3D viewLine(camera()->center(), viewVector.normalized());
		camera()->setEye(viewLine.point(zoomMag));
	}
}

void GLViewWidget::rorateView(qreal anglex, qreal angley, qreal anglez)//旋转场景
{
/*	QQuaternion q = m_camera->tilt(anglex);
	q *= m_camera->roll(angley);
	q *= m_camera->pan(anglez);
	m_camera->rotateCenter(q);*/
	m_camera->tiltPanRollCenter(anglex, angley, anglez, QGLCamera::TiltRollPan);
}

