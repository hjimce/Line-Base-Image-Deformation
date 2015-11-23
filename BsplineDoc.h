// BsplineDoc.h : interface of the CBsplineDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSPLINEDOC_H__D0A362A6_E770_4E2B_8435_53035EDE42C5__INCLUDED_)
#define AFX_BSPLINEDOC_H__D0A362A6_E770_4E2B_8435_53035EDE42C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GdiPlus.h>
#include "PupilGUI.h"
#include <opencv2\core\core.hpp>
#include <opencv2/opencv.hpp>  
class CBsplineDoc : public CDocument
{
protected: // create from serialization only
	CBsplineDoc();
	DECLARE_DYNCREATE(CBsplineDoc)

// Attributes
public:

// Operations
public:
	void GetImage(string image_path,Gdiplus::Bitmap * &pInImage1,cv::Mat &cvimg,vector<cv::Vec2f>&facept);
	vector<cv::Vec2f>m_face_ori;
	vector<cv::Vec2f>m_face_def;
	CPupilGUI *m_Gui;
	Gdiplus::Bitmap* m_pOrignImageS;

	Gdiplus::Bitmap* m_pProcessResults;
	BOOL ResizeBitmap(Gdiplus::Bitmap **ppImg,int m_NewWidth,int m_NewHeight);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBsplineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBsplineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBsplineDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	void GetBitmapData(Gdiplus::BitmapData&lockData,Gdiplus::Bitmap*bitmap_image);
	void GetBbox(vector<cv::Vec2f>pt,cv::Rect&bbox);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BSPLINEDOC_H__D0A362A6_E770_4E2B_8435_53035EDE42C5__INCLUDED_)
