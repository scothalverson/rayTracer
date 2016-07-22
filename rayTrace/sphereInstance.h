/********************************************************
/	sphereInstance.h
/	Scot Halverson
/	Provides tools for creating and manipulating an instance of a sphere
*/

#ifndef SPHEREINSTANCEH
#define SPHEREINSTANCEH 1

#include "sphere.h"
#include "instanceShape.h"

using namespace std;

class SphereInstance : public Sphere, public InstanceShape {
	public:
		SphereInstance();
		~SphereInstance();
		SphereInstance(Point4d&, float, Color&, string&);		
		Color intersect(Ray4d& r, list<Light*>&, float&, float&, list<Shape*>&, int);
		bool intersect(Ray4d& r, float& t0, float& t1);
		float discriminant(Ray4d& r);
		Point4d getPoint(Ray4d& r, bool& success);
		string getType();
		string getName();
		void setSpecularReflectColor(Color& spec);
		list<string> getShaderReferences();
		Point4d getMinPoint();
		Point4d getMaxPoint();
		Point4d getMidPoint();
		
	private:

};

//type accessor
inline string SphereInstance::getType(){return "SphereInstance";}


//accessor for shader references
inline list<string> SphereInstance::getShaderReferences(){
	return shaderRefs;
}

//set spec color
inline void SphereInstance::setSpecularReflectColor(Color& spec){
	this->spec = spec;
}

//name accessor
inline string SphereInstance::getName(){return name;}

inline Point4d SphereInstance::getMinPoint(){
	Point4d min(origin.getX() - radius, origin.getY() - radius, origin.getZ() - radius, 1);
	return *transforms.front() * min;
}

inline Point4d SphereInstance::getMaxPoint(){
	Point4d max(origin.getX() + radius, origin.getY() + radius, origin.getZ() + radius, 1);
	return *transforms.front() * max;
}

inline Point4d SphereInstance::getMidPoint(){
	return origin;
}

#endif
