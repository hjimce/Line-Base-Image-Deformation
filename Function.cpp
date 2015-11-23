//#include "StdAfx.h"
#include "Function.h"

int mlength=20;
int g_CtrlIndex[20] = {
//脸型10
1,2,
2,3,
3,4,
4,5,
5,0,
0,10,
10,9,
9,8,
8,7,
7,6
};

Function::Function(void)
{


}


Function::~Function(void)
{

}

void Function::bilinear(cv::Mat psrcImgData,float X ,float Y,cv::Vec3b &resultpiexl)
{
	int x_floor = (int)X ;
	int y_floor = (int)Y ;
	int x_ceil = x_floor + 1 ;
	int y_ceil = y_floor + 1 ;
	float a = X - x_floor ;
	float b = Y - y_floor ;

	if(x_ceil >= psrcImgData.cols-1) 
		x_ceil =psrcImgData.cols-1 ;
	if(y_ceil >= psrcImgData.rows-1) 
		y_ceil = psrcImgData.rows-1 ;


	cv::Vec3b leftdown; 
	cv::Vec3b lefttop; 
	cv::Vec3b rightdown; 
	cv::Vec3b righttop; 
    Get2D(psrcImgData,y_floor,x_floor,leftdown);
	Get2D(psrcImgData,y_ceil,x_floor,lefttop);
	Get2D(psrcImgData,y_floor,x_ceil,rightdown);
	Get2D(psrcImgData,y_ceil,x_ceil,righttop);



	resultpiexl=(1-a)*(1-b)*leftdown+ a*(1-b)*rightdown+a*b*righttop+(1-a)*b*lefttop;
}


void Function::Get2D(cv::Mat psrcImgData, int Y,int X, cv::Vec3b &piexl)
{
	piexl=psrcImgData.at<cv::Vec3b>(Y,X);
}


void Function::Warp(cv::Mat pleftImgData, cv::Mat &prightImgData,vector<cv::Vec2f> srcPtList, vector<cv::Vec2f> exPtList)
{

	//exPtList=GetFaceTransformation(srcPtList,exPtList);
	exPtList=Similarity_transform_2d(exPtList,srcPtList);//相似变换

	for (int i=0;i<exPtList.size();i++)
	{
		float x=exPtList[i][0];
		float y=exPtList[i][1];


		float x1=srcPtList[i][0];
		float y1=srcPtList[i][1];

	}


	prightImgData=pleftImgData.clone();

	int aa=prightImgData.channels();
	aa=0;
	int nLength =mlength;
	vector<struct LinePair> pairs;



	for (int i=0; i<nLength; i+= 2)
	{
		int indexp = g_CtrlIndex[i];
		int indexq = g_CtrlIndex[i + 1];
		LinePair curLinePair;
		curLinePair.leftLine.P.x =(int)srcPtList[indexp][0];
		curLinePair.leftLine.P.y =(int)srcPtList[indexp][1];
		curLinePair.leftLine.Q.x =(int)srcPtList[indexq][0];
		curLinePair.leftLine.Q.y =(int)srcPtList[indexq][1];


		Line  curLine=curLinePair.leftLine;


		float curLen=sqrt((curLine.Q.x-curLine.P.x)*(curLine.Q.x-curLine.P.x)+(curLine.Q.y-curLine.P.y)*(curLine.Q.y-curLine.P.y));
		curLinePair.leftLine.len=curLen;

		curLinePair.rightLine.P.x =(int)exPtList[indexp][0];
		curLinePair.rightLine.P.y =(int)exPtList[indexp][1];
		curLinePair.rightLine.Q.x =(int)exPtList[indexq][0];
		curLinePair.rightLine.Q.y =(int)exPtList[indexq][1];


		curLine=curLinePair.rightLine;
		curLen=sqrt((curLine.Q.x-curLine.P.x)*(curLine.Q.x-curLine.P.x)+(curLine.Q.y-curLine.P.y)*(curLine.Q.y-curLine.P.y));

		curLinePair.rightLine.len=curLen;


		pairs.push_back(curLinePair);

	}




	int nWidth=prightImgData.cols;
	int nHeight=prightImgData.rows;
    for(int x = 0 ; x < nWidth ; x++)
	{
        for(int y = 0 ; y < nHeight ; y++)
		{
			Vector2 dst_point ;
			dst_point.x= x ; 
			dst_point.y= y;
			double leftXSum_x = 0.0;
			double leftXSum_y = 0.0;
			double leftWeightSum = 0.0;
			double rightXSum_x = 0.0;
			double rightXSum_y = 0.0;
			double rightWeightSum = 0.0;
			for(int i = 0 ; i < pairs.size() ; i++)
			{

				Line src_line = pairs[i].leftLine;	
				Line dst_line = pairs[i].rightLine;

				double new_u = dst_line.Getu(dst_point);
				double new_v = dst_line.Getv(dst_point);

				Vector2 src_point = src_line.Get_Point(new_u , new_v);
				double src_weight = dst_line.Get_Weight(dst_point);

				leftXSum_x = leftXSum_x + (double)src_point.x * src_weight ;
				leftXSum_y = leftXSum_y + (double)src_point.y * src_weight ;
				leftWeightSum = leftWeightSum + src_weight ;
			}
			double left_src_x = leftXSum_x / leftWeightSum;
			double left_src_y = leftXSum_y / leftWeightSum;
			double right_src_x = x;
			double right_src_y = y;


			if(left_src_x<0)
				left_src_x=0;
			if(left_src_y<0)
				left_src_y=0;
			if(left_src_x>=pleftImgData.cols)
				left_src_x=pleftImgData.cols-1;
			if(left_src_y>=pleftImgData.rows)
				left_src_y=pleftImgData.rows-1;


			cv::Vec3b leftimg;
			bilinear(pleftImgData,left_src_x,left_src_y,leftimg);


			prightImgData.at<cv::Vec3b>(y,x)=leftimg;
        }
    }

}

