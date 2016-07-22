#include "boundingBox.h"

BoundingBox::BoundingBox(Point4d& a, Point4d& b){
	if (a.getX() < b.getX()){
		minX = a.getX();
		maxX = b.getX();	
	}
	else {
		maxX = a.getX();
		minX = b.getX();
	}
	if (a.getY() < b.getY()){
		minY = a.getY();
		maxY = b.getY();	
	}
	else {
		maxY = a.getY();
		minY = b.getY();
	}
	if (a.getZ() < b.getZ()){
		minZ = a.getZ();
		maxZ = b.getZ();	
	}
	else {
		maxZ = a.getZ();
		minZ = b.getZ();
	}
	
	left = NULL;
	right = NULL;
}

BoundingBox::BoundingBox(BoundingBox* l, BoundingBox* r){
	left = l;
	right = r;
	
	if (l->minX < r->minX){
		minX = l->minX;
	}
	else {
		minX = r->minX;
	}
	if (l->minY < r->minY){
		minY = l->minY;
	}
	else {
		minY = r->minY;
	}
	if (l->minZ < r->minZ){
		minZ = l->minZ;
	}
	else {
		minZ = r->minZ;
	}
	if (l->maxX > r->maxX){
		maxX = l->maxX;
	}
	else {
		maxX = r->maxX;
	}
	if (l->maxY > r->maxY){
		maxY = l->maxY;
	}
	else {
		maxY = r->maxY;
	}
	if (l->maxZ > r->maxZ){
		maxZ = l->maxZ;
	}
	else {
		maxZ = r->maxZ;
	}
	
}

BoundingBox::BoundingBox(Shape* s){
	float epsilon = .0001;
	Point4d a = s->getMinPoint();
	Point4d b = s->getMaxPoint();

	if (a.getX() < b.getX()){
		minX = a.getX();
		maxX = b.getX();	
	}
	else {
		maxX = a.getX();
		minX = b.getX();
	}
	if (a.getY() < b.getY()){
		minY = a.getY();
		maxY = b.getY();	
	}
	else {
		maxY = a.getY();
		minY = b.getY();
	}
	if (a.getZ() < b.getZ()){
		minZ = a.getZ();
		maxZ = b.getZ();	
	}
	else {
		maxZ = a.getZ();
		minZ = b.getZ();
	}
	
	if (maxX == minX){
		minX = minX - epsilon;
	}
	if (maxY == minY){
		minY = minY - epsilon;
	}
	if (maxZ == minZ){
		minZ = minZ - epsilon;
	}
	
	
	this->s = s;
	left = NULL;
	right = NULL;
	
}

bool BoundingBox::intersect(Ray4d& r, float& t0, float& t1){
	//magnitude of the x,y,z components of the direction vector
	float xd = r.getDirection().getX();
	float yd = r.getDirection().getY();
	float zd = r.getDirection().getZ();
	
	//position of the 'eye' - the origin of the ray
	float xe = r.getOrigin().getX();
	float ye = r.getOrigin().getY();
	float ze = r.getOrigin().getZ();

	//tvalues of the ray where the ray intersects the min/max values along the x,y,z planes 
	float txmin, txmax, tymin, tymax, tzmin, tzmax;
	
	//determine txmin & txmax
	float ax = 1/xd;
	if ( ax >= 0){
		txmin = ax*(minX - xe);
		txmax = ax*(maxX - xe);
	}
	else {
		txmax = ax*(minX - xe);
		txmin = ax*(maxX - xe);
	}
	
	//determine tymin & tymax
	float ay = 1/yd;
	if ( ay >= 0){
		tymin = ay*(minY - ye);
		tymax = ay*(maxY - ye);
	}
	else {
		tymax = ay*(minY - ye);
		tymin = ay*(maxY - ye);
	}
	
	//determine tzmin & tzmax
	float az = 1/zd;
	if ( az >= 0){
		tzmin = az*(minZ - ze);
		tzmax = az*(maxZ - ze);
	}
	else {
		tzmax = az*(minZ - ze);
		tzmin = az*(maxZ - ze);
	}
	
	
	//at this point, we need to know if the ray intersects the bounding volume.  
	//all intersection tests at these t values will produce an intersection 
	float bvMinT = max(txmin, max(tymin, tzmin)); //the highest t value for the minimum intersection point
	float bvMaxT = min(txmax, min(tymax, tzmax)); //the lowest t value for the maximum intersection point
	float epsilon = 0.0001f;
	if ((bvMinT - epsilon) > (bvMaxT + epsilon)){
		return false;
	}
	//if we get here, then the ray intersects the bv.
	//now we need to determine if it does so within the t0 and t1 values
	//if ((bvMinT + epsilon) < t0 || (bvMaxT - epsilon) > t1){
	//	return false;
	//}
	
	//finally, we know that the ray intersects, and that it does so within the t0, t1 constraints.
	return true;
}

BoundingBox* BoundingBox::getBoundingBox(){
	return this;
}

Point4d BoundingBox::getMidPoint(){
	if ( left == NULL && right == NULL){
		return s->getMidPoint();
	}
	else {
		return Point4d((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2, 1);
	}
}

void BoundingBox::initialize(){
	if (left == NULL && right == NULL){
		//do nothing
	}
	else if (left == NULL){
		//set min/max values to those of the right boundingBox
		
		minX = right->getMin().getX();
		minY = right->getMin().getY();
		minZ = right->getMin().getZ();
		maxX = right->getMax().getX();
		maxY = right->getMax().getY();
		maxZ = right->getMax().getZ();
	}
	else if (right == NULL){
		//set min/max values to those of the left boundingBox
		minX = left->getMin().getX();
		minY = left->getMin().getY();
		minZ = left->getMin().getZ();
		maxX = left->getMax().getX();
		maxY = left->getMax().getY();
		maxZ = left->getMax().getZ();
		
	}
	else {
		//find the min/max values for the two sub boundingboxes
		minX = min(right->getMin().getX(),left->getMin().getX());
		minY = min(right->getMin().getY(),left->getMin().getY());
		minZ = min(right->getMin().getZ(),left->getMin().getZ());
		maxX = max(right->getMax().getX(),left->getMax().getX());
		maxY = max(right->getMax().getY(),left->getMax().getY());
		maxZ = max(right->getMax().getZ(),left->getMax().getZ());
		
	}
}


