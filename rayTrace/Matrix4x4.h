/********************************************************
/	Matrix4x4.h
/	Scot Halverson
/	Provides tools for creating and manipulating a four dimensional matrix
*/

#ifndef MATRIX4X4H
#define MATRIX4X4H 1

#include "vector4d.h"
#include <string>
#include "point4d.h"

class Matrix4x4
{
public:
	public:
	Matrix4x4(); //Default constructor	
	~Matrix4x4(); //Default Destructor
	void set2Identity(); // clears the matrix to the identity matrix
	Matrix4x4 transpose(); // returns the transpose
	float get(int i, int j); // returns the value at index i,j
	Matrix4x4 operator+(Matrix4x4); //Addition of two matrices
	Matrix4x4 operator-(Matrix4x4); //Subtraction of one Matrix from another
	Matrix4x4 operator*(Matrix4x4); //Matrix multiplication
	Vector4d operator*(Vector4d);//vector multipliplication
	Point4d operator*(Point4d);//vector multipliplication
	Matrix4x4 operator*(float); //scalar multiplication
	Matrix4x4 scale(float, float, float, float);//scale individual dimensions
	Matrix4x4 transform(float, float, float, float); //transform individual dimensions
	Matrix4x4 rotX(float); //rotate about X axis
	Matrix4x4 rotY(float); //rotate about Y axis
	Matrix4x4 rotZ(float);	//rotate about Z axis
	Matrix4x4 shear(float xy, float xz, float yx, float yz, float zx, float zy);  //matrix shear
	string ToString();
	

private:
	void set(float[4][4] ); // sets the 16 values in the matrix 
	float m[4][4];
};


//Default Constructor
inline Matrix4x4::Matrix4x4(){
	this->set2Identity();
}

//Default Destructor
inline Matrix4x4::~Matrix4x4(){}

//Returns the value at index i,j
inline float Matrix4x4::get(int i, int j){
	return m[i][j];
}

#endif
