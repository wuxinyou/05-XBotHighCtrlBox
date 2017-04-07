
#ifndef _DEVWDM_H
#define _DEVWDM_H
#endif
#define LONG long
//#define     WINAPI     __stdcall     
#define     APIENTRY     __stdcall 
#define     BOOL     bool 
#define     DWORD     long 
typedef enum
{
	AnalogVideo_None       = 0x00000000,
        AnalogVideo_NTSC_M     = 0x00000001, 
        AnalogVideo_PAL_B      = 0x00000010,
        AnalogVideo_PAL_D      = 0x00000020,
        AnalogVideo_SECAM_B    = 0x00001000,
        AnalogVideo_SECAM_D    = 0x00002000,
             
} AnalogVideoStandard;

/*devwdm_InitCard
函数功能：		初始化设备
nID： 			设备ID号，默认0
hWnd: 			显示视频窗口的窗口句柄
nWidth, nHeight:	图像的分辨率 
*/
LONG APIENTRY devwdm_InitCard(int nID, HWND hWnd, int nWidth, int nHeight);
/*devwdm_CloseCard:
函数功能：		关闭设备
nID： 			设备ID号
*/
LONG APIENTRY devwdm_CloseCard(int nID);

/*devwdm_SetVideoStandard
函数功能：		设置视频制式
nID： 			设备ID号
VideoStandard:		制式,如P制:AnalogVideo_PAL_D;N制:AnalogVideo_NTSC_M等
*/
LONG APIENTRY devwdm_SetVideoStandard(int nID, LONG  VideoStandard);


/*devwdm_SaveBmpFile
函数功能：		保存单前单帧图像
nID： 			设备ID号
strFileName:		存放bmp文件的完整路径名
*/
LONG APIENTRY devwdm_SaveBmpFile(int nID, char* strFileName);


/*devwdm_SetDisplayPos
函数功能：		调整视频在其视频窗口的显示位置
nID： 			设备ID号
x:			左上角的x位置
y:			左上角的y位置
w:			图像的宽度
h:			图像的高度
*/
LONG APIENTRY devwdm_SetDisplayPos(int nID, int x, int y, int w, int h);


/*devwdm_SetBrightNess,devwdm_SetContrast, devwdm_SetSaturation ,devwdm_SetHue
函数功能：		调整视频的颜色值,分别为亮度，对比度，饱和度色度
nID： 			设备ID号
*/
LONG APIENTRY devwdm_SetBrightNess(int nID, LONG brightness);
LONG APIENTRY devwdm_SetContrast(int nID, LONG contrast);
LONG APIENTRY devwdm_SetSaturation(int nID, LONG satu);
LONG APIENTRY devwdm_SetHue(int nID, LONG hue);

/*devwdm_GetBrightNess,devwdm_GetContrast, devwdm_GetSaturation ,devwdm_GetHue
函数功能：		取得当前视频的颜色值,分别为亮度，对比度，饱和度色度
nID： 			设备ID号
Min---Max:  色彩范围值    
*/
LONG APIENTRY devwdm_GetBrightNess(int nID, LONG *brightness, LONG *Max, LONG *Min, LONG *Default);
LONG APIENTRY devwdm_GetContrast(int nID, LONG *contrast, LONG *Max, LONG *Min, LONG *Default);
LONG APIENTRY devwdm_GetSaturation(int nID, LONG *satu, LONG *Max, LONG *Min, LONG *Default);
LONG APIENTRY devwdm_GetHue(int nID, LONG *hue, LONG *Max, LONG *Min, LONG *Default);


/*devwdm_GetVideoPinCounts
函数功能：		取得当前设备的输入源,如：s-video, 复合视频等
nID： 			设备ID号
OutputPins: 		
InputPins		暂时不用
*/
LONG APIENTRY devwdm_GetVideoPinCounts(int nID, LONG *OutputPins, LONG *InputPins);

/*devwdm_RouteOutPin
函数功能：		设置当前设备的输入源,
nID： 			设备ID号
OutputPins: 		s-video为0, 复合视频为1

*/
LONG APIENTRY devwdm_RouteOutPin(int nID, LONG OutputPin);


/*devwdm_StartVideoPreview
函数功能：		启动视频
nID： 			设备ID号

*/
LONG APIENTRY devwdm_StartVideoPreview(int nID);


/*devwdm_SetFlip
函数功能：		将视频图像垂直翻转180度,
nID： 			设备ID号
dwFlip: 		为DWORD的指针,1或0, 1表示翻转，0表示正常显示
fbGet:			1:此函数当Get使用， 0，此函数当Set使用
*/

LONG APIENTRY devwdm_SetFlip(int nID, DWORD *dwFlip,  BOOL fbGet);


/*devwdm_SetMirror
函数功能：		将视频图水平翻转180度,
nID： 			设备ID号
dwFlip: 		为DWORD的指针,1或0, 1表示翻转，0表示正常显示
fbGet:			1:此函数当Get使用， 0，此函数当Set使用
*/
LONG APIENTRY devwdm_SetMirror(int nID, DWORD *dwMirror, BOOL fbGet);


/*devwdm_PreviewPause
函数功能：		视频暂停显示,
nID： 			设备ID号
*/
LONG APIENTRY devwdm_PreviewPause(int nID);

/*devwdm_PreviewResume
函数功能：		重新启动视频显示,与devwdm_PreviewPause相对应
nID： 			设备ID号
*/
LONG APIENTRY devwdm_PreviewResume(int nID);

/*devwdm_StartCaptureMp4
函数功能：		启动录像，进行动态采集
nID： 			设备ID号
strFileName:		存放录像文件的完整路径名
*/
LONG APIENTRY devwdm_StartCaptureMp4(int nID, char* strFileName);
/*devwdm_stopCaptureMp4
函数功能：		停止录像，终止进行动态采集
nID： 			设备ID号
*/
LONG APIENTRY devwdm_stopCaptureMp4(int nID);



