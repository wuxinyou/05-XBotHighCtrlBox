/********************************************************************************
概述：YUV2RGBThread.cpp实现摄像头采集并处理，最终通过构造函数将采集到的图像数据传给上层调用。
作者：吴新有
日期：2017-01-11
备注：YUV2RGBThread.cpp调用camera类，实现图像的采集
********************************************************************************/

#include "YUV2RGBThread.h"   
#include <QMessageBox>


/****************************** SENDTHREAD ************************************ 
 ******************************************************************************/  
YUV2RGBThread::YUV2RGBThread(unsigned char *temImage)
{
	pp=temImage;
	char *devName="/dev/video0";
	camera = new Camera(devName,720,576,0);

 
    if(!camera->OpenDevice()){
		QMessageBox::warning(0,tr("error"),tr("OpenDevice failed"),QMessageBox::Yes);

    }
	

}

/******************************* Distructor ***********************************/  
YUV2RGBThread::~YUV2RGBThread()
{  

} 

 
// Thread  Loop   
void YUV2RGBThread::run()
{
    unsigned char image[720*576*2];
    forever
    {  
    mutex.lock();
    
	camera->GetBuffer(image);
	YV12ToBGR24_Table(image,pp,720,576);
	
	emit readySignal();	
    QThread::msleep (2);
    
    mutex.unlock();	
    }
}  

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*yuv格式转换为rgb格式*/
int YUV2RGBThread::convert_yuv_to_rgb_buffer(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height)
{
 unsigned int in, out = 0;
 unsigned int pixel_16;
 unsigned char pixel_24[3];
 unsigned int pixel32;
 int y0, u, y1, v;
 for(in = 0; in < width * height * 2; in += 4) {
  pixel_16 =
   yuv[in + 3] << 24 |
   yuv[in + 2] << 16 |
   yuv[in + 1] <<  8 |
   yuv[in + 0];
  y0 = (pixel_16 & 0x000000ff);
  u  = (pixel_16 & 0x0000ff00) >>  8;
  y1 = (pixel_16 & 0x00ff0000) >> 16;
  v  = (pixel_16 & 0xff000000) >> 24;
  pixel32 = convert_yuv_to_rgb_pixel(y0, u, v);
  pixel_24[0] = (pixel32 & 0x000000ff);
  pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
  pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
  rgb[out++] = pixel_24[0];
  rgb[out++] = pixel_24[1];
  rgb[out++] = pixel_24[2];
  pixel32 = convert_yuv_to_rgb_pixel(y1, u, v);
  pixel_24[0] = (pixel32 & 0x000000ff);
  pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
  pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
  rgb[out++] = pixel_24[0];
  rgb[out++] = pixel_24[1];
  rgb[out++] = pixel_24[2];
 }
 return 0;
}

int YUV2RGBThread::convert_yuv_to_rgb_pixel(int y, int u, int v)
{
 unsigned int pixel32 = 0;
 unsigned char *pixel = (unsigned char *)&pixel32;
 int r, g, b;
 r = y + (1.370705 * (v-128));
 g = y - (0.698001 * (v-128)) - (0.337633 * (u-128));
 b = y + (1.732446 * (u-128));
 if(r > 255) r = 255;
 if(g > 255) g = 255;
 if(b > 255) b = 255;
 if(r < 0) r = 0;
 if(g < 0) g = 0;
 if(b < 0) b = 0;
 pixel[0] = r * 220 / 256;
 pixel[1] = g * 220 / 256;
 pixel[2] = b * 220 / 256;
 return pixel32;
}
/*yuv格式转换为rgb格式*/


/*yuv格式转换为rgb格式--查表法*/
bool YUV2RGBThread::YV12ToBGR24_Table(unsigned char* pYUV,unsigned char* pBGR24,int width,int height)
{
    if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
        return false;
    const long len = width * height;
	
	/*
    unsigned char* yData = pYUV;
    unsigned char* vData = pYUV;
    unsigned char* uData = pYUV;
*/
	    unsigned char* yData = pYUV;
    unsigned char* vData = &yData[len];
    unsigned char* uData = &vData[len >> 2];
	

    int bgr[3];
    int yIdx,uIdx,vIdx,idx;
    int rdif,invgdif,bdif;
    for (int i = 0;i < height;i++){
        for (int j = 0;j < width;j++){
			
			yIdx = i * width + j;
            vIdx = (i/2) * (width/2) + (j/2);
            uIdx = vIdx;
			/*
            yIdx = i * width + j;
            uIdx = (i/2)*width+(j/2)*2+len;
            vIdx = uIdx+1;
			*/
            
            rdif = Table_fv1[vData[vIdx]];
            invgdif =  Table_fu1[uData[uIdx]] +  Table_fv2[vData[vIdx]];
            bdif = Table_fu2[uData[uIdx]];
			
			//最终的RGB
            bgr[0] = yData[yIdx]   + bdif  ;    
            bgr[1] = yData[yIdx]  - invgdif;
            bgr[2] = yData[yIdx]  + rdif   ;

            for (int k = 0;k < 3;k++){
                idx = (i * width + j) * 3 + k;
                if(bgr[k] >= 0 && bgr[k] <= 255)
                    pBGR24[idx] = bgr[k];
                else
                    pBGR24[idx] = (bgr[k] < 0)?0:255;
            }
        }
    }
    return true;
}


