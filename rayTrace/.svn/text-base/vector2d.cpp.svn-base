/********************************************************
/	vector2d.cpp
/	Scot Halverson
/	Provides tools for creating and manipulating a two dimensional vector
*/
#include "vector2d.h"
#include <iostream>
#include "math.h"

using namespace std;

inline Vector2d::Vector2d(){}

//constructor:  takes in the change in x and change in y associated with the vector
inline Vector2d::Vector2d(float x, float y) {
	this->v[0] = x;
	this->v[1] = y;
}

inline Vector2d::~Vector2d() {}

//Returns the length of the vector
inline float Vector2d::length(){
	return sqrt(v[0]*v[0] + v[1]*v[1]);
}


//Provides a means for changing the vector
inline void Vector2d::set(float x, float y){
	this->v[0] = x;
	this->v[1] = y;
}

//Provides a means for adding two vectors together
inline Vector2d Vector2d::operator +(Vector2d v2){
	return Vector2d(this->v[0] + v2.getX(), this->v[1] + v2.getY());
}

//Provides a means for subtracting one vector from another
inline Vector2d Vector2d::operator -(Vector2d v2){
	return Vector2d(this->v[0] - v2.getX(), this->v[1] - v2.getY());
}

//Multiplies the vector by a constant/scalar
inline Vector2d Vector2d::operator *(float scalar){
	return Vector2d(this->getX()*scalar, this->getY()*scalar);
}

//crates a unit vector parallel to the vector
inline Vector2d Vector2d::normalize(){
	float div = ( 1 / this->length());

	return Vector2d(this->getX()*div, this->getY()*div);
}

//computes the dot product of two 2d vectors
inline float Vector2d::dotProduct(Vector2d v2){
	return (this->getX() * v2.getX() + this->getY() * v2.getY());
}

//computes the magnitude of the cross product of two 2d vectors
float Vector2d::crossProduct(Vector2d v2){
	Vector2d nv1 = this->normalize();
	Vector2d nv2 = v2.normalize();
	float length1 = this->length();
	float length2 = v2.length();

	return (length1 * length2 * sqrt(1 - (nv1.dotProduct(nv2))*(nv1.dotProduct(nv2))));
}

//Provides a means for accessing the X value
inline float Vector2d::getX(){
	return v[0];
}

//Provides a means for accessing the Y value
inline float Vector2d::getY(){
	return v[1];
}