//算法通过固定脸庞上的1、13号点，对这两个点进行变换对齐，face2_landmark往face1_landmark进行对齐变换
vector<cv::Vec2f> Function::GetFaceTransformation(vector<cv::Vec2f>face1_landmark,vector<cv::Vec2f>face2_landmark)
{
	float sum_dis=0;
	vector<cv::Vec2f>result0;
	Eigen::Matrix2d tm=Transform_Line_Segment(face1_landmark[1],face1_landmark[13],face2_landmark[1],face2_landmark[13]);
	Eigen::Vector2d Line1P(face2_landmark[1][0],face2_landmark[1][1]);
	Eigen::Vector2d Movv(face1_landmark[1][0],face1_landmark[1][1]);
	for (int i=0;i<face2_landmark.size();i++)
	{
		Eigen::Vector2d pt(face2_landmark[i][0],face2_landmark[i][1]);
		Eigen::Vector2d dst_point_eigen=pt-Line1P;
		Eigen::Vector2d src_point_eigen=tm*dst_point_eigen+Movv;//变换后的点
		result0.push_back(cv::Vec2f(src_point_eigen(0),src_point_eigen(1)));

	}
	return result0;
}

//计算两个线段之间的变换矩阵，求解线段（Line2P,Line2Q）往（Line1P,Line1Q）的变换矩阵
Eigen::Matrix2d Function::Transform_Line_Segment(cv::Vec2f Line1P,cv::Vec2f Line1Q,cv::Vec2f Line2P,cv::Vec2f Line2Q)
{
	Eigen::Vector2d A;
	Eigen::Vector2d B;
	A(0)=Line1P[0];
	A(1)=Line1P[1];
	B(0)=Line1Q[0];
	B(1)=Line1Q[1];

	Eigen::Vector2d C;
	Eigen::Vector2d D;
	C(0)=Line2P[0];
	C(1)=Line2P[1];
	D(0)=Line2Q[0];
	D(1)=Line2Q[1];

	Eigen::Vector2d cd=D-C;
	Eigen::Vector2d ab=B-A;

	Eigen::Matrix2d cof;
	cof(0,0)=cd(0);
	cof(0,1)=cd(1);
	cof(1,0)=cd(1);
	cof(1,1)=-cd(0);
	Eigen::Vector2d tr=cof.inverse()*ab;

	cof(0,0)=tr(0);
	cof(0,1)=tr(1);
	cof(1,0)=-tr(1);
	cof(1,1)=tr(0);

	return cof;
}

vector<cv::Vec2f> Function::Similarity_transform_2d(vector<cv::Vec2f> src,vector<cv::Vec2f>ref)
{
	vector<cv::Vec2f>dst;
	using namespace Eigen;
	int count=ref.size();
	dst.resize(count);
	assert(count >= 3);
	Eigen::Matrix<float, Dynamic, Dynamic> A(2 * count, 4), X, B(2 * count, 1), S;
	for (int i = 0; i < count; i++)
	{
		A(i, 0) = src[i][0];
		A(i, 1) = src[i][1];
		A(i, 2) = 1;
		A(i, 3) = 0;
		A(i + count, 0) = src[i][1];
		A(i + count, 1) = -src[i][0];
		A(i + count, 2) = 0;
		A(i + count, 3) = 1;
		B(i, 0) = ref[i][0];
		B(i + count, 0) = ref[i][1];
	}

	X = A.jacobiSvd(ComputeThinU | ComputeThinV).solve(B);
	Eigen::Matrix<float, 2, 3> M;
	M << X(0, 0), X(1, 0), X(2, 0), -X(1, 0), X(0, 0), X(3, 0);

	for (int i = 0; i < count; i++)
	{
		dst[i][0]= M(0, 0) * src[i][0]+ M(0, 1) * src[i][1]+ M(0, 2);
		dst[i][1]= M(1, 0) * src[i][0]+ M(1, 1) * src[i][1]+ M(1, 2);
	}
	return dst;
}


