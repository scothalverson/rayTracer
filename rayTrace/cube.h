/********************************************************
/	cube.h
/	Scot Halverson
/	Provides tools for creating and manipulating a cube object
*/

#ifndef CUBEH
#define CUBEH 1

#include "triangle.h"
#include "point4d.h"
#include "mesh.h"

class Cube : public Mesh {

	public:
		Cube();
		Cube(Point4d&, Point4d&, Color&, string&);
		Cube(Point4d&, Point4d&, Point4d&, Point4d&, Point4d&, Point4d&, Point4d&, Point4d&, Color&, string&);
		~Cube();
		list<Triangle*> getTriangles();
		string getName();
		void addShader(Shader*);
		void addShaderReference(string&);
		list<string> getShaderReferences();

	private:
		Triangle* triangles[12];
		Point4d points[8];
		Color color;
		string name;
		list<Shader*> shaders;
		list<string> shaderRefs;

};

//default constructor
inline Cube::Cube(){}

//destructor
inline Cube::~Cube(){
	delete [] triangles;
}

//add a shader reference
inline void Cube::addShaderReference(string& s){
	shaderRefs.push_front(s);
	for(int a = 0; a < 12; a++){
		triangles[a]->addShaderReference(s);
	}
}

//accessor for shader references
inline list<string> Cube::getShaderReferences(){
	return shaderRefs;
}

//gets the list of triangles
inline list<Triangle*> Cube::getTriangles(){
	list<Triangle*> trianglesList;
	for (int a = 0; a < 12; a++){
		trianglesList.push_front(triangles[a]);
	}
	return trianglesList;
}

//name accessor
inline string Cube::getName(){return name;}

//add a shader
inline void Cube::addShader(Shader* s){
	for (int a = 0; a < 12; a++){
		triangles[a]->addShader(s);
	}
}

#endif
