#pragma once
#include "svm/svm.h"
#include "Vec.h"
#include <vector>
class CLibsvm
{
public:
	CLibsvm(void);
	~CLibsvm(void);
	void TrainModel(vector<vec2>traindata);//����ѵ��
	void Predict(float x,float &y);//���Ԥ�⺯��

private:
	svm_parameter Initialize_svm_parameter();
	svm_parameter m_svmpara;
	svm_problem m_svmprob;
	std::vector<vec2>m_traindata;//��ά�������
	svm_model *m_svmmodel;
	void GetMax_Min(double*pdata,int data_num,double &minpt,double&maxpt);
	double *m_maxx;
	double *m_minx;
	double m_miny;
	double m_maxy;

	

};

