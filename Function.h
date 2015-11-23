#include <vector>
#include "Vectors.h"
#include "morphing.h"
#include "Eigen/Eigen"
#include <opencv2/core.hpp>
using namespace std;

#pragma once
class Function
{
public:
	Function(void);
	~Function(void);
	void Warp(cv::Mat pleftImgData, cv::Mat &prightImgData,vector<cv::Vec2f> srcPtList, vector<cv::Vec2f> exPtList);
private:
	vector<cv::Vec2f> GetFaceTransformation(vector<cv::Vec2f>face1_landmark,vector<cv::Vec2f>face2_landmark);
	Eigen::Matrix2d Transform_Line_Segment(cv::Vec2f Line1P,cv::Vec2f Line1Q,cv::Vec2f Line2P,cv::Vec2f Line2Q);
	void Get2D(cv::Mat psrcImgData, int Y,int X, cv::Vec3b &piexl);
	void bilinear(cv::Mat psrcImgData, float X,float Y,cv::Vec3b &piexl);
	vector<cv::Vec2f> Similarity_transform_2d(vector<cv::Vec2f> src,vector<cv::Vec2f>ref);
	

};

