/********************************************************
/	blinnPhongShader.h
/	Scot Halverson
/	Provides tools for creating and manipulating a Blinn Phong shader
*/

#ifndef BLINNPHONGSHADERH
#define BLINNPHONGSHADERH 1

#include "shader.h"

class BlinnPhongShader : public Shader {
	public:
		BlinnPhongShader(Color&, float, string);
		~BlinnPhongShader();
		Color genColor(Light*, Vector4d&, Ray4d&, Point4d&, Color&);
		string getType();
		string getName();
	private:
		float power;
		Color ks;
		string name;
};

//constructor
inline BlinnPhongShader::BlinnPhongShader(Color& ks, float power, string name){
	this->ks = ks;
	this->power = power;
	this->name = name;	
}

//destructor - so far, this doesn't need to do anything
inline BlinnPhongShader::~BlinnPhongShader(){}

//self-explanitory...
inline string BlinnPhongShader::getType(){return "Blinn Phong";}

//self-explanitory...
inline string BlinnPhongShader::getName(){return name;}
#endif
