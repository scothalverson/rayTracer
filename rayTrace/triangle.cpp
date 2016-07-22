#include "triangle.h"

//constructor for a triangle taking in 3 points and a color
Triangle::Triangle(Point4d& aPoint, Point4d& bPoint, Point4d& cPoint, Color& color, string name){
	this->aPoint = aPoint;
	this->bPoint = bPoint;
	this->cPoint = cPoint;
	this->color = color;
	this->spec = color;
	this->name = name;

	a = aPoint.getX() - bPoint.getX();
	b = aPoint.getY() - bPoint.getY();
	c = aPoint.getZ() - bPoint.getZ();
	d = aPoint.getX() - cPoint.getX();
	e = aPoint.getY() - cPoint.getY();
	f = aPoint.getZ() - cPoint.getZ();

	//figure out two vectors on the plane
	Vector4d temp1 = (aPoint - bPoint);
	Vector4d temp2 = (aPoint - cPoint);
	//calculate normal
	normal = -(temp2.crossProduct(temp1).normalize());
}

//determine the color of the triangle at the point of intersection
Color Triangle::intersect(Ray4d& r, list<Light*>& lights, float& t0, float& t1, list<Shape*>& shapes, int recursiveDepth){
	//if (recursiveDepth < 6)
	//	cout << recursiveDepth;
	float g, h, i, j, k, l, M, beta, gamma, t;

	g = r.getX();
	h = r.getY();
	i = r.getZ();
	j = aPoint.getX() - r.getPosX();
	k = aPoint.getY() - r.getPosY();
	l = aPoint.getZ() - r.getPosZ();
	
	M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);

	//generate t
	t = (f*(j*b-a*k)+e*(a*l-j*c)+d*(k*c-b*l))/M;
	//check t
	if (t > t1 || t < t0){
		return Color(-1,-1,-1);		
	}
	
	//generate gamma
	gamma = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
	//check gamma
	if (gamma < 0 || gamma > 1){
		return Color(-1,-1,-1);
	}
	
	//generate beta
	beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h - e*g))/M;
	//check beta 
	if (beta < 0 || beta > 1){
		return Color(-1,-1,-1);
	}
	
	if ((beta + gamma) > 1){
		return Color(-1,-1,-1);
	}

	// at this point, it is clear that the ray intersects the triangle.  
	// the intersection point marks the new closest point of intersection on the ray
	t1 = t;
	
	Point4d p = r.getOrigin() + r.getDirection() * t;
	
	Color litColor = color * .05;
	
	list<Shape*>::iterator shapeIterator;
		
	Vector4d shadowRayVec;
	Ray4d shadowRay;

	Shape* tempShape;

	Color tempColor;

	bool shadowed;

	float epsilon = 0.0001f, T1 = 1000;
	Light* templ;
	//loop through lights, summing colors generated
	Color genCol, genCol2;
	
	srand48 (time (0));
	Vector4d modVec1, modVec2;
	
	for (it = lights.begin(); it != lights.end(); it++){
		Color genCol = Color(0,0,0);		
		templ = *it;
		//for (int softCounter1 = 0; softCounter1 < n; softCounter1++){
		//	for (int softCounter2 = 0; softCounter2 < n; softCounter2++){
		shadowed = false;	
		//generate ray from point to light
		srand48 (drand48());
		modVec1 = (templ->getV1() * ((r.sampleX + drand48() - .5)/r.maxSampleX));
		srand48 (drand48());
		modVec2 = (templ->getV2() * ((r.sampleY + drand48() - .5)/r.maxSampleY));
		Point4d lightPt = templ->getOrigin() + modVec1 + modVec2;
		shadowRayVec = (lightPt - p);
		shadowRay = Ray4d(p, shadowRayVec);
		
		//check all shapes for intersection on generated ray
		for (shapeIterator = shapes.begin(); shapeIterator != shapes.end() && shadowed == false; shapeIterator++){
			tempShape = *shapeIterator;				
			shadowed = tempShape->intersect(shadowRay, epsilon, T1);
		}

		for (shaderIterator = shaders.begin(); shaderIterator != shaders.end() && shadowed == false; shaderIterator++){
			s = *shaderIterator;
			genCol2 = s->genColor(templ, normal, r, p, color);
			genCol =  genCol + genCol2;
		}
		genCol2 = Color(genCol.getR()/ lights.size(), genCol.getG()/lights.size(), genCol.getB()/lights.size());
		litColor = litColor + genCol2;

	}
	//recursively call intersect methods for specular reflection

	// first, generate the new ray
	Vector4d tempRecursiveVec = r.getDirection();
	tempRecursiveVec = tempRecursiveVec.normalize();
	Point4d tempRecursivePoint = p;
	Ray4d tempRecursiveRay(tempRecursivePoint, tempRecursiveVec);
		
	float gloss = 1.0;
	float area = (1/gloss) * .001;
	
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
			
		vecPrime = tempRecursiveVec + uVec * u + vVec * v;
		vecPrime = vecPrime.normalize();
		rPrime = Ray4d(p, vecPrime);
					
		rPrime.sampleX = r.sampleX;
		rPrime.sampleY = r.sampleY;
		rPrime.maxSampleX = r.maxSampleX;
		rPrime.maxSampleY = r.maxSampleY;
					
		tempColor = tempShape->intersect(rPrime, lights, epsilon, T1, shapes, recursiveDepth - 1);	
		if (tempColor.getR() >= 0){
			genCol =  tempColor;	
				
		}

		genCol = Color(genCol.getR()/shapes.size(), genCol.getG()/shapes.size(), genCol.getB()/shapes.size());	 
		genCol2 = genCol2 + genCol;
		genCol2 = genCol2;	
	}
	litColor = litColor + genCol2;	

	if (litColor.getR() < 0)
		litColor = Color(0,0,0);

	if (lights.empty()){
		return Color(1,0,0);
	}
	else {
		litColor.clamp();
		return litColor;
		
	}	
	
}

