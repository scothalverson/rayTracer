/********************************************************
/	ray4d.h
/	Scot Halverson
/	Provides tools for creating and manipulating a three dimensional ray
*/

#ifndef RAY4DH
#define RAY4DH 1

#include "point4d.h"
#include "vector4d.h"
#include <iostream>
#include "math.h"

using namespace std;

class Ray4d {
	public:
	Ray4d(); //default constructor
	Ray4d(float,float,float,float,float,float); //constructor
	Ray4d(Point4d&, Vector4d&);
	Ray4d(Point4d&, Point4d&);
	~Ray4d(); //Destructor
	float getPosX();
	float getPosY();
	float getPosZ();
	float getPosW();
	float getX();
	float getY();
	float getZ();
	float getW();
	Point4d getOrigin();
	Vector4d getDirection();
	Vector4d* getDirPtr();
	Point4d getS();
	Point4d genPoint(float);
	float length();  //method to get length
	void set(float,float,float,float,float,float);  //method to set values for origin and lengths
	void set(Point4d&, Vector4d&); //method to set values for origin and direction
	void setS(Point4d&);  //sets the S point for the ray (some point intersected by the ray)
	int sampleX, sampleY, maxSampleX, maxSampleY;	
	private:
	Point4d origin, s;  //origin and s points.  s is used in the 3d parametric form of the line, where p(t) = origin + t(s - origin)
	Vector4d direction;  //array containing X,Y,Z  (direction values)
};

inline Ray4d::Ray4d(){}

//contsructor taking in change in posX, posY, x,y,& z
inline Ray4d::Ray4d(float posX, float posY, float posZ, float x, float y, float z) {
	origin = Point4d(posX, posY, posZ,1);
	direction = Vector4d(x,y,z,0);	
}

inline Ray4d::Ray4d(Point4d& origin, Vector4d& direction){
	this->origin = origin;
	this->direction = direction;
}

inline Ray4d::Ray4d(Point4d& origin, Point4d& s){
	this->origin = origin;
	this->s = s;
	this->direction = origin - s;
}

inline Ray4d::~Ray4d() {}

//Returns the x coordinate of the origin
inline float Ray4d::getPosX(){return origin.getX();}

//Returns the y coordinate of the origin
inline float Ray4d::getPosY(){return origin.getY();}

//Returns the z coordinate of the origin
inline float Ray4d::getPosZ(){return origin.getZ();}

//Returns the w coordinate of the origin
inline float Ray4d::getPosW(){return origin.getW();}

//Returns the x length of the ray
inline float Ray4d::getX(){return direction.getX();}

//Returns the y length of the ray
inline float Ray4d::getY(){return direction.getY();}

//Returns the z length of the ray
inline float Ray4d::getZ(){return direction.getZ();}

//Returns the w length of the ray
inline float Ray4d::getW(){return direction.getW();}

inline Point4d Ray4d::getOrigin(){return origin;}

inline Vector4d Ray4d::getDirection(){return direction;}

inline Vector4d* Ray4d::getDirPtr(){return &direction;}

inline Point4d Ray4d::getS(){return s;}

inline Point4d Ray4d::genPoint(float t){
	return origin + (direction * t); 
}

inline void Ray4d::setS(Point4d& s){this->s = s;}

//Returns the length of the ray
inline float Ray4d::length(){
	return sqrt(direction.getX()*direction.getX() + direction.getY()*direction.getY() + direction.getZ()*direction.getZ());
}

//setter method for all internal variables
inline void Ray4d::set(float posX, float posY, float posZ, float x, float y, float z){
	origin = Point4d(posX, posY, posZ);
	direction = Vector4d(x,y,z);	
}

inline void Ray4d::set(Point4d& origin, Vector4d& direction){
	this->origin = origin;
	this->direction = direction;
}

#endif
