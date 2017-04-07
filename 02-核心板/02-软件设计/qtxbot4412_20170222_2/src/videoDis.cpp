#include "videoDis.h"

VideoDis::VideoDis( QWidget * parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	//setupUi(this);
	
	mold=1;

	type=false;
	lockFlag=false;
	changeFlag=false;
	positionFlag=5;
	setPosition(0);
	last=QPoint(0,0);
	backPoint=QPoint(0,0);
	
	cameraProcess = new ProcessImage(this);
	//cameraProcess->setGeometry(59,0,682*w,430*h);
	
	//count=0;
	//timer= new QTimer(this);
	//timer->setInterval(1000);//一秒之内两次点击为双击
	//connect(timer, SIGNAL(timeout()), this, SLOT(changeCount())); 
}
void VideoDis::setMold(int m)
{
	mold=m;
	update();
}
//void VideoDis::changeCount()
//{
	//this->count++;
	//if(this->count>0)
	//{
		//this->count=0;
		//timer->stop();
	//}
//}
void VideoDis::setType()//设定在武器界面
{
	type=true;
}
void VideoDis::resetType()//设定在平台或者在侦察界面
{
	type=false;
}
void VideoDis::setLock()
{
	lockFlag=true;
}

void VideoDis::resetLock()
{
	lockFlag=false;
}


void VideoDis::setPosition(int p)
{
	if(p==positionFlag)
	{
		return;
	}
	positionFlag=p;	
	if(positionFlag==1)//全屏幕显示
	{
		this->setGeometry(0,24,800,576);
		cameraProcess->setGeometry(0,0,800,576);
	}
	else if(p==0)
	{
		this->setGeometry(80,32,640,416);
		cameraProcess->setGeometry(0,0,640,416);
	}
}
//void VideoDis::mouseDoubleClickEvent ( QMouseEvent * e)
//{

	//if(e->buttons()==Qt::LeftButton)
	//{

	    //if((width()>700)&&(height()<380))//处在综合显示界面
	    //{
	    	//if(e->globalPos().x()<400)
	    		//emit mouseChange(1);//显示平台界面
	    	//else
	    		//emit mouseChange(2);//显示武器（侦查）界面
    	//}
    	//else if((width()<700)&&(height()>380))
    	//{

    		//if(type)
    		//{
    			//if(lockFlag)//锁定
					//return;
   			//}

    		//emit mouseChange(3);// 全屏显示
   		//}
   		//else if((width()>700)&&(height()>500))
   		//{
   			//emit mouseChange(4);// 退出全屏显示
  		//}
	//}		
//}

void VideoDis::mouseMoveEvent(QMouseEvent *e)
{

	if (!(e->buttons() & Qt::LeftButton))
    	return;
    int x=e->x()-last.x();
    int y=e->y()-last.y();

    if(changeFlag==false&&(x>60||x<-60))//横向滑动屏幕切换视频
    {
    	if((last.x()<width()/2)&&(last.y()<height()/2))//显示CH1
    		emit mouseChange(1);
    	else if((last.x()>width()/2)&&(last.y()<height()/2))//显示CH1
    		emit mouseChange(2);
    	else if((last.x()<width()/2)&&(last.y()>height()/2))//显示CH1
    		emit mouseChange(3);
    	else if((last.x()>width()/2)&&(last.y()>height()/2))//显示CH1
    		emit mouseChange(4);	
    	changeFlag=true;
   	}
   	else if(changeFlag==false&&(y>160||y<-160))//纵向滑动视频四分屏显示
   	{
   		emit mouseChange(0);// 四分屏显示
   		changeFlag=true;
  	}
}

void VideoDis::mousePressEvent(QMouseEvent *e)
{
	last = e->pos();
	changeFlag=false;
}
//void VideoDis::mouseReleaseEvent ( QMouseEvent * e)//鼠标松开事件
//{
	//if(lockFlag&&type)//锁定并且处在武器界面
		//emit sendXY(e->globalPos().x(),e->globalPos().y());
//}

//void VideoDis::paintEvent(QPaintEvent *)
//{
	//QPainter painter(this);
	//painter.setBrush(QColor(40,40,40));
	//painter.setPen(Qt::NoPen);
	//QFont m_digitFont;
    //m_digitFont.setPointSize(12);
    //painter.setFont (m_digitFont);
	//if(width()>700)
	//{
		//painter.drawRect(0,0,800,24);
		//QPen Pen(QColor(0,255,255));
    	//painter.setPen(Pen);
    	//if(positionFlag==2)
    	//{
	    	//if(type)
	    	//{
	    		//if(mold==1)
					//painter.drawText( QPointF(10,18), "武器图像");
				//else if(mold==2)
					//painter.drawText( QPointF(10,18), "侦察图像");	    		
    		//}
			//else
				//painter.drawText( QPointF(10,18), "平台图像");
   		//}
	//}
//}
void VideoDis::stopVideo()
{
	//myAvideo->stop();
}
void VideoDis::startVideo()
{
	//myAvideo->start();
}

