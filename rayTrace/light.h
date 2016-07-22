/********************************************************
/	light.h
/	Scot Halverson
/	Provides tools for creating and manipulating a light
*/

#ifndef LIGHTH
#define LIGHTH 1

#include "point4d.h"
#include "ray4d.h"
#include "color.h"
#include "string"

class Light {
	public:
		Light();
		Light(Point4d&, Color&, string&);
		~Light();
		Ray4d getRay(Point4d&);
		Color getColor();
		Point4d getOrigin();
		string getName();
		void setV1(Vector4d);
		void setV2(Vector4d);
		Vector4d getV1();
		Vector4d getV2();
	private:
		Point4d p;
		Color c;
		string name;
		Vector4d v1, v2;

};

//default constructor
inline Light::Light(){}

//destructor.  nothing to delete
inline Light::~Light(){}

//constructor taking in a point, a color, and a name
inline Light::Light(Point4d& p, Color& c, string& name){
	this->p = p;
	this->c = c;
	this->name = name;
}

//get the ray representing the light
inline Ray4d Light::getRay(Point4d& newPoint){
	Vector4d v = (newPoint - p);	
	return Ray4d(p, v);
}

//accessor for the color of the light
inline Color Light::getColor(){return c;}

//accessor for the point of origin
inline Point4d Light::getOrigin(){
	return p;
}

//accessor for the light's name
inline string Light::getName(){return name;}

inline void Light::setV1(Vector4d v){v1 = v;}

inline void Light::setV2(Vector4d v){v2 = v;}

inline Vector4d Light::getV1(){return v1;}

inline Vector4d Light::getV2(){return v2;}

#endif
