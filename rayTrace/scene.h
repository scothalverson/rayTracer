/********************************************************
/	scene.h
/	Scot Halverson
/	Provides tools for creating and manipulating a scene
*/

#ifndef SCENEH
#define SCENEH

#include "camera.h"
#include "shape.h"
#include "mesh.h"
#include <list>
#include "triangle.h"
#include "shader.h"
#include "boundingBox.h"
#include "point4d.h"

using namespace std;

class Scene {
	public:
		Scene();
		~Scene();
		Shape& getShape();
		void operator+(Shape*);
		void operator+(Shader*);
		void operator+(Light*);
		void operator+(Camera*);
		void operator+(Mesh*);		
		Color getColor(Ray4d&);
		Color getColorBoundingVolumes(Ray4d&);
		list<Camera*> getCameras();
		list<BoundingBox*> getBoundingBoxes();
		void setRecursiveDepth(int);
		void setSampleDepth(int);
		void setVerbose(bool);
		void setRes(int, int);
		void setShaders();
		void generateBoundingBox();
		
	private:
		BoundingBox* split(list<BoundingBox*>&, int);
		BoundingBox* bb;
		list<Shape*> shapes;
		list<BoundingBox*> boundingBoxes;
		list<Shader*> shaders;
		list<Light*> lights;
		list<Camera*> cameras;
		int recursiveDepth, sampleDepth;
		bool verbose;
};

// default constructor for a scene
inline Scene::Scene(){
	verbose = false;
	recursiveDepth = 0;	
}

//add a shape
inline void Scene::operator+(Shape* s){
	if (verbose)
		cout << "adding shape of type " << s->getType() << ": " << s->getName() << endl;
	shapes.push_front(s);
	boundingBoxes.push_front(new BoundingBox(s));
}

//add a shader
inline void Scene::operator+(Shader* s){
	if (verbose)
		cout << "adding shader of type " << s->getType() << ": " << s->getName() << endl;
	shaders.push_front(s);
}

//add a light
inline void Scene::operator+(Light* l){
	if (verbose)
		cout << "Adding light " + l->getName() << endl; 
	lights.push_front(l);
}

//add a camera
inline void Scene::operator+(Camera* c){
	cout << "SampleDepth: " << sampleDepth << endl;
	c->setSampleMultiplier(sampleDepth);
	if (verbose)
		cout << "adding camera " + c->getName() << endl;
	cameras.push_front(c);
}

//get the list of cameras
inline list<Camera*> Scene::getCameras(){
	return cameras;
}

//get the list of BoundingBoxes
inline list<BoundingBox*> Scene::getBoundingBoxes(){
	return boundingBoxes;
}

//set the recursive depth
inline void Scene::setRecursiveDepth(int depth){
	if (depth >= 0){
		recursiveDepth = depth;
	}
	else {
		recursiveDepth = 0;
	}
}

//set the recursive depth
inline void Scene::setSampleDepth(int depth){
	if (depth >= 0){
		sampleDepth = depth;
	}
	else {
		sampleDepth = 1;
	}
}

//set the verbose mode
inline void Scene::setVerbose(bool mode){verbose = mode;}

inline void Scene::setRes(int height, int width){
	
	Camera* c;
	
	list<Camera*>::iterator ci;
	for (ci = cameras.begin(); ci != cameras.end(); ci++){
		c = *ci;
		c->initView(height, width);
	}
}

#endif
