#include "StdAfx.h"
#include "PupilGUI.h"
#include "CommonDefine.h"

CPupilGUI::CPupilGUI(void)
{
}


CPupilGUI::~CPupilGUI(void)
{
}
CPupilGUI::CPupilGUI(BYTE* pImage, int nWidth, int nHeight)
{
	//转换成灰度图像
	m_width=nWidth;
	m_height=nHeight;
	byte*m_pImagebyte=ConvertToGray(pImage,nWidth,nHeight);//转换为灰度图像
	if (!face_detection(m_pImagebyte,nWidth,nHeight,m_face_detection))
	{
		isface=false;
		return;
	}
	else
	{
		isface=true;
	}


}
//使用face++进行人脸关键点的检测
bool CPupilGUI::face_detection(byte *pData,int nWidth,int nHeight ,FACEPP_FACEINFO  &face0)
{
#define MAX_FACE_COUNT 10
	FACEPP_FACEINFO  faceData[MAX_FACE_COUNT];
	facepp_init();
	facepp_setDetectionMode(FACEPP_DETECTMODEACCURACY_HIGH);
	facepp_setAttributeMode(FACEPP_ATTRIBUTEMODE_LANDMARK39);
	int fn=facepp_detect(pData,nWidth,nHeight,faceData,MAX_FACE_COUNT,0);
	face0=faceData[0];
	if (fn<=0)
	{
		return false;
	}
	else return true;

}
//彩色图像转换为灰度图像
byte * CPupilGUI::ConvertToGray(BYTE* pImage, int nWidth, int nHeight)
{
	byte *gra_image=new byte[nHeight*nWidth];
	for (int y=0;y<nHeight;y++)
	{
		for (int x=0;x<nWidth;x++)
		{
			BYTE *pTempData=pImage+(y*nWidth+x)*4;
			float gray=pTempData[MT_RED] * 0.3 +pTempData[MT_GREEN]* 0.59 + pTempData[MT_BLUE]* 0.11;
			byte*ptemp=gra_image+y*nWidth+x;
			*ptemp=(byte)gray;
		}
	}
	return gra_image;
}
//绘制
void CPupilGUI::Render(CDC*pDC)
{
	CPen pen1;
	CPen *oldPen;
	pen1.CreatePen(PS_SOLID,3,RGB(0,0,255));//创建对象
	oldPen = pDC->SelectObject(&pen1);//将画笔选入设备描述表，并保存旧的画笔
	// TODO: 在此处为本机数据添加绘制代码
	for (int i=0;i<39;i++)
	{   
		int x=m_face_detection.landmarks[i].x;
		int y=m_face_detection.landmarks[i].y;
		CPoint pt(x,y);
		pDC->Ellipse(pt.x-1,pt.y
		-1,pt.x+1,pt.y+1);
	}
    pDC->SelectObject(oldPen);
}

