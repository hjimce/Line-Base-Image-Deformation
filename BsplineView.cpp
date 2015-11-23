// BsplineView.cpp : implementation of the CBsplineView class
//

#include "stdafx.h"

#include "Bspline.h"
#include "Bspline1.h"


#include "BsplineDoc.h"
#include "BsplineView.h"
#include "Libsvm.h"
#include <GdiPlus.h>
#include "PupilGUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBsplineView

IMPLEMENT_DYNCREATE(CBsplineView, CView)

BEGIN_MESSAGE_MAP(CBsplineView, CView)
	//{{AFX_MSG_MAP(CBsplineView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_GEN, OnGen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBsplineView construction/destruction

CBsplineView::CBsplineView()
{
	// TODO: add construction code here

}

CBsplineView::~CBsplineView()
{
}

BOOL CBsplineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBsplineView drawing

void CBsplineView::OnDraw(CDC* pDC)
{
	CBsplineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here




	DrawBitmap(pDC);
	if (pDoc->m_Gui)
	{
		pDoc->m_Gui->Render(pDC);
	}

	CPen pen2;
	pen2.CreatePen(PS_SOLID,2,RGB(0,255,255));//创建对象
	CPen *oldPen=pDC->SelectObject(&pen2);//将画笔选入设备描述表，并保存旧的画笔
	// TODO: 在此处为本机数据添加绘制代码
	for (int i=0;i<pDoc->m_face_ori.size();i++)
	{   
		pDC->Ellipse(pDoc->m_face_ori[i][0]-1,pDoc->m_face_ori[i][1]
		-1,pDoc->m_face_ori[i][0]+1,pDoc->m_face_ori[i][1]+1);
	}

	CPen pen1;
	pen1.CreatePen(PS_SOLID,2,RGB(0,255,0));//创建对象
	pDC->SelectObject(&pen1);//将画笔选入设备描述表，并保存旧的画笔
	// TODO: 在此处为本机数据添加绘制代码
	for (int i=0;i<pDoc->m_face_def.size();i++)
	{   
		pDC->Ellipse(pDoc->m_face_def[i][0]-1,pDoc->m_face_def[i][1]
		-1,pDoc->m_face_def[i][0]+1,pDoc->m_face_def[i][1]+1);
	}

	pDC->SelectObject(oldPen);

}
void CBsplineView::DrawBitmap(CDC*pDC)
{
	CBsplineDoc* pDoc = GetDocument();
	if(!pDoc->m_pOrignImageS)return;
	Gdiplus::Bitmap*TImage=pDoc->m_pOrignImageS;
	CRect clientrect;
	GetClientRect(&clientrect);
	Gdiplus::Rect m_rtShowRect(0,0,pDoc->m_pOrignImageS->GetWidth(),pDoc->m_pOrignImageS->GetHeight());
	Gdiplus::Graphics gsClient(pDC->GetSafeHdc());
	gsClient.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	gsClient.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
	gsClient.DrawImage(pDoc->m_pOrignImageS, m_rtShowRect, 0, 0,pDoc->m_pOrignImageS->GetWidth(),pDoc->m_pOrignImageS->GetHeight(), Gdiplus::UnitPixel);

}

/////////////////////////////////////////////////////////////////////////////
// CBsplineView printing

BOOL CBsplineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBsplineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBsplineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBsplineView diagnostics

#ifdef _DEBUG
void CBsplineView::AssertValid() const
{
	CView::AssertValid();
}

void CBsplineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBsplineDoc* CBsplineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBsplineDoc)));
	return (CBsplineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBsplineView message handlers

void CBsplineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	vec2 pt(point.x,point.y);
	m_controlpoint.push_back(pt);
	CDC*pDC=GetDC();
	CPen pen1;
	CPen *oldPen;
	pen1.CreatePen(PS_SOLID,5,RGB(0,0,255));//创建对象
	oldPen = pDC->SelectObject(&pen1);//将画笔选入设备描述表，并保存旧的画笔
	// TODO: 在此处为本机数据添加绘制代码
	int i;
	for (i=0;i<m_controlpoint.size();i++)
	{   
		pDC->Ellipse(m_controlpoint[i][0]-3,m_controlpoint[i][1]
		-3,m_controlpoint[i][0]+3,m_controlpoint[i][1]+3);
	}
	pDC->SelectObject(oldPen);
	CView::OnLButtonDown(nFlags, point);

}
void CBsplineView::OnGen() 
{
	// TODO: Add your command handler code here
	CBsplineDoc* pDoc = GetDocument();
	Gdiplus::BitmapData m_TempBitmapData;
	GetBitmapData(m_TempBitmapData,pDoc->m_pOrignImageS);
	if (pDoc->m_Gui)
	{
		delete pDoc->m_Gui;
	}

	
	pDoc->m_Gui=new CPupilGUI((BYTE*)m_TempBitmapData.Scan0, m_TempBitmapData.Width, m_TempBitmapData.Height);
/*
	pDoc->m_LipContour_left=new CLipContour((BYTE*)m_TempBitmapData.Scan0, m_TempBitmapData.Width, m_TempBitmapData.Height,true);
	pDoc->m_LipContour_right=new CLipContour((BYTE*)m_TempBitmapData.Scan0, m_TempBitmapData.Width, m_TempBitmapData.Height,false);*/
	
	pDoc->m_pOrignImageS->UnlockBits(&m_TempBitmapData);

/*
	if (m_controlpoint.size()<2)
	{   
		MessageBox("请输入两个以上的控制顶点");
		return;
	}
	int i;
	CDC*pDC=GetDC();
	CPen pen1;
	CPen *oldPen;
	pen1.CreatePen(PS_DASH,1,RGB(0,0,255));//创建对象
	oldPen = pDC->SelectObject(&pen1);//将画笔选入设备描述表，并保存旧的画笔
		for (i=0;i<m_controlpoint.size()-1;i++)
	{   
		pDC->MoveTo(m_controlpoint[i][0],m_controlpoint[i][1]);
		pDC->LineTo(m_controlpoint[i+1][0],m_controlpoint[i+1][1]);
	}
	CPen pen2;
	pen2.CreatePen(PS_DASH,3,RGB(0,0,255));//创建对象
	pDC->SelectObject(&pen2);//将画笔选入设备描述表，并保存旧的画笔



   	CLibsvm csvm;
	csvm.TrainModel(m_controlpoint);

	float minx=1e10;
	float maxx=0;
	for (int i=0;i<m_controlpoint.size();i++)
	{
		if (m_controlpoint[i][0]<minx)
		{
			minx=m_controlpoint[i][0];
		}
		if (m_controlpoint[i][0]>maxx)
		{
			maxx=m_controlpoint[i][0];
		}
	}
	m_resultcurve.clear();
	for (int i=minx;i<maxx;i++)
	{
		float y=0;
		csvm.Predict(i,y);
		m_resultcurve.push_back(vec2(i,y));
	}*/


/*
	bcurve.Computeinterpolation();
   for(i=0;i<bcurve.m_interpolationnode.size()-1;i++)
   {
	   pDC->MoveTo(bcurve.m_interpolationnode[i][0],bcurve.m_interpolationnode[i][1]);
		   pDC->LineTo(bcurve.m_interpolationnode[i+1][0],bcurve.m_interpolationnode[i+1][1]);
   }*/
	Invalidate();
	//pDC->SelectObject(oldPen);
  
	
}
void CBsplineView::GetBitmapData(Gdiplus::BitmapData&lockData,Gdiplus::Bitmap*bitmap_image)
{
	Gdiplus::Rect rc(0, 0,bitmap_image->GetWidth(),bitmap_image->GetHeight());
	bitmap_image->LockBits(&rc, Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &lockData);
}
