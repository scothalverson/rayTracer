#include "Matrix4x4.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "vector3d.h"
#include "vector4d.h"
#include "math.h"

using namespace std;


//Sets the 16 values in the matrix via 4*4 array of floats
void Matrix4x4::set(float newMatrix[4][4]){
	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			m[a][b] = newMatrix[a][b];
		}
	}
}

//Clears the matrix to the identity matrix
void Matrix4x4::set2Identity(){
	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			if (a == b){
				m[a][b] = 1.0;
			}
			else {
				m[a][b] = 0.0;
			}
		}
	}
}

//Returns a string representation of the 4x4 matrix
string Matrix4x4::ToString(){
	string s;
	ostringstream oss;
	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			oss << m[a][b] << " ";
		}
		oss << endl;
	}
	return oss.str();
}

//Returns the transpose of the matrix
Matrix4x4 Matrix4x4::transpose(){
	Matrix4x4 mat;
	float mV[4][4];

	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			mV[a][b] = m[b][a];
		}
	}
	mat.set(mV);
	return mat;
}



//Addition of two matrices
Matrix4x4 Matrix4x4::operator+(Matrix4x4 second){
	float newMat[4][4];
	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			newMat[a][b] = m[a][b] + second.get(a,b);
		}
	}
	Matrix4x4 newM;
	newM.set(newMat);
	return newM;
}

//Subtraction of one Matrix from another 
Matrix4x4 Matrix4x4::operator-(Matrix4x4 second){
float newMat[4][4];
	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			newMat[a][b] = m[a][b] - second.get(a,b);
		}
	}
	Matrix4x4 newM;
	newM.set(newMat);
	return newM;
}

//Matrix multiplication 
Matrix4x4 Matrix4x4::operator*(Matrix4x4 second){
	Matrix4x4 mat;
	float mV[4][4];

	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			mV[a][b] = m[a][0] * second.get(0, b) + m[a][1] * second.get(1, b) +  m[a][2] * second.get(2, b) + m[a][3] * second.get(3, b);
			/*cout << m[a][0] << " " << second.get(0, b) << endl;
			cout << m[a][1] << " " << second.get(1, b) << endl;
			cout << m[a][2] << " " << second.get(2, b) << endl;
			cout << m[a][3] << " " << second.get(3, b) << endl;*/
		}
	}

	mat.set(mV);

	//cout << mat.ToString();
	return mat;
}

//Matrix-Vector multiplication
Vector4d Matrix4x4::operator*(Vector4d vector){
  float vals[4];
  float orig[4];
	
  orig[0] = vector.getX();
  orig[1] = vector.getY();
  orig[2] = vector.getZ();
  orig[3] = vector.getW();
  for (int a = 0; a < 4; a++){
    vals[a] = orig[0] * m[a][0] + orig[1] * m[a][1] + orig[2] * m[a][2] + orig[3] * m[a][3];
  }
  return Vector4d(vals[0], vals[1], vals[2], vals[3]);
}

//Matrix-point multiplication
Point4d Matrix4x4::operator*(Point4d point){
  float vals[4];
  float orig[4];
	
  orig[0] = point.getX();
  orig[1] = point.getY();
  orig[2] = point.getZ();
  orig[3] = point.getW();
  for (int a = 0; a < 4; a++){
    vals[a] = orig[0] * m[a][0] + orig[1] * m[a][1] + orig[2] * m[a][2] + orig[3] * m[a][3];
  }
  return Point4d(vals[0], vals[1], vals[2], vals[3]);
}

//Matrix-scalar multiplication
Matrix4x4 Matrix4x4::operator*(float scalar){
	Matrix4x4 mat;
	Matrix4x4 mati;
	float mV[4][4];
	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			mV[a][b] = m[a][b] * scalar;
		}
	}
	mat.set(mV);
	return mat;
}

//Matrix dimensional scale
Matrix4x4 Matrix4x4::scale(float scalarX, float scalarY, float scalarZ, float scalarW){
	Matrix4x4 mat;
	float mV[4][4];
	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			mV[a][b] = 0.0;
		}
	}
	mV[0][0] = scalarX;
	mV[1][1] = scalarY;
	mV[2][2] = scalarZ;
	mV[3][3] = scalarW;	
	mat.set(mV);
	return this->operator*(mat);
}

//Matrix transformation
Matrix4x4 Matrix4x4::transform(float transformX, float transformY, float transformZ, float transformW){
	Matrix4x4 mat;
	float mV[4][4];
	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			if (a == b){
				mV[a][b] = 1.0;
			}
			else{
				mV[a][b] = 0.0;
			}
		}
	}
	mV[3][0] = transformX;
	mV[3][1] = transformY;
	mV[3][2] = transformZ;
	mV[3][3] = transformW;	
	mat.set(mV);
	return this->operator*(mat);
}

Matrix4x4 Matrix4x4::rotX(float theta){
	Matrix4x4 mat;
	float mV[4][4];
	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			mV[a][b] = 0.0;
		}
	}
	mV[0][0] = 1;
	mV[1][1] = cos(theta);
	mV[1][2] = -sin(theta);
	mV[2][1] = sin(theta);
	mV[2][2] = cos(theta);
	mV[3][3] = 1;
	mat.set(mV);
	return this->operator*(mat);
}

Matrix4x4 Matrix4x4::rotY(float theta){
	Matrix4x4 mat;
	float mV[4][4];
	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			mV[a][b] = 0.0;
		}
	}
	mV[0][0] = cos(theta);	
	mV[0][2] = -sin(theta);
	mV[1][1] = 1;
	mV[2][0] = sin(theta);
	mV[2][2] = cos(theta);
	mV[3][3] = 1;
	mat.set(mV);
	return this->operator*(mat);
}

Matrix4x4 Matrix4x4::rotZ(float theta){
	Matrix4x4 mat;
	float mV[4][4];
	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			mV[a][b] = 0.0;
		}
	}
	mV[0][0] = cos(theta);
	mV[0][1] = -sin(theta);
	mV[1][0] = sin(theta);
	mV[1][1] = cos(theta);
	mV[2][2] = 1;
	mV[3][3] = 1;
	mat.set(mV);
	return this->operator*(mat);
}

Matrix4x4 Matrix4x4::shear(float xy, float xz, float yx, float yz, float zx, float zy){
	Matrix4x4 mat;
	float mV[4][4];
	for (int a = 0; a < 4; a++){
		for (int b = 0; b < 4; b++){
			mV[a][b] = 0.0;
		}
	}
	mV[0][0] = 1;
	mV[1][1] = 1;
	mV[2][2] = 1;
	mV[3][3] = 1;
	mV[0][1] = xy;
	mV[0][2] = xz;
	mV[1][0] = yx;
	mV[1][2] = yz;
	mV[2][0] = zx;
	mV[2][1] = zy;
	mat.set(mV);
	return this->operator*(mat);
}

