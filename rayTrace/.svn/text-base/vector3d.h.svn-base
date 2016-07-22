/********************************************************
/	vector3d.h
/	Scot Halverson
/	Provides tools for creating and manipulating a three dimensional vector
*/

#ifndef VECTOR3DH
#define VECTOR3DH 1

#include <iostream>
#include "math.h"
#include <string>

using namespace std;

class Vector3d {
public:
	Vector3d();  //default constructor
	Vector3d(float,float,float);  //Contrstuctor with parameters
	//Vector3d(Vector4d);  //Contrstuctor taking in Vector4d
	virtual ~Vector3d();  //destructor
	float length();  //method to get length
	void set(float,float,float);  //method to set x & y values
	Vector3d operator+(Vector3d);  //vector addition
	Vector3d operator-(Vector3d);  //vector subtraction
	Vector3d operator-();  //vector negation
	Vector3d operator*(float);  //scalar multiplication
	float getX();  //X accessor
	float getY();  //Y accessor
	float getZ();	//Z accessor
	Vector3d normalize();  //normalizes the vector
	float dotProduct(Vector3d);  //computes the dot product of two vectors
	float operator*(Vector3d); // calls the dot product function
	Vector3d crossProduct(Vector3d);  //computes the cross product of two 3d vectors
private:
	float v[3];  //array containing X,Y,Z
};

inline Vector3d::Vector3d(){}

//contsructor taking in change in x,y,& z
inline Vector3d::Vector3d(float x, float y, float z) {
	this->v[0] = x;
	this->v[1] = y;
	this->v[2] = z;
}
//constructor taking in a vector4d
/*inline Vector3d::Vector3d(Vector4d vec) {
	this->v[0] = vec.getX();
	this->v[1] = vec.getY();
	this->v[2] = vec.getZ();
}*/

inline Vector3d::~Vector3d() {}

//Returns the length of the vector
inline float Vector3d::length(){
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

//Provides a means for changing the x,y,z values for the vector
inline void Vector3d::set(float x, float y, float z){
	this->v[0] = x;
	this->v[1] = y;
	this->v[2] = z;
}

//Provides a means for adding two 3d vectors 
inline Vector3d Vector3d::operator +(Vector3d v2){
	return Vector3d(this->getX() + v2.getX(), this->getY() + v2.getY(), this->getZ() + v2.getZ());
}

//Provides a means for subtracting one 3d vector from another
inline Vector3d Vector3d::operator -(Vector3d v2){
	return Vector3d(this->getX() - v2.getX(), this->getY() - v2.getY(), this->getZ() - v2.getZ());
}

inline Vector3d Vector3d::operator -(){
	return Vector3d(this->getX() * -1, this->getY() * -1, this->getZ() * -1);
}

//Multiplies the vector by a contstant/scalar
inline Vector3d Vector3d::operator *(float scalar){
	return Vector3d(this->getX()*scalar, this->getY() * scalar, this->getZ() * scalar);
}

//creates a unit vector parallel to the vector
inline Vector3d Vector3d::normalize(){
	float div = (1/this->length());
	return Vector3d(this->getX()*div, this->getY()*div, this->getZ()*div);
}

//computes the dot product of two vectors
inline float Vector3d::dotProduct(Vector3d v2){
	return ((this->getX() * v2.getX()) + (this->getY() * v2.getY()) + (this->getZ() * v2.getZ()));
}

inline float Vector3d::operator*(Vector3d v2){
	return dotProduct(v2);
}

//creates a vector that is perpendicular to the two given vectors.  
inline Vector3d Vector3d::crossProduct(Vector3d v2){
	float x = (this->getY() * v2.getZ()) - (v2.getY() * this->getZ());
	float y = (this->getZ() * v2.getX()) - (v2.getZ() * this->getX());
	float z = (this->getX() * v2.getY()) - (v2.getX() * this->getY());

	return Vector3d(x,y,z);
}

//accessor for X
inline float Vector3d::getX(){
	return v[0];
}

//accessor for Y
inline float Vector3d::getY(){
	return v[1];
}

//accessor for Z
inline float Vector3d::getZ(){
	return v[2];
}

#endif /* VECTOR3DH */
