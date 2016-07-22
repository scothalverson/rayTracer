#include "cube.h"
#include "mesh.h"
//constructor given two points
Cube::Cube(Point4d& a, Point4d& b, Color& color, string& name){

	this->color = color;
	this->name = name;

	//generate the 8 points representing the cube from the two given
	points[0] = a;
	points[1] = Point4d(a.getX(), a.getY(), b.getZ());
	points[2] = Point4d(a.getX(), b.getY(), a.getZ());
	points[3] = Point4d(a.getX(), b.getY(), b.getZ());
	points[4] = b;
	points[5] = Point4d(b.getX(), b.getY(), a.getZ());
	points[6] = Point4d(b.getX(), a.getY(), b.getZ());
	points[7] = Point4d(b.getX(), a.getY(), a.getZ());

	//generate the 12 triangles representing the cube

	triangles[0] = new Triangle(points[0], points[6], points[7], color, name + "t0"); //bottom face
	triangles[1] = new Triangle(points[0], points[1], points[6], color, name + "t1"); //bottom face
	triangles[2] = new Triangle(points[0], points[7], points[5], color, name + "t2"); //front face
	triangles[3] = new Triangle(points[0], points[5], points[2], color, name + "t3"); //front face
	triangles[4] = new Triangle(points[0], points[2], points[3], color, name + "t4"); //left face 
	triangles[5] = new Triangle(points[0], points[3], points[1], color, name + "t5"); //left face 
	triangles[6] = new Triangle(points[4], points[3], points[2], color, name + "t6"); //top face
	triangles[7] = new Triangle(points[4], points[2], points[5], color, name + "t7"); //top face
	triangles[8] = new Triangle(points[4], points[1], points[3], color, name + "t8"); //back face
	triangles[9] = new Triangle(points[4], points[6], points[1], color, name + "t9"); //back face 
	triangles[10] = new Triangle(points[4], points[5], points[7], color, name + "t10"); //right face 
	triangles[11] = new Triangle(points[4], points[7], points[6], color, name + "t11"); //right face 
}

//constructor given 8 points
Cube::Cube(Point4d& a, Point4d& b, Point4d& c, Point4d& d, Point4d& e, Point4d& f, Point4d& g, Point4d& h, Color& color, string& name){
	this->color = color;
	this->name = name;	
		
	points[0] = a;
	points[1] = b;
	points[2] = c;
	points[3] = d;
	points[4] = e;
	points[5] = f;
	points[6] = g;
	points[7] = h;

	//TODO: check order so that the resulting triangles all have outward-facing normals

	//generate the 12 triangles representing the cube

	triangles[0] = new Triangle(points[0], points[6], points[7], color, name + "t0");
	triangles[1] = new Triangle(points[0], points[1], points[6], color, name + "t1");
	triangles[2] = new Triangle(points[0], points[7], points[5], color, name + "t2");
	triangles[3] = new Triangle(points[0], points[2], points[5], color, name + "t3");
	triangles[4] = new Triangle(points[0], points[2], points[3], color, name + "t4");
	triangles[5] = new Triangle(points[0], points[1], points[3], color, name + "t5");
	triangles[6] = new Triangle(points[4], points[3], points[2], color, name + "t6");
	triangles[7] = new Triangle(points[4], points[5], points[2], color, name + "t7");
	triangles[8] = new Triangle(points[4], points[3], points[1], color, name + "t8");
	triangles[9] = new Triangle(points[4], points[6], points[1], color, name + "t9");
	triangles[10] = new Triangle(points[4], points[5], points[7], color, name + "t10");
	triangles[11] = new Triangle(points[4], points[6], points[7], color, name + "t11");
}


