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
	unsigned int m_k,m_n;//次数、控制顶点个数
	vector<vec>m_Controlpoint;//控制顶点
	vector<float>m_u;//节点矢量
public:
	void Hartley(void);
};
