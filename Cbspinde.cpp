#include "StdAfx.h"
#include "Cbspinde.h"

Cbspinde::Cbspinde(void)
{
} 
Cbspinde::Cbspinde(vector<vec>pt)
{ 
  m_n=pt.size()-1;
  if (pt.size()<4)
  {
	  m_k=pt.size()-1;
  }
  else m_k=3;
  m_Controlpoint.resize(pt.size());
  memcpy(&m_Controlpoint[0], &pt[0], pt.size() * sizeof(vec));
  m_u.resize(m_n+m_k+2);
}

Cbspinde::~Cbspinde(void)
{
}

void Cbspinde::Computeinterpolation(void)
{   
	ComputeNode();
	
	int m;
	int n;
	float interpolationnumber;
	vector<vec>relevantPoint;
	vector<float>relevantU;
	relevantPoint.resize(m_k+1);//相关控制顶点
	relevantU.resize(2*m_k);//相关节点矢量
	//相关控制顶点拷贝
	float u=0;
	int i=m_k;//m表示u值所在的节点,则控制顶点为m_controlpoint[i-k]\m_controlpoint[i]
	float a;
   for (interpolationnumber=0.0;interpolationnumber<300.0;interpolationnumber++)
   {
       n=0;
	   m=0;
	   u=interpolationnumber/300;
      if (u>m_u[i+1])i++;
	   for (m=i-m_k;m<=i;m++)
	   {   
		   relevantPoint[n]=m_Controlpoint[m];
		   n++;
	   }
	   //相关节点矢量拷贝
	   n=0;
	   for (m=i-m_k+1;m<=i+m_k;m++)
	   {   
		   relevantU[n]=m_u[m];
		   n++;
	   }
	   //开始插值计
	   for (n=1;n<relevantPoint.size();n++)
		   for(m=0;m<relevantPoint.size()-n;m++)
		   {   a=relevantU[m_k+m]-relevantU[m+n-1];
	           if (fabs(a)<1e-5) a=0.0;
	           else  a=(u-relevantU[m+n-1])/a;
	           relevantPoint[m]=(1-a)*relevantPoint[m]+a*relevantPoint[m+1];
	        }
	   m_interpolationnode.push_back(relevantPoint[0]);
   }
   
	
	

}
//计算节点矢量
void Cbspinde::ComputeNode(void)
{ int i;
  float u=0;
  for (i=0;i<=m_k;i++)m_u[i]=0;
  for(i=1;i<=m_k+1;i++)m_u[i+m_n]=1;
  Hartley();
}
void Cbspinde::Hartley(void)
{   int i,j;
	float u=0;
	float sum=0;
	float s=0;
	vector<float>length(m_n);
	vector<float>ll;
	ll.push_back(0.0);
	vec pq;
	for(i=0;i<m_n;i++)
	{
		pq=m_Controlpoint[i+1]-m_Controlpoint[i];
		length[i]=len(pq);
	}
	for (i=0;i<=length.size()-m_k;i++)
	{   
		s=0;
		for(j=0;j<m_k;j++)
			{
				s+=length[i+j];
			}
		sum+=s;
		ll.push_back(s);
	}
	for(i=1;i<ll.size();i++)
	{   
		ll[i]=ll[i-1]+ll[i];
		m_u[i+m_k]=ll[i]/sum;
	}
}
