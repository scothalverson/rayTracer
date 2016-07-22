#include "phongShader.h"

//calculate the color of an object at a given point
Color PhongShader::genColor(Light* l, Vector4d& normal, Ray4d& r, Point4d& p, Color& c){
	//calculate the scalar of the normal to add to p1 to get p2
	float s = -(l->getRay(p).getDirection().normalize()) * normal;	
	s = max(s, 0.0f);
	//calculate p1 - the point that is 1 unit away from the point of intersection along the light ray
	Point4d p1 = p + (l->getRay(p).getDirection().normalize());
	//calculate p2 - the point that is 2s*normal away from p1
	Point4d p2 = p1 + normal * (2 * s);
	//p2 represents a point on the outgoing/reflecting vector.  Use it to calc that vector
	Vector4d out = (p2 - p).normalize();
	//determine the cross product of the reflective vector and the viewing direction
	float cross = max((float)0.0, (out * -r.getDirection().normalize()));
	//finally, determine the color
	Color col = l->getColor();

	return (col * ks * max((double)0, pow(cross,power)));
}


