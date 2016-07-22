/********************************************************
/	vector2d.h
/	Scot Halverson
/	Provides tools for creating and manipulating a two dimensional vector
*/

#ifndef VECTOR2DH
#define VECTOR2DH 1

#include <string>


using namespace std;

class Vector2d {
public:
	Vector2d();  //default constructor
	Vector2d(float,float);  //Contrstuctor with parameters
	virtual ~Vector2d();  //destructor
	float length();  //method to get length
	void set(float,float);  //method to set x & y values
	Vector2d operator+(Vector2d);  //vector addition
	Vector2d operator-(Vector2d);  //vector subtraction
	Vector2d operator*(float);  //scalar multiplication
	float getX();  //X accessor
	float getY();  //Y accessor
	Vector2d normalize();  //normalizes the vector
	float dotProduct(Vector2d);  //computes the dot product of two vectors
	float crossProduct(Vector2d);  //computes the magnitude of the cross product of two vectors
private:
	float v[2];  //array containing X&Y
};

//#include "vector2d.cpp"

#endif /* VECTOR2DH */
