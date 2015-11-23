#include "stdafx.h"
#include "Libsvm.h"


CLibsvm::CLibsvm(void)
{
	m_svmpara=Initialize_svm_parameter();
}


CLibsvm::~CLibsvm(void)
{
}
svm_parameter CLibsvm::Initialize_svm_parameter()
{
	svm_parameter svmpara;//svm的相关参数
	svmpara.svm_type = EPSILON_SVR;
	svmpara.kernel_type =RBF;
	svmpara.degree = 3;
	svmpara.gamma = 1;	// 默认大小可选择特征的倒数 1/num_features，核函数中的gamma函数设置（只针对多项式/rbf/sigmoid核函数）
	svmpara.coef0 = 0;
	svmpara.nu = 0.5;
	svmpara.cache_size = 1;//缓存块大小
	svmpara.C = 1;
	svmpara.eps = 1e-3;
	svmpara.p = 0.1;
	svmpara.shrinking = 1;
	svmpara.probability = 0;
	svmpara.nr_weight = 0;
	svmpara.weight_label = NULL;
	svmpara.weight = NULL;
	return svmpara;
}
//拟合数据输入
void CLibsvm::TrainModel(vector<vec2>traindata)
{
	//Normalizedata(traindata,m_minpt,m_maxpt);
	int sample_num=traindata.size();//训练样本个数
	int feature_dimn=1;//样本的特征维数为1
	double *y=new double[sample_num];
	double **x=new double *[sample_num];
	for (int i=0;i<sample_num;i++)
	{
		x[i]=new double[feature_dimn];
	}

	for (int i=0;i<sample_num;i++)
	{
		y[i]=traindata[i][feature_dimn];
		for (int j=0;j<feature_dimn;j++)
		{
			x[i][j]=traindata[i][j];
		}
	}

//训练数据归一化
	//获取最大最小值
	GetMax_Min(y,sample_num,m_miny,m_maxy);//训练数据y的最大最小值获取
	m_minx=new double[feature_dimn];//特征最大最小值获取
	m_maxx=new double[feature_dimn];
	double *pdata=new double[sample_num];
	for (int j=0;j<feature_dimn;j++)
	{
		for (int i=0;i<sample_num;i++)
		{
			pdata[i]=x[i][j];	
		}
		GetMax_Min(pdata,sample_num,m_minx[j],m_maxx[j]);
	}
	//训练数据归一化
	for (int i=0;i<sample_num;i++)
	{
		y[i]=2*(y[i]-m_miny)/(m_maxy-m_miny)-1;
		for (int j=0;j<feature_dimn;j++)
		{
			x[i][j]=2*(x[i][j]-m_minx[j])/(m_maxx[j]-m_minx[j])-1;
		}
	}



//训练数据输入
	svm_problem svmpro;//svm训练数据
	svmpro.l=sample_num;
	svmpro.y=new double[sample_num];
	svmpro.x=new svm_node *[sample_num];//训练数据的特征向量
	for (int i=0;i<sample_num;i++)
	{
		svmpro.y[i]=y[i];//用训练数据的y，作为输入标签
		svmpro.x[i]=new svm_node[feature_dimn+1];
		for (int j=0;j<feature_dimn;j++)
		{
			svm_node node_ij;
			node_ij.index=j+1;//需要注意的是svm_node的第一个数据的索引为1，数值为第一位特征值，我一开始这里搞错了，把索引搞成从0开始
			node_ij.value=x[i][j];
			svmpro.x[i][j]=node_ij;
		}
		svm_node node_last;//需要添加最后一维特征的索引为-1
		node_last.index=-1;
		svmpro.x[i][feature_dimn]=node_last;
	}
//验证输入的训练数据、初始化的参数是否有误
	const char *error_msg;
	error_msg = svm_check_parameter(&svmpro,&m_svmpara);
	if(error_msg)
	{
		//AfxMessageBox(error_msg);
	}
//数据训练
	m_svmmodel=svm_train(&svmpro,&m_svmpara);
}
void CLibsvm::Predict(float x,float &y)
{

	x=2*(x-m_minx[0])/(m_maxx[0]-m_minx[0])-1;
	svm_node *testX1=new svm_node[1+1];
	testX1[0].index=1;
	testX1[0].value=x;
	testX1[1].index=-1;
	y=(svm_predict(m_svmmodel,testX1)+1)*(m_maxy-m_miny)*0.5+m_miny;


}
//数据归一化
void CLibsvm::GetMax_Min(double*pdata,int data_num,double &minpt,double&maxpt)
{

	double minx=1e10;
	double maxx=-1e10;
	for (int i=0;i<data_num;i++)
	{
		if (pdata[i]<minx)
		{
			minx=pdata[i];
		}
		if (pdata[i]>maxx)
		{
			maxx=pdata[i];
		}
	}
	minpt=minx;
	maxpt=maxx;
}


