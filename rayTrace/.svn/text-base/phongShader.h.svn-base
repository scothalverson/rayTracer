/********************************************************
/	phongShader.h
/	Scot Halverson
/	Provides tools for creating and manipulating a Phong shader
*/

#ifndef PHONGSHADERH
#define PHONGSHADERH 1

#include "shader.h"

class PhongShader : public Shader {
	public:
		PhongShader(Color, float, string);
		~PhongShader();
		Color genColor(Light*, Vector4d&, Ray4d&, Point4d&, Color&);
		string getType();
		string getName();
	private:
		float power;
		Color ks;
		string name;
};
// constructor 
inline PhongShader::PhongShader(Color ks, float power, string name){
	this->ks = ks;
	this->power = power;	
	this->name = name;
}

//destructor.  nothing to delete.
inline PhongShader::~PhongShader(){}

//type accessor
inline string PhongShader::getType(){return "Phong";}
//name accessor
inline string PhongShader::getName(){return name;}

#endif
