// BsplineDoc.cpp : implementation of the CBsplineDoc class
//


#include "stdafx.h"
#include "Bspline.h"

#include "BsplineDoc.h"
#include <opencv2\core\core.hpp>
#include <opencv2/opencv.hpp>  
#include "Function.h"


/////////////////////////////////////////////////////////////////////////////
// CBsplineDoc

IMPLEMENT_DYNCREATE(CBsplineDoc, CDocument)

BEGIN_MESSAGE_MAP(CBsplineDoc, CDocument)
	//{{AFX_MSG_MAP(CBsplineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBsplineDoc construction/destruction

CBsplineDoc::CBsplineDoc()
{
	// TODO: add one-time construction code here
	m_pOrignImageS=NULL;
	m_pProcessResults=NULL;
	m_Gui=NULL;
}

CBsplineDoc::~CBsplineDoc()
{
}

BOOL CBsplineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBsplineDoc serialization

void CBsplineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBsplineDoc diagnostics

#ifdef _DEBUG
void CBsplineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBsplineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBsplineDoc commands

#include<atlconv.h>
#include "directory.h"
#include "Function.h"
BOOL CBsplineDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	
	string image1="1.jpg";
	cv::Mat ori;
	GetImage(image1,m_pOrignImageS,ori,m_face_ori);

	string image2="4.jpg";
	Gdiplus::Bitmap *secondimage;
	cv::Mat def;
	GetImage(image2,secondimage,def,m_face_def);



	Function warp;
	warp.Warp(ori,ori,m_face_ori,m_face_def);

	cv::imshow("def",ori);




	return TRUE;
}
void CBsplineDoc::GetImage(string image_path,Gdiplus::Bitmap * &pInImage1,cv::Mat &cvimg,vector<cv::Vec2f>&facept)
{
	string img=image_path;
	wchar_t * wc = new wchar_t[];
	swprintf(wc,100,L"%S",img.c_str());
	pInImage1 = Gdiplus::Bitmap::FromFile(wc);
	

	// TODO:  在此添加您专用的创建代码
	if (pInImage1->GetWidth()>480||pInImage1->GetHeight()>640)
	{
		float scalew=1;
		float scaleh=1;
		//if (m_pOrignImageS->GetWidth()>480)
		//{
			scalew=480.f/pInImage1->GetHeight();
		//}
		/*if(m_pOrignImageS->GetHeight()>640)
		{
			scaleh=640.f/m_pOrignImageS->GetWidth();
		}
		scalew=min(scalew,scaleh);*/
		
		int width=pInImage1->GetWidth()*scalew;
		int height=pInImage1->GetHeight()*scalew;
		ResizeBitmap(&pInImage1,width,height);





	}




	Gdiplus::BitmapData m_TempBitmapData;
	GetBitmapData(m_TempBitmapData,pInImage1);
	CPupilGUI cpi=CPupilGUI((BYTE*)m_TempBitmapData.Scan0, m_TempBitmapData.Width, m_TempBitmapData.Height);
	if (cpi.isface==false)
	{
		return ;
	}

	for (int i=0;i<39;i++)
	{
		cv::Vec2f pt(cpi.m_face_detection.landmarks[i].x,cpi.m_face_detection.landmarks[i].y);
		facept.push_back(pt);
	}
	pInImage1->UnlockBits(&m_TempBitmapData);


	cvimg =cv::imread(image_path);  //原始读入	


/*
	cv::Mat dst;
	cv::resize(cvimg,dst,cv::Size(pInImage1->GetWidth(),pInImage1->GetHeight()));
	cvimg=dst;*/

	

}

void CBsplineDoc::GetBitmapData(Gdiplus::BitmapData&lockData,Gdiplus::Bitmap*bitmap_image)
{
	Gdiplus::Rect rc(0, 0,bitmap_image->GetWidth(),bitmap_image->GetHeight());
	bitmap_image->LockBits(&rc, Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &lockData);
}

//示例：ResizeBitmap(&m_pOrignImageS,width,height);
BOOL CBsplineDoc::ResizeBitmap(Gdiplus::Bitmap **ppImg,int m_NewWidth,int m_NewHeight)
{
	if(ppImg == NULL || *ppImg == NULL)
	{
		return FALSE;
	}

	Gdiplus::Bitmap *m_NewImage = new Gdiplus::Bitmap(m_NewWidth,m_NewHeight);

	Gdiplus::ColorMatrix colorMatrix = {
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

		Gdiplus::ImageAttributes imageAtt;
		imageAtt.SetColorMatrix(&colorMatrix);
		imageAtt.SetWrapMode(Gdiplus::WrapModeTileFlipXY);

		Gdiplus::Graphics gs(m_NewImage);
		gs.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		gs.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality );
		gs.DrawImage(
			(*ppImg), 
			Gdiplus::Rect(0,0,m_NewWidth,m_NewHeight),  // Destination rectangle
			0,								   // Source rectangle temp->x 
			0,								   // Source rectangle temp->y
			(*ppImg)->GetWidth(),     // Source rectangle width
			(*ppImg)->GetHeight(),    // Source rectangle height
			Gdiplus::UnitPixel, 
			&imageAtt);

		//交换指针
		delete (*ppImg);
		(*ppImg) = m_NewImage;
		return TRUE;
}
