// BsplineView.h : interface of the CBsplineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSPLINEVIEW_H__76598A60_1285_4008_97E8_5E14A35444DF__INCLUDED_)
#define AFX_BSPLINEVIEW_H__76598A60_1285_4008_97E8_5E14A35444DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "vec.h"
#include<vector>
using namespace std;
#endif // _MSC_VER > 1000


class CBsplineView : public CView
{
protected: // create from serialization only
	CBsplineView();
	DECLARE_DYNCREATE(CBsplineView)

// Attributes
public:
	CBsplineDoc* GetDocument();

	vector<vec2>m_controlpoint;
	vector<vec2>m_resultcurve;
	void DrawBitmap(CDC*pDC);
	void GetBitmapData(Gdiplus::BitmapData&lockData,Gdiplus::Bitmap*bitmap_image);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBsplineView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBsplineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBsplineView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BsplineView.cpp
inline CBsplineDoc* CBsplineView::GetDocument()
   { return (CBsplineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BSPLINEVIEW_H__76598A60_1285_4008_97E8_5E14A35444DF__INCLUDED_)
