/********************************************************
/	mesh.h
/	Scot Halverson
/	Provides tools for creating and manipulating a mesh object
*/

#ifndef MESHH
#define MESHH 1

#include "triangle.h"

class Mesh {
	public:
		Mesh(){};
		virtual ~Mesh();
		virtual list<Triangle*> getTriangles() = 0;
		virtual string getName() = 0;
	private:

};

inline Mesh::~Mesh(){}

#endif
