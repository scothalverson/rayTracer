/********************************************************
/	instanceShape.h
/	Scot Halverson
/	Provides tools for creating and manipulating a base instance shape
*/

#ifndef INSTANCESHAPEH
#define INSTANCESHAPEH 1

#include "shape.h"
#include "color.h"
#include "Matrix4x4.h"

class InstanceShape {
	public:
		InstanceShape();
		~InstanceShape();
		Matrix4x4* getTransform();
		Matrix4x4* getInverseTransform();
		void addTransform(Matrix4x4, Matrix4x4);
		void removeTransform();
		Ray4d transformRay(Ray4d);
	protected:
		list<Matrix4x4*> transforms;
		list<Matrix4x4*> inverseTransforms;
		Matrix4x4 inverseTranspose;
};




#endif


