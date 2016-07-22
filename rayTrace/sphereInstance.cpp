#include "sphereInstance.h"

SphereInstance::SphereInstance(){}
SphereInstance::~SphereInstance(){}

//constructor for a sphere
SphereInstance::SphereInstance(Point4d& origin, float radius, Color& c, string& name){
	this->origin = origin;
	this->radius = radius;
	this->c = c;
	this->spec = c;
	this->name = name;


	Matrix4x4 scale, undoScale;
	Matrix4x4 translate, undoTranslate;
	
	

	undoScale = undoScale.scale(1.0f, 1.5f, 1.0f, 1.0f);
	scale = scale.scale((1.0/1.0),(1/1.5),1.0f,1.0f);

	//addTransform(scale, undoScale);	
	//addTransform(undoScale, scale);
	
	translate = translate.transform(15, 0, 0, 1);
	undoTranslate = undoTranslate.transform(-15,0,0,1);
	
	//addTransform(translate, undoTranslate);	

}

//get the color of the sphere at a given point
Color SphereInstance::intersect(Ray4d& unmodifiedRay, list<Light*>& lights, float& t0, float& t1, list<Shape*>& shapes, int recursiveDepth){

	//if the discriminant is positive, the ray intersects the sphere at two points
	//if the discriminant is 0, the ray intersects the sphere at one point
	//if the discriminant is negative, the ray does not intersect the sphere at all

	//modify the ray so that it reflects the changes applied by the transformation matrix
	Point4d modPoint = *inverseTransforms.front() * unmodifiedRay.getOrigin();
	Vector4d modDir = *inverseTransforms.front() * unmodifiedRay.getDirection();
	Ray4d r(modPoint, modDir);
	r.sampleX = unmodifiedRay.sampleX;
	r.sampleY = unmodifiedRay.sampleY;
	r.maxSampleX = unmodifiedRay.maxSampleX;
	r.maxSampleY = unmodifiedRay.maxSampleY;
	
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
		Point4d ump = unmodifiedRay.getOrigin() + unmodifiedRay.getDirection() * t;

		Vector4d normal = inverseTranspose * (p - origin).normalize();
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
		//int n = 8;
		Color genCol,  genCol2;
		
		srand48 (time (0));
		Vector4d modVec1, modVec2;
		
		for (it = lights.begin(); it != lights.end(); it++){
			genCol = Color(0,0,0);
			l = *it;
			shadowed = false;
					
			//generate ray from point to light
			srand48 (drand48());
			modVec1 = (l->getV1() * ((r.sampleX + drand48() - .5)/r.maxSampleX));
			srand48 (drand48());
			modVec2 = (l->getV2() * ((r.sampleY + drand48() - .5)/r.maxSampleY));
			Point4d lightPt = l->getOrigin() + modVec1 + modVec2;

			shadowRayVec = (lightPt - p);
			shadowRay = Ray4d( p, shadowRayVec);

			//check all shapes for intersection on generated ray
			for (shapeIterator = shapes.begin(); shapeIterator != shapes.end() && shadowed == false; shapeIterator++){
				tempShape = *shapeIterator;				
				shadowed = tempShape->intersect(shadowRay, epsilon, T1);
			}
			//loop through shaders, assuming that the point is not in a shadow for the current light
			for (shaderIterator = shaders.begin(); shaderIterator != shaders.end() && shadowed == false; shaderIterator++){
				s = *shaderIterator;
				genCol2 = s->genColor(l, normal, unmodifiedRay, ump, c);
				genCol2 = genCol2 * .6;
				genCol =  genCol + genCol2;
					
			}
			genCol = Color(genCol.getR()/ shaders.size(), genCol.getG()/shaders.size(), genCol.getB()/shaders.size());
			genCol2 = genCol2 + genCol;
		}
		genCol2 = Color(genCol2.getR()/ lights.size(), genCol2.getG()/lights.size(), genCol2.getB()/lights.size());
		litColor = litColor + genCol2;
		
		//recursively call intersect methods for specular reflection

		// first, generate the new ray
		Vector4d tempRecursiveVec = *transforms.front() * (unmodifiedRay.getDirection() - (normal * (2 *(unmodifiedRay.getDirection() * normal))));
		tempRecursiveVec = tempRecursiveVec.normalize();
		Point4d tempRecursivePoint = *transforms.front() * p;
		Ray4d tempRecursiveRay(tempRecursivePoint, tempRecursiveVec);
		
		float gloss = .3;
		float area = (1 - gloss) * .01;
		Vector4d vTemp(0,1,0);//arbitrary...
		Vector4d uVec = vTemp.crossProduct(tempRecursiveVec);		
		Vector4d vVec = tempRecursiveVec.crossProduct(uVec);
		Vector4d vecPrime;
		Ray4d rPrime;
		float u, v;
		genCol2 = Color(0,0,0);
		for (shapeIterator = shapes.begin(); shapeIterator != shapes.end() && recursiveDepth > 0; shapeIterator++){
			tempShape = *shapeIterator;
			srand48(drand48());

			u = -area/2 + r.sampleX*area + drand48() - .5;
			v = -area/2 + r.sampleY*area + drand48() - .5;
			//cout << "u = " << u << " v = " << v << endl;
			vecPrime = tempRecursiveVec + uVec * u + vVec * v;
			vecPrime = vecPrime.normalize();
			rPrime = Ray4d(p, vecPrime);
					
			rPrime.sampleX = unmodifiedRay.sampleX;
			rPrime.sampleY = unmodifiedRay.sampleY;
			rPrime.maxSampleX = unmodifiedRay.maxSampleX;
			rPrime.maxSampleY = unmodifiedRay.maxSampleY;

			tempColor = tempShape->intersect(rPrime, lights, epsilon, T1, shapes, recursiveDepth - 1);	
			if (tempColor.getR() >= 0){
				genCol =  tempColor;	
				
			}
			genCol = Color(genCol.getR()/shapes.size(), genCol.getG()/shapes.size(), genCol.getB()/shapes.size());	 
			genCol2 = genCol2 + genCol;
			genCol2 = genCol2;
			
		}
		litColor = litColor + genCol2;	

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
bool SphereInstance::intersect(Ray4d& unmodifiedRay, float& t0, float& t1){
	//if the discriminant is positive, the ray intersects the sphere at two points
	//if the discriminant is 0, the ray intersects the sphere at one point
	//if the discriminant is negative, the ray does not intersect the sphere at all
	Vector4d modDir = *inverseTransforms.front() * unmodifiedRay.getDirection();
	Point4d p = unmodifiedRay.getOrigin();

	float disc = discriminant(unmodifiedRay);
	if (disc >= 0){
		float dec = -unmodifiedRay.getDirection() * (unmodifiedRay.getOrigin() - origin);
		float dd = (unmodifiedRay.getDirection() * unmodifiedRay.getDirection());
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


float SphereInstance::discriminant(Ray4d& unmodifiedRay){
	//calculate the discriminant
	// d = direction vector for the ray
	Vector4d d = unmodifiedRay.getDirection();
	
	// e = eye point, or origin of the ray
	// c = center point for the sphere
	// R = radius for sphere
	
	// the vector (e - c) is used a number of times, so we'll calculate it in advance 
	Vector4d ec = unmodifiedRay.getOrigin() - origin;

	return (d * ec)*(d * ec) - (d * d)*((ec * ec) - (radius * radius));
}

//get the point of intersection.  also sets the reference boolean to true if there is an intersection
Point4d SphereInstance::getPoint(Ray4d& unmodifiedRay, bool& success){
	Point4d po = unmodifiedRay.getOrigin();	
	Vector4d v = *inverseTransforms.front() * unmodifiedRay.getDirection();
	//Ray4d r(po, v);	
	
	success = false;
	float disc = discriminant(unmodifiedRay);
	if (disc >= 0){
		success = true;
	}
	else {
		return Point4d(0,0,0,0);
	}	
	//calculate t value
	//calculate -d * (e - c)
	float dec = -unmodifiedRay.getDirection() * (unmodifiedRay.getOrigin() - origin);
	//calculate d * d 
	float dd = (unmodifiedRay.getDirection() * unmodifiedRay.getDirection());

	float t = min((dec + sqrt(disc))/dd, (dec - sqrt(disc))/dd);
				
	//calculate normal
	// first calculate the point for which the normal should be determined
	Point4d p = unmodifiedRay.getOrigin() + unmodifiedRay.getDirection() * t;
	
	return p;	
}