/*yuv格式转换为rgb格式--直接转换法*/
bool YUV2RGBThread::YV12ToBGR24_Native(unsigned char* pYUV,unsigned char* pBGR24,int width,int height)
{
    if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
        return false;
    const long len = width * height;
    unsigned char* yData = pYUV;
    unsigned char* vData = &yData[len];
    unsigned char* uData = &vData[len >> 2];

    int bgr[3];
    int yIdx,uIdx,vIdx,idx;
    for (int i = 0;i < height;i++){
        for (int j = 0;j < width;j++){
            yIdx = i * width + j;
            vIdx = (i/2) * (width/2) + (j/2);
            uIdx = vIdx;

            bgr[0] = (int)(yData[yIdx] + 1.732446 * (uData[vIdx] - 128));                                    // b分量
            bgr[1] = (int)(yData[yIdx] - 0.698001 * (uData[uIdx] - 128) - 0.703125 * (vData[vIdx] - 128));    // g分量
            bgr[2] = (int)(yData[yIdx] + 1.370705 * (vData[uIdx] - 128));                                    // r分量

            for (int k = 0;k < 3;k++){
                idx = (i * width + j) * 3 + k;
                if(bgr[k] >= 0 && bgr[k] <= 255)
                    pBGR24[idx] = bgr[k];
                else
                    pBGR24[idx] = (bgr[k] < 0)?0:255;
            }
        }
    }
    return true;
}



/*yuv格式转换为rgb格式--Pinknoise转换法*/
bool YUV2RGBThread::YV12ToBGR24_Pinknoise(unsigned char* pYUV,unsigned char* pBGR24,int width,int height)
{
    if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
        return false;
    unsigned char *yData = pYUV;
    unsigned char *vData = &pYUV[width * height];
    unsigned char *uData = &vData[width * height >> 2];

    yuv420_2_rgb888(pBGR24,yData,uData,vData,width,height,width,width>>1,width*3,NULL,0);
    return true;
}



void YUV2RGBThread::yuv420_2_rgb888(uint8_t  *dst_ptr,
               const uint8_t  *y_ptr,
               const uint8_t  *u_ptr,
               const uint8_t  *v_ptr,
                     int32_t   width,
                     int32_t   height,
                     int32_t   y_span,
                     int32_t   uv_span,
                     int32_t   dst_span,
               const uint32_t *tables,
                     int32_t   dither)
{
    height -= 1;
    while (height > 0)
    {
        height -= width<<16;
        height += 1<<16;
        while (height < 0)
        {
            /* Do 2 column pairs */
            uint32_t uv, y0, y1;

            uv  = READUV(*u_ptr++,*v_ptr++);
            y1  = uv + READY(y_ptr[y_span]);
            y0  = uv + READY(*y_ptr++);
            FIXUP(y1);
            FIXUP(y0);
            STORE(y1, &dst_ptr[dst_span]);
            STORE(y0, dst_ptr);
            dst_ptr += 3;
            y1  = uv + READY(y_ptr[y_span]);
            y0  = uv + READY(*y_ptr++);
            FIXUP(y1);
            FIXUP(y0);
            STORE(y1, &dst_ptr[dst_span]);
            STORE(y0, dst_ptr);
            dst_ptr += 3;
            height += (2<<16);
        }
        if ((height>>16) == 0)
        {
            /* Trailing column pair */
            uint32_t uv, y0, y1;

            uv = READUV(*u_ptr,*v_ptr);
            y1 = uv + READY(y_ptr[y_span]);
            y0 = uv + READY(*y_ptr++);
            FIXUP(y1);
            FIXUP(y0);
            STORE(y0, &dst_ptr[dst_span]);
            STORE(y1, dst_ptr);
            dst_ptr += 3;
        }
        dst_ptr += dst_span*2-width*3;
        y_ptr   += y_span*2-width;
        u_ptr   += uv_span-(width>>1);
        v_ptr   += uv_span-(width>>1);
        height = (height<<16)>>16;
        height -= 2;
    }
    if (height == 0)
    {
        /* Trail row */
        height -= width<<16;
        height += 1<<16;
        while (height < 0)
        {
            /* Do a row pair */
            uint32_t uv, y0, y1;

            uv  = READUV(*u_ptr++,*v_ptr++);
            y1  = uv + READY(*y_ptr++);
            y0  = uv + READY(*y_ptr++);
            FIXUP(y1);
            FIXUP(y0);
            STORE(y1, dst_ptr);
            dst_ptr += 3;
            STORE(y0, dst_ptr);
            dst_ptr += 3;
            height += (2<<16);
        }
        if ((height>>16) == 0)
        {
            /* Trailing pix */
            uint32_t uv, y0;

            uv = READUV(*u_ptr++,*v_ptr++);
            y0 = uv + READY(*y_ptr++);
            FIXUP(y0);
            STORE(y0, dst_ptr);
            dst_ptr += 3;
        }
    }
}



