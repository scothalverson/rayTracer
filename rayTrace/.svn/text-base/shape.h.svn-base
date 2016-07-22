/********************************************************
/	shape.h
/	Scot Halverson
/	Provides tools for creating and manipulating a generic shape
*/

#ifndef SHAPEH
#define SHAPEH 1

#include "color.h"
#include "light.h"
#include "shader.h"
#include "vector4d.h"
#include <list>

class Shape {
	public:
		Shape();

		virtual ~Shape();
		virtual Color intersect(Ray4d&, list<Light*>&, float&, float&, list<Shape*>&, int) = 0;
		virtual bool intersect(Ray4d&, float&, float&) = 0;
		virtual string getType() = 0;
		virtual Vector4d getNormal() = 0;
		virtual void addShader(Shader*) = 0;
		virtual Point4d getPoint(Ray4d&, bool&) = 0;
		virtual void setSpecularReflectColor(Color&) = 0;
		virtual string getName() = 0;
		virtual void addShaderReference(string&) = 0;
		virtual list<string> getShaderReferences() = 0;
		virtual Point4d getMinPoint() = 0;
		virtual Point4d getMaxPoint() = 0;
		virtual Point4d getMidPoint() = 0;

	protected:
		Color c, spec;
		list<Shader*> shaders;
		list<string> shaderRefs;
		string name;
};

inline Shape::Shape(){}

inline Shape::~Shape(){}
#endif
