/********************************************************
/	point4d.h
/	Scot Halverson
/	Provides tools for creating and manipulating a three dimensional point
*/

#ifndef POINT4DH
#define POINT4DH 1

#include <string>
#include "point3d.h"
#include "vector4d.h"
#include "math.h"
#include <iostream>

using namespace std;

class Point4d {
	public:
		Point4d();
		Point4d(float,float,float,float);
		Point4d(Point3d);
		~Point4d();
		Point4d operator+(Point4d);
		Point4d operator-();
		Point4d operator+(Vector4d);
		//Point4d operator-(Point4d);
		Vector4d operator-(Point4d);	
		float getX();
		float getY();
		float getZ();
		float getW();
		void print();
	private:
		float v[4];
};

//default constructor
inline Point4d::Point4d(){}

//constructor taking in XYZW values
inline Point4d::Point4d(float x, float y, float z, float w = 1.0){	
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

//constructor taking in a Point3d object
inline Point4d::Point4d(Point3d p3d){	
	v[0] = p3d.getX();
	v[1] = p3d.getY();
	v[2] = p3d.getZ();
	v[3] = 1;
}

//destructor.  nothing needs to be deleted
inline Point4d::~Point4d(){}

//overloaded add operator for a point.  returns another point
inline Point4d Point4d::operator+(Point4d p){
	return Point4d(p.getX() + v[0], p.getY() + v[1], p.getZ() + v[2], p.getW() + v[3]);
}

//overloaded sub operator.  negates the given point
inline Point4d Point4d::operator-(){
	return Point4d(-v[0], -v[1], -v[2], -v[3]);
}

//overloaded sub operator.  generates a vector between two points
inline Vector4d Point4d::operator-(Point4d p){
	return Vector4d(v[0] - p.getX(), v[1] - p.getY(), v[2] - p.getZ(), v[3] - p.getW());
}

//x accessor
inline float Point4d::getX(){return v[0];}

//y accessor
inline float Point4d::getY(){return v[1];}

//z accessor
inline float Point4d::getZ(){return v[2];}

//w accessor
inline float Point4d::getW(){return v[3];}

//prints (cout) the values of the given point
inline void Point4d::print(){cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3];}

//overloaded add operator.  adds a vector and returns another point
inline Point4d Point4d::operator+(Vector4d vector){
	return Point4d(v[0] + vector.getX(), v[1] + vector.getY(), v[2] + vector.getZ(), v[3] + vector.getW());	
}

#endif
