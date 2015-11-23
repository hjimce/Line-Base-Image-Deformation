// Bspline1.h: interface for the CBspline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSPLINE1_H__1EFCF494_1783_466F_BCFB_6D2371BFFD48__INCLUDED_)
#define AFX_BSPLINE1_H__1EFCF494_1783_466F_BCFB_6D2371BFFD48__INCLUDED_

#if _MSC_VER > 1000
#include "Vec.h"
#include<vector>
using namespace std;
#pragma once

#endif // _MSC_VER > 1000

class CBspline  
{
public:
	CBspline();
	virtual ~CBspline();
	CBspline(vector<vec>pt);
	 void Computeinterpolation(void);
	 void ComputeNode(void);
	 vector<vec>m_interpolationnode;
private:
	unsigned int m_k,m_n;//���������ƶ������
	vector<vec>m_Controlpoint;//���ƶ���
	vector<float>m_u;//�ڵ�ʸ��
public:
	void Hartley(void);

};

#endif // !defined(AFX_BSPLINE1_H__1EFCF494_1783_466F_BCFB_6D2371BFFD48__INCLUDED_)
