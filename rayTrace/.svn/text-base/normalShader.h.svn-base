/********************************************************
/	normalShader.h
/	Scot Halverson
/	Provides tools for creating and manipulating a normal shader
*/

#ifndef NORMALSHADERH
#define NORMALSHADERH 1

#include "shader.h"

class NormalShader : public Shader {
	public:
		NormalShader(string name);
		~NormalShader();
		Color genColor(Light*, Vector4d&, Ray4d&, Point4d&, Color&);
		string getType();
		string getName();
	private:
		string name;
};

//default constructor
inline NormalShader::NormalShader(string name){
	this->name = name;
}

//destructor.  nothing to delete
inline NormalShader::~NormalShader(){}

//determine the color of an object at a given point
inline Color NormalShader::genColor(Light* l, Vector4d& normal, Ray4d& r, Point4d& p, Color& c){
	return Color((normal.getX() + 1)/2, (normal.getY() + 1)/2, (normal.getZ() + 1)/2);
}

//type accessor
inline string NormalShader::getType(){return "Normal";}

//name accessor
inline string NormalShader::getName(){return name;}
#endif
