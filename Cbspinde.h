#include "Vec.h"
#include<vector>
using namespace std;
#pragma once

class Cbspinde
{
public:
	Cbspinde(void);
	~Cbspinde(void);
	 Cbspinde(vector<vec>pt);
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
