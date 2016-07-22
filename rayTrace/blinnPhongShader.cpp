#include "blinnPhongShader.h"
#include "math.h"

using namespace std;

//Calculates the color of a point on an object given its pre-shaded color, the light(ray) and the normal
Color BlinnPhongShader::genColor(Light* l, Vector4d& normal, Ray4d& r, Point4d& p, Color& c){
	// calculate h
	Vector4d vVec = -(r.getDirection().normalize());
	Vector4d lVec = -(l->getRay(p).getDirection().normalize());
	Vector4d hVec = vVec + lVec;
	hVec = hVec.normalize();
	
	//compute the colors	
	//Color l1 = (c * l->getColor() * max((float)0, normal.normalize() * lVec));
	Color l2 = l->getColor();
	return (l2 * ks * max((double)0, pow(normal.normalize() * hVec,power)));
}


