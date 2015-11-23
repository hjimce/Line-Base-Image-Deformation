#pragma once
#include "svm/svm.h"
#include "Vec.h"
#include <vector>
class CLibsvm
{
public:
	CLibsvm(void);
	~CLibsvm(void);
	void TrainModel(vector<vec2>traindata);//数据训练
	void Predict(float x,float &y);//拟合预测函数

private:
	svm_parameter Initialize_svm_parameter();
	svm_parameter m_svmpara;
	svm_problem m_svmprob;
	std::vector<vec2>m_traindata;//二维拟合数据
	svm_model *m_svmmodel;
	void GetMax_Min(double*pdata,int data_num,double &minpt,double&maxpt);
	double *m_maxx;
	double *m_minx;
	double m_miny;
	double m_maxy;

	

};

