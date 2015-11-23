#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Vectors.h"
using namespace std;

#ifndef __MT_MORPHING_147J__

#define __MT_MORPHING_147J__

struct Line
{
	Line()
	{
		parameter_a = 1.0;
		parameter_b = 2.0;
		parameter_p = 0.0;
	}




	Vector2 P; //start 
	Vector2 Q; //end
	float parameter_a;
	float parameter_b;
	float parameter_p;
	float len;


	double Getu(Vector2 X);
	double Getv(Vector2 X);
	Vector2 Get_Point(double u , double v);
	double Get_Weight(Vector2 X);
};


struct LinePair
{
	Line leftLine;
	Line rightLine;
	Line warpLine;

};


#endif //#ifndef __MT_MORPHING_147J__