/********************************************************
/	vector4d.h
/	Scot Halverson
/	Provides tools for creating and manipulating a four dimensional vector
*/

#ifndef VECTOR4DH
#define VECTOR4DH 1

#include <string>
#include "math.h"
#include "vector3d.h"


using namespace std;

class Vector4d
{
public:
	Vector4d();  //default constructor
	Vector4d(float,float,float,float);  //Contrstuctor with parameters
	Vector4d(Vector3d);  //Contrstuctor using a 3d vector. This allows implicit type casting from vector3d to vector4d
	float length();  //method to get length
	void set(float,float,float,float);  //method to set x,y,z,w values

	Vector4d operator+(Vector4d);  //vector addition
	Vector4d operator-(Vector4d);  //vector subtraction
	void operator=(Vector4d);  //assignment
	Vector4d operator*(float);  //scalar multiplication
	Vector4d operator-(); //vector negation

	float dotProduct(Vector4d);  //computes the dot product of two vectors
	float operator*(Vector4d); // calls the dot product function
	Vector4d crossProduct(Vector4d);  //computes the cross product of two 3d vectors
	
	float getX(){return v[0];};  //X accessor
	float getY(){return v[1];};  //Y accessor
	float getZ(){return v[2];};	//Z accessor
	float getW(){return v[3];};	//W accessor
	Vector4d normalize();  //normalizes the vector
private:
	float v[4];  //array containing X,Y,Z,W
};

inline Vector4d::Vector4d(){}

inline Vector4d::Vector4d(float x, float y, float z, float w = 1) {
	this->v[0] = x;
	this->v[1] = y;
	this->v[2] = z;
	this->v[3] = w;
}

inline Vector4d::Vector4d(Vector3d v3d) {
	this->v[0] = v3d.getX();
	this->v[1] = v3d.getY();
	this->v[2] = v3d.getZ();
	this->v[3] = 1;
}

inline float Vector4d::length(){
	return sqrt(v[2]*v[2] + v[1]*v[1] + v[0]*v[0]);
}

// set method.  w is given a default value of 1 for any case where a Vector3d object was replaced
// with a Vector4d object, and the old set method call was not updated
inline void Vector4d::set(float x, float y, float z, float w = 1){
	this->v[0] = x;
	this->v[1] = y;
	this->v[2] = z;
	this->v[3] = w;
}

inline Vector4d Vector4d::operator +(Vector4d v2){
	return Vector4d(this->getX() + v2.getX(), this->getY() + v2.getY(), this->getZ() + v2.getZ(), 1);
}

inline Vector4d Vector4d::operator -(Vector4d v2){
	return Vector4d(this->getX() - v2.getX(), this->getY() - v2.getY(), this->getZ() - v2.getZ(), 1);
}

inline Vector4d Vector4d::operator *(float scalar){
	return Vector4d(this->getX()*scalar, this->getY() * scalar, this->getZ() * scalar, 1);
}

inline Vector4d Vector4d::normalize(){
	float div = (1/this->length());
	return Vector4d(this->getX()*div, this->getY()*div, this->getZ()*div, 1);
}

//creates a vector that is perpendicular to the two given vectors.  
inline Vector4d Vector4d::crossProduct(Vector4d v2){
	float x = (this->getY() * v2.getZ()) - (v2.getY() * this->getZ());
	float y = (this->getZ() * v2.getX()) - (v2.getZ() * this->getX());
	float z = (this->getX() * v2.getY()) - (v2.getX() * this->getY());

	return Vector4d(x,y,z,1);
}

inline float Vector4d::operator*(Vector4d v2){
	return dotProduct(v2);
}

//computes the dot product of two vectors
inline float Vector4d::dotProduct(Vector4d v2){
	return ((this->getX() * v2.getX()) + (this->getY() * v2.getY()) + (this->getZ() * v2.getZ()));
}

inline Vector4d Vector4d::operator -(){
	return Vector4d(this->getX() * -1, this->getY() * -1, this->getZ() * -1, 1);
}

inline void Vector4d::operator=(Vector4d vec){
	v[0] = vec.v[0];
	v[1] = vec.v[1];
	v[2] = vec.v[2];
	v[3] = vec.v[3];
}

#endif
