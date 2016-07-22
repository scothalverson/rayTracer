/********************************************************
/	triangle.h
/	Scot Halverson
/	Provides tools for creating and manipulating a triangle
*/

#ifndef TRIANGLEH
#define TRIANGLEH 1

#include "shape.h"
#include "point4d.h"
#include "ray4d.h"
#include "math.h"
#include "vector4d.h"
#include <list>
#include <stdlib.h>

class Triangle : public Shape {
	public:
		Triangle();
		Triangle(Point4d&, Point4d&, Point4d&, Color&, string);
		Color intersect(Ray4d&, list<Light*>&, float&, float&, list<Shape*>&, int);
		bool intersect(Ray4d&, float&, float&);
		~Triangle();
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

	private:
		Point4d aPoint,bPoint,cPoint;
		list<Shader*> shaders;
		Color color, spec;
		Vector4d normal;
		float a, b, c, d, e, f;
		list<Light*>::iterator it;
		Shader* s;
		list<Shader*>::iterator shaderIterator;
		Light* tempLight;
		string name;
		list<string> shaderRefs;
		
};
//default constructor
inline Triangle::Triangle(){}

//destructor 
inline Triangle::~Triangle(){	
}

//type accessor
inline string Triangle::getType(){return "Triangle";}

//returns the vector representing the normal of the triangle
inline Vector4d Triangle::getNormal(){
	return normal;
}

//add a shader
inline void Triangle::addShader(Shader* s){
	shaders.push_front(s);
}


//add a shader reference
inline void Triangle::addShaderReference(string& s){
	shaderRefs.push_front(s);
}

//accessor for shader references
inline list<string> Triangle::getShaderReferences(){
	return shaderRefs;
}

inline void Triangle::setSpecularReflectColor(Color& spec){
	this->spec = spec;
}
//name accessor
inline string Triangle::getName(){return name;}
#endif
