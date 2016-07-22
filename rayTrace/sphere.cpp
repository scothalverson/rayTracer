#include "sphere.h"
//default constructor 
Sphere::Sphere(){}

//destructor
Sphere::~Sphere(){
}
//constructor for a sphere
Sphere::Sphere(Point4d& origin, float radius, Color& c, string& name){
	this->origin = origin;
	this->radius = radius;
	this->c = c;
	this->spec = c;
	this->name = name;
}

//get the color of the sphere at a given point
Color Sphere::intersect(Ray4d& r, list<Light*>& lights, float& t0, float& t1, list<Shape*>& shapes, int recursiveDepth){
	//cout << recursiveDepth;
	//if the discriminant is positive, the ray intersects the sphere at two points
	//if the discriminant is 0, the ray intersects the sphere at one point
	//if the discriminant is negative, the ray does not intersect the sphere at all
	
	float disc = discriminant(r);
	if (disc >= 0){
		//calculate t value
		//calculate -d * (e - c)
		float dec = -r.getDirection() * (r.getOrigin() - origin);
		//calculate d * d 
		float dd = (r.getDirection() * r.getDirection());
		
		float t = min((dec + sqrt(disc))/dd, (dec - sqrt(disc))/dd);
		//cout << t << endl;
		if (t < t0 || t > t1){
			return 	Color(-1,-1,-1);	
		}
		t1 = t;	
		
		//calculate normal
		// first calculate the point for which the normal should be determined
		Point4d p = r.getOrigin() + r.getDirection() * t;

		Vector4d normal = (p - origin).normalize();
		Color litColor = c * .05, tempColor;
		Light* l;
		Shader* s;
		//loop through lights, summing colors generated
		list<Light*>::iterator it;
		list<Shader*>::iterator shaderIterator;
		list<Shape*>::iterator shapeIterator;
		
		Vector4d shadowRayVec;
		Ray4d shadowRay;

		Shape* tempShape;

		bool shadowed;

		float epsilon = 0.0001f, T1 = 1000;

		for (it = lights.begin(); it != lights.end(); it++){
			shadowed = false;
			l = *it;
			
			//generate ray from point to light
			shadowRayVec = l->getOrigin() - p;
			shadowRay = Ray4d(p, shadowRayVec);

			//check all shapes for intersection on generated ray
			for (shapeIterator = shapes.begin(); shapeIterator != shapes.end() && shadowed == false; shapeIterator++){
				tempShape = *shapeIterator;				
				shadowed = tempShape->intersect(shadowRay, epsilon, T1);
			}

			//loop through shaders, assuming that the point is not in a shadow for the current light
			for (shaderIterator = shaders.begin(); shaderIterator != shaders.end() && shadowed == false; shaderIterator++){
				s = *shaderIterator;
				Color genCol = s->genColor(l, normal, r, p, c);
				litColor = litColor + genCol;
			}
		}
		
		//recursively call intersect methods for specular reflection

		// first, generate the new ray
		Vector4d tempRecursiveVec = r.getDirection() - (normal * (2 *(r.getDirection() * normal)));
		tempRecursiveVec = tempRecursiveVec.normalize();
		Ray4d tempRecursiveRay(p, tempRecursiveVec);

		for (shapeIterator = shapes.begin(); shapeIterator != shapes.end() && recursiveDepth > 0; shapeIterator++){
			tempShape = *shapeIterator;
			
			tempColor = tempShape->intersect(tempRecursiveRay, lights, epsilon, T1, shapes, recursiveDepth - 1);	
			if (tempColor.getR() > 0){
				tempColor = tempColor * spec;
				litColor = litColor + tempColor;		
			}
		}

		if (lights.empty()){
			return c;
		}
		else {
			litColor.clamp();
			return litColor;
		}
	}	
	else {
		return Color(-1,-1,-1);
	}
}

//just determine if the given ray intersects the sphere within the specified interval
bool Sphere::intersect(Ray4d& r, float& t0, float& t1){
	//cout << r.getX() << " " << r.getY() << " " << r.getZ() << endl;
	//if the discriminant is positive, the ray intersects the sphere at two points
	//if the discriminant is 0, the ray intersects the sphere at one point
	//if the discriminant is negative, the ray does not intersect the sphere at all
	
	float disc = discriminant(r);
	if (disc >= 0){
		float dec = -r.getDirection() * (r.getOrigin() - origin);
		float dd = (r.getDirection() * r.getDirection());
		//calculate t value
		
		float t = max((dec + sqrt(disc))/dd, (dec - sqrt(disc))/dd);
		if (t < t0 || t > t1){
			return 	false;	
		}
		return true;
	}	
	else {
		return false;
	}
}

//determine the discriminant of the quadratic function.  negative = no intersection, 0 = 1 intersection, positive = 2 intersections
float Sphere::discriminant(Ray4d& r){
	//calculate the discriminant
	// d = direction vector for the ray
	Vector4d d = r.getDirection();
	//cout << "d.x = " << d.getX() << " d.y = " << d.getY() << " d.z = " << d.getZ() << endl;
	// e = eye point, or origin of the ray
	// c = center point for the sphere
	// R = radius for sphere
	
	// the vector (e - c) is used a number of times, so we'll calculate it in advance 
	Vector4d ec = r.getOrigin() - origin;
	//cout << "t = " << (d * ec)*2 << " - " << (d * d) << " * " << (ec * ec) - (radius * radius) << endl;

	float disc = (d * ec)*(d * ec) - (d * d)*((ec * ec) - (radius * radius));
	
	//cout << "discriminant = " << t << endl;

	return disc;
}

//not implemented yet... isn't really needed though.
Vector4d Sphere::getNormal(){
	Vector4d normal(0,0,0,0);

	return normal;
	
}

//get the point of intersection.  also sets the reference boolean to true if there is an intersection
Point4d Sphere::getPoint(Ray4d& r, bool& success){
	success = false;
	float disc = discriminant(r);
	if (disc >= 0){
		success = true;
	}
	else {
		return Point4d(0,0,0);
	}	
	//calculate t value
	//calculate -d * (e - c)
	float dec = -r.getDirection() * (r.getOrigin() - origin);
	//calculate d * d 
	float dd = (r.getDirection() * r.getDirection());

	float t = min((dec + sqrt(disc))/dd, (dec - sqrt(disc))/dd);
				
	//calculate normal
	// first calculate the point for which the normal should be determined
	Point4d p = r.getOrigin() + r.getDirection() * t;
	
	return p;	
}


