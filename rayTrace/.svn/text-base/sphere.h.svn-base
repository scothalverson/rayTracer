/********************************************************
/	sphere.h
/	Scot Halverson
/	Provides tools for creating and manipulating a sphere
*/

#ifndef SPHEREH
#define SPHEREH 1

#include "shape.h"
#include "point4d.h"
#include "ray4d.h"
#include "math.h"
#include "vector4d.h"
#include "shader.h"
#include <list>
#include <string>
#include <stdlib.h>

class Sphere : public Shape {
	public:
		Sphere();
		Sphere(Point4d&, float, Color&, string&);
		~Sphere();
		Color intersect(Ray4d& r, list<Light*>&, float&, float&, list<Shape*>&, int);
		bool intersect(Ray4d&, float&, float&);
		string getType();
		Vector4d getNormal();
		void addShader(Shader*);
		Point4d getPoint(Ray4d&, bool&);
		void setSpecularReflectColor(Color&);
		string getName();
		void addShaderReference(string&);
		list<string> getShaderReferences();
		Point4d getMinPoint();
		Point4d getMaxPoint();
		Point4d getMidPoint();
		
	protected:
		float discriminant(Ray4d&);
		Point4d origin;
		float radius;
};


//type accessor
inline string Sphere::getType(){return "Sphere";}

//add a shader
inline void Sphere::addShader(Shader* s){
	shaders.push_front(s);
}

//add a shader reference
inline void Sphere::addShaderReference(string& s){
	shaderRefs.push_front(s);
}

//accessor for shader references
inline list<string> Sphere::getShaderReferences(){
	return shaderRefs;
}

//set spec color
inline void Sphere::setSpecularReflectColor(Color& spec){
	this->spec = spec;
}

//name accessor
inline string Sphere::getName(){return name;}

inline Point4d Sphere::getMinPoint(){
	return Point4d(origin.getX() - radius, origin.getY() - radius, origin.getZ() - radius, 1);
}
inline Point4d Sphere::getMaxPoint(){
	return Point4d(origin.getX() + radius, origin.getY() + radius, origin.getZ() + radius, 1);
}

inline Point4d Sphere::getMidPoint(){
	return origin;
}

#endif
