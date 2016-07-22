#include "scene.h"

//destructor for a scene.
Scene::~Scene(){

	list<Shape*>::iterator si;
	for (si = shapes.begin(); si != shapes.end(); si++){
		delete *si;	
	}
	list<Light*>::iterator li;
	for (li = lights.begin(); li != lights.end(); li++){
		delete *li;	
	}
	list<Camera*>::iterator ci;
	for (ci = cameras.begin(); ci != cameras.end(); ci++){
		delete *ci;	
	}
	list<Shader*>::iterator shi;
	for (shi = shaders.begin(); shi != shaders.end(); shi++){
		delete *shi;	
	}
}

//generate the pixel color for the given viewing ray
Color Scene::getColor(Ray4d& r){
	list<Shape*>::iterator it;
	Color c(-1,-1,-1);
	Color temp;	
	Shape* s;
	float t0 = 0, t1 = 1000;
	for (it = shapes.begin(); it != shapes.end(); it++){
		s = *it;

		temp = s->intersect(r, lights, t0, t1, shapes, recursiveDepth);	
		if (temp.getR() != -1){
			c = temp;		
		}
	}
	if (t1 == 1000){
		c = Color(.1,.1,.1);
	}
	return c;
}

//generate the pixel color for the given viewing ray
Color Scene::getColorBoundingVolumes(Ray4d& r){
	list<Shape*>::iterator it;
	Color c(-1,-1,-1);
	Color temp;	
	float t0 = 0, t1 = 1000;
	Shape* s;
	list<Shape*> possibleIntersections;
	//here we need to check the bounding volume heirarchy to produce a list of shapes that could be intersected by the ray
	//stack used to keep track of bounding boxes that produce intersections
	list<BoundingBox*> bvStack;
	//create the outermost bounding box and push it to the stack
	bvStack.push_front(bb);
	
	BoundingBox* bvTemp;
	
	while(!bvStack.empty()){
		bvTemp = bvStack.front(); //get the top boundingBox
		bvStack.pop_front(); //remove it from the stack
		
		if (bvTemp->intersect(r, t0, t1)){ //if the bounding box is intersected by the ray,
			if (bvTemp->getLeft() != NULL){ //check if there is a left branch,
				bvStack.push_front(bvTemp->getLeft()); // and add it to the stack.
			}
			if (bvTemp->getRight() != NULL){ //check if there is  right branch,
				bvStack.push_front(bvTemp->getRight()); // and add it to the stack.
			}
			if (bvTemp->getShape() != NULL){ //check if the bv has a shape associated with it,
				possibleIntersections.push_front(bvTemp->getShape()); // and add it to the shape list
			}
		}// otherwise, don't do anything with the bounding volume.
	}
	
	
	// once we have a list of shapes, we need it iterate through them to find which one, if any, has the closest intersection
	for (it = possibleIntersections.begin(); it != possibleIntersections.end(); it++){
		s = *it;

		temp = s->intersect(r, lights, t0, t1, shapes, recursiveDepth);	
		if (temp.getR() != -1){
			c = temp;		
		}
	}
	if (t1 == 1000){
		c = Color(.1,.1,.1);
	}
	return c;
}

//add a mesh object
void Scene::operator+(Mesh* m){
	if (verbose)
		cout << "Adding mesh " + m->getName() << endl; 

	list<Triangle*> tri = m->getTriangles();
	list<Triangle*>::iterator si;
	Triangle* t;
	for (si = tri.begin(); si != tri.end(); si++){
		t = *si;	
		shapes.push_front(t);
		boundingBoxes.push_front(new BoundingBox(t));	
	}
}

//apply the shaders read in from the file to the shapes that they belong to.
void Scene::setShaders(){
	list<Shape*>::iterator shapeIterator;
	list<Shader*>::iterator shaderIterator;
	list<string>::iterator stringIterator;
	Shape* s;
	string ref;
	Shader* sh;
	list<string> temp;
	for(shapeIterator = shapes.begin(); shapeIterator != shapes.end(); shapeIterator++){
		s = *shapeIterator;
		 temp = s->getShaderReferences();		
		for (stringIterator = temp.begin(); stringIterator != temp.end(); stringIterator++){
			ref = *stringIterator;			
			for (shaderIterator = shaders.begin(); shaderIterator != shaders.end(); shaderIterator++){
				sh = *shaderIterator;
				if (ref == sh->getName()){
					s->addShader(sh);
					if (verbose)
						cout << "adding shader " << ref << "(" << sh->getType() << ") to object " << s->getName() << endl;				
				}
			}
		}
	}
}

void Scene::generateBoundingBox(){
	bb = split(boundingBoxes, 1);
}

// recursive function that splits the given list into two and generates a bounding volume 
// dimension is an integer representation of x,y,z dimension on which the list should be split
BoundingBox* Scene::split(list<BoundingBox*>& myList, int dimension){
	
	//check to see if the list only has one element in it.  if it does, return that.
	if (myList.size() == 1){
		return myList.front();
	}
	
	else if (myList.size() < 1){
		return NULL;
	}		
	
	float sum = 0.0, av;
	int count = 0;
	
	BoundingBox* bb;
	
	list<BoundingBox*>::iterator bbi;
	
	// determine the average midpoint
	if (dimension == 0){
		//cerr << "X dimension\n";
		for (bbi = myList.begin(); bbi != myList.end(); bbi++){
			bb = *bbi;
			sum+= bb->getMidPoint().getX();
			count++;
		}
	}
	
	else if (dimension == 1){
		//cerr << "Y dimension\n";
		for (bbi = myList.begin(); bbi != myList.end(); bbi++){
			bb = *bbi;
			sum+= bb->getMidPoint().getY();
			count++;
		}
	}
	else {
		//cerr << "Z dimension\n";
		for (bbi = myList.begin(); bbi != myList.end(); bbi++){
			bb = *bbi;
			sum+= bb->getMidPoint().getZ();
			count++;
		}
	}
	
	av = sum / count;
	list<BoundingBox*> lList, rList;
	
	
	
	//given the midpoint, split the list into two
	if (dimension == 0){
		for (bbi = myList.begin(); bbi != myList.end(); bbi++){
			bb = *bbi;
			if (bb->getMidPoint().getX() >= av){
				lList.push_front(bb);
			}
			else {
				rList.push_front(bb);
			}
		}
	}
	else if (dimension == 1){
		for (bbi = myList.begin(); bbi != myList.end(); bbi++){
			bb = *bbi;
			if (bb->getMidPoint().getY() >= av){
				lList.push_front(bb);
			}
			else {
				rList.push_front(bb);
			}
		}
	}
	else{
		for (bbi = myList.begin(); bbi != myList.end(); bbi++){
			bb = *bbi;
			if (bb->getMidPoint().getZ() >= av){
				lList.push_front(bb);
			}
			else {
				rList.push_front(bb);
			}
		}
	}
	
	BoundingBox* result = new BoundingBox();
	
	//given the two lists, call the function recursively on both lists and change the
	//dimension on which the splitting will take place.
	if (lList.size() > 0){
		BoundingBox* left = split(lList, (dimension + 1) % 3);
		result->setLeft(left);
	}
	if (rList.size() > 0){
		BoundingBox* right = split(rList, (dimension + 1) % 3);
		result->setRight(right);
	}
	
	//finally, create the bounding box that will be returned
	
	return result;
		
	

}
