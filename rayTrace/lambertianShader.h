/********************************************************
/	lambertianShader.h
/	Scot Halverson
/	Provides tools for creating and manipulating a Lambertian shader
*/

#ifndef LAMBERTIANSHADERH
#define LAMBERTIANSHADERH 1

#include "shader.h"

class LambertianShader : public Shader {
	public:
		LambertianShader(string);
		LambertianShader(Color, Color, string);
		~LambertianShader();
		Color genColor(Light*, Vector4d&, Ray4d&, Point4d&, Color&);
		string getType();
		string getName();
	private:
		Color diffuse, ambient;
		string name;
};

//default constructor
inline LambertianShader::LambertianShader(string name){
	diffuse = Color(1.0,0,0);
	ambient = Color(.05, .05, .05);
	this->name = name;
}

//constructor taking in ambient and diffuse colors
inline LambertianShader::LambertianShader(Color d, Color a, string name){
	diffuse = d;
	ambient = a;
	this->name = name;
}

//destructor.  nothing should need to be done
inline LambertianShader::~LambertianShader(){}

//calculate the shaded value
inline Color LambertianShader::genColor(Light* l, Vector4d& normal, Ray4d& r, Point4d& p, Color& c){
	Color temp = l->getColor() * max((float)0, normal * -(l->getRay(p).getDirection().normalize()));
	return (diffuse * temp);
}

//accessor for the type of shader
inline string LambertianShader::getType(){return "Lambertian";}

//accessor for the name of shader
inline string LambertianShader::getName(){return name;}
#endif
