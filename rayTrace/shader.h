/********************************************************
/	shader.h
/	Scot Halverson
/	Provides tools for creating and manipulating a generic shader
*/

#ifndef SHADERH
#define SHADERH 1

#include "light.h"
#include "vector4d.h"
#include "color.h"

class Shader {
	public:
		Shader(){};

		virtual ~Shader(){};
		virtual Color genColor(Light*, Vector4d&, Ray4d&, Point4d&, Color&) = 0;
		virtual string getType() = 0;
		virtual string getName() = 0;

	private:
		
};

#endif