//determine if the given ray intersects the triangle within a given interval
bool Triangle::intersect(Ray4d& r, float& t0, float& t1){
	
	float g, h, i, j, k, l, M, beta, gamma, t;

	g = r.getX();
	h = r.getY();
	i = r.getZ();
	j = aPoint.getX() - r.getPosX();
	k = aPoint.getY() - r.getPosY();
	l = aPoint.getZ() - r.getPosZ();
	
	M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);

	//generate t
	t = (f*(j*b-a*k)+e*(a*l-j*c)+d*(k*c-b*l))/M;
	//check t
	if (t > t1 || t < t0){
		return false;
	}
	
	//generate gamma
	gamma = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
	//check gamma
	if (gamma < 0 || gamma > 1){
		return false;
	}
	
	//generate beta
	beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h - e*g))/M;
	//check beta 
	if (beta < 0 || beta > 1){
		return false;
	}
	
	if ((beta + gamma) > 1){
		return false;
	}
	return true;
}

//get the point of intersection on a given ray.  if it exists, success is modified to be true
Point4d Triangle::getPoint(Ray4d& r, bool& success){

	float g, h, i, j, k, l, M, t;

	g = r.getX();
	h = r.getY();
	i = r.getZ();
	j = aPoint.getX() - r.getPosX();
	k = aPoint.getY() - r.getPosY();
	l = aPoint.getZ() - r.getPosZ();
	
	M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);
	//generate t
	t = (f*(j*b-a*k)+e*(a*l-j*c)+d*(k*c-b*l))/M;
	Point4d p = r.getOrigin() + r.getDirection() * t;
	success = true;
	return p;

}

Point4d Triangle::getMinPoint(){
	float minX = aPoint.getX();
	float minY = aPoint.getY();
	float minZ = aPoint.getZ();
	
	if (bPoint.getX() < minX){
		minX = bPoint.getX();
	}
	if (cPoint.getX() < minX){
		minX = cPoint.getX();
	}
	if (bPoint.getY() < minY){
		minY = bPoint.getY();
	}
	if (cPoint.getY() < minY){
		minY = cPoint.getY();
	}
	if (bPoint.getZ() < minZ){
		minZ = bPoint.getZ();
	}
	if (cPoint.getZ() < minZ){
		minZ = cPoint.getZ();
	}
	return Point4d(minX, minY, minZ, 1);
}

Point4d Triangle::getMaxPoint(){
	float maxX = aPoint.getX();
	float maxY = aPoint.getY();
	float maxZ = aPoint.getZ();
	
	if (bPoint.getX() > maxX){
		maxX = bPoint.getX();
	}
	if (cPoint.getX() > maxX){
		maxX = cPoint.getX();
	}
	if (bPoint.getY() > maxY){
		maxY = bPoint.getY();
	}
	if (cPoint.getY() > maxY){
		maxY = cPoint.getY();
	}
	if (bPoint.getZ() > maxZ){
		maxZ = bPoint.getZ();
	}
	if (cPoint.getZ() > maxZ){
		maxZ = cPoint.getZ();
	}
	return Point4d(maxX, maxY, maxZ, 1);
}

Point4d Triangle::getMidPoint(){
	float x, y, z;
	x = (aPoint.getX() + bPoint.getX() + cPoint.getX()) / 3.0;
	y = (aPoint.getY() + bPoint.getY() + cPoint.getY()) / 3.0;
	z = (aPoint.getZ() + bPoint.getZ() + cPoint.getZ()) / 3.0;
	
	return Point4d(x,y,z,1);
}





