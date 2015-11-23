#pragma once
#include "facepp/faceppapi.h"
#include "Vec.h"
#include <vector>
using namespace std;
class CPupilGUI
{
public:
	CPupilGUI(void);
	~CPupilGUI(void);
	CPupilGUI(BYTE* pImage, int nWidth, int nHeight);
	void Render(CDC*pDC);
	FACEPP_FACEINFO m_face_detection;
	bool isface;
private:
	int m_width;
	int m_height;
	bool face_detection(byte *pData,int nWidth,int nHeight ,FACEPP_FACEINFO  &face0);
	
	byte * ConvertToGray(BYTE* pImage, int nWidth, int nHeight);
	void GenerateCircle(float radius,vec2 center,vector<CPoint>&Reuslt);
	vector<CPoint>m_result;//最后的结果
	vector<CPoint>m_inicir;//初始轮廓
	DWORD m_Times;
};

