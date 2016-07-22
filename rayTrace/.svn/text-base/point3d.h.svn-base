/********************************************************
/	point3d.h
/	Scot Halverson
/	Provides tools for creating and manipulating a three dimensional point
*/

#ifndef POINT3DH
#define POINT3DH 1

#include <string>
#include "vector4d.h"
#include "math.h"
#include <iostream>

using namespace std;

class Point3d {
	public:
		Point3d();
		Point3d(float,float,float);
		~Point3d();
		Point3d operator+(Point3d);
		Point3d operator-();
		Point3d operator+(Vector4d);
		//Point3d operator-(Point3d);
		Vector4d operator-(Point3d);	
		float getX();
		float getY();
		float getZ();
		void print();
	private:
		float v[3];
};

//default constructor
inline Point3d::Point3d(){}

//constructor taking in XYZ values
inline Point3d::Point3d(float x, float y, float z){	
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

//destructor.  nothing needs to be deleted
inline Point3d::~Point3d(){}

//overloaded add operator for a point.  returns another point
inline Point3d Point3d::operator+(Point3d p){
	return Point3d(p.getX() + v[0], p.getY() + v[1], p.getZ() + v[2]);
}

//overloaded sub operator.  negates the given point
inline Point3d Point3d::operator-(){
	return Point3d(-v[0], -v[1], -v[2]);
}

//overloaded sub operator.  generates a vector between two points
inline Vector4d Point3d::operator-(Point3d p){
	return Vector4d(v[0] - p.getX(), v[1] - p.getY(), v[2] - p.getZ());
}

//x accessor
inline float Point3d::getX(){return v[0];}

//y accessor
inline float Point3d::getY(){return v[1];}

//z accessor
inline float Point3d::getZ(){return v[2];}

//prints (cout) the values of the given point
inline void Point3d::print(){cout << v[0] << " " << v[1] << " " << v[2];}

//overloaded add operator.  adds a vector and returns another point
inline Point3d Point3d::operator+(Vector4d vector){
	return Point3d(v[0] + vector.getX(), v[1] + vector.getY(), v[2] + vector.getZ());	
}

#endif
