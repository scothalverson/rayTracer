/********************************************************
/	ray3d.h
/	Scot Halverson
/	Provides tools for creating and manipulating a three dimensional ray
*/

#ifndef RAY3DH
#define RAY3DH 1

#include "point3d.h"
#include "vector4d.h"
#include <iostream>
#include "math.h"

using namespace std;

class Ray3d {
	public:
	Ray3d(); //default constructor
	Ray3d(float,float,float,float,float,float); //constructor
	Ray3d(Point3d, Vector4d);
	Ray3d(Point3d, Point3d);
	~Ray3d(); //Destructor
	float getPosX();
	float getPosY();
	float getPosZ();
	float getX();
	float getY();
	float getZ();
	Point3d getOrigin();
	Vector4d getDirection();
	Point3d getS();
	Point3d genPoint(float);
	float length();  //method to get length
	void set(float,float,float,float,float,float);  //method to set values for origin and lengths
	void set(Point3d, Vector4d); //method to set values for origin and direction
	void setS(Point3d);  //sets the S point for the ray (some point intersected by the ray)	
	private:
	Point3d origin, s;  //origin and s points.  s is used in the 3d parametric form of the line, where p(t) = origin + t(s - origin)
	Vector4d direction;  //array containing X,Y,Z  (direction values)
};

inline Ray3d::Ray3d(){}

//contsructor taking in change in posX, posY, x,y,& z
inline Ray3d::Ray3d(float posX, float posY, float posZ, float x, float y, float z) {
	origin = Point3d(posX, posY, posZ);
	direction = Vector4d(x,y,z);	
}

inline Ray3d::Ray3d(Point3d origin, Vector4d direction){
	this->origin = origin;
	this->direction = direction;
}

inline Ray3d::Ray3d(Point3d origin, Point3d s){
	this->origin = origin;
	this->s = s;
	this->direction = origin - s;
}

inline Ray3d::~Ray3d() {}

//Returns the x coordinate of the origin
inline float Ray3d::getPosX(){return origin.getX();}

//Returns the y coordinate of the origin
inline float Ray3d::getPosY(){return origin.getY();}

//Returns the z coordinate of the origin
inline float Ray3d::getPosZ(){return origin.getZ();}

//Returns the x length of the ray
inline float Ray3d::getX(){return direction.getX();}

//Returns the y length of the ray
inline float Ray3d::getY(){return direction.getY();}

//Returns the z length of the ray
inline float Ray3d::getZ(){return direction.getZ();}

inline Point3d Ray3d::getOrigin(){return origin;}

inline Vector4d Ray3d::getDirection(){return direction;}

inline Point3d Ray3d::getS(){return s;}

inline Point3d Ray3d::genPoint(float t){
	return origin + (direction * t); 
}

inline void Ray3d::setS(Point3d s){this->s = s;}

//Returns the length of the ray
inline float Ray3d::length(){
	return sqrt(direction.getX()*direction.getX() + direction.getY()*direction.getY() + direction.getZ()*direction.getZ());
}

//setter method for all internal variables
inline void Ray3d::set(float posX, float posY, float posZ, float x, float y, float z){
	origin = Point3d(posX, posY, posZ);
	direction = Vector4d(x,y,z);	
}

inline void Ray3d::set(Point3d origin, Vector4d direction){
	this->origin = origin;
	this->direction = direction;
}

#endif
