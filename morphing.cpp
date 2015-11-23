//#include "stdafx.h"
#include "morphing.h"

double Line::Getu(Vector2 X)
{
	double X_P_x = X.x - P.x; 
	double X_P_y = X.y - P.y;

	double Q_P_x = Q.x - P.x;
	double Q_P_y = Q.y - P.y;




	double u = ((X_P_x * Q_P_x) + (X_P_y * Q_P_y)) / (len * len)  ;
	return u ;
}





double Line::Getv(Vector2 X){
	double X_P_x = X.x - P.x;
	double X_P_y = X.y - P.y;
	double Q_P_x = Q.x - P.x;
	double Q_P_y = Q.y - P.y;

	double Perp_Q_P_x = Q_P_y ;    //´¹Ïß
	double Perp_Q_P_y = -Q_P_x ;


	double v = ((X_P_x * Perp_Q_P_x) + (X_P_y * Perp_Q_P_y))/len ; 


	return v ; 
}



Vector2 Line::Get_Point(double u , double v)
{
	double Q_P_x = Q.x - P.x;
	double Q_P_y = Q.y - P.y;

	double Perp_Q_P_x = Q_P_y ;  
	double Perp_Q_P_y = -Q_P_x ;



	double Point_x = P.x + u * (Q.x - P.x) + ((v * Perp_Q_P_x)/len) ;
	double Point_y = P.y + u * (Q.y - P.y) + ((v * Perp_Q_P_y)/len) ;


	Vector2 X;
	X.x = Point_x;
	X.y = Point_y;


	return X ;
}



double Line::Get_Weight(Vector2 X )
{
	double a = parameter_a;
	double b = parameter_b;
	double p = parameter_p;
	double d = 0.0;


	double u = Getu(X);


	if(u > 1.0 )
		d = sqrt((X.x - Q.x) * (X.x - Q.x) + (X.y - Q.y) * (X.y - Q.y));
	else if(u < 0)
		d = sqrt((X.x - P.x) * (X.x - P.x) + (X.y - P.y) * (X.y - P.y));
	else
		d = abs(Getv(X));


	double weight =pow(pow((float)len,(float)p)/(a + d) , b);


	return weight; 
}

