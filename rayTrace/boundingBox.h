/********************************************************
/	boundingBox.h
/	Scot Halverson
/	Provides tools for creating and manipulating a bounding box around a shape
*/

#ifndef BOUNDINGBOXH
#define BOUNDINGBOXH 1

#include "point4d.h"
#include "ray4d.h"
#include "shape.h"

class BoundingBox {
	public:
		BoundingBox();
		BoundingBox(Point4d&, Point4d&);
		BoundingBox(Shape*);
		BoundingBox(BoundingBox*, BoundingBox*);
		~BoundingBox();
		string getType();
		BoundingBox* getBoundingBox();
		Point4d getMin();
		Point4d getMax();
		bool intersect(Ray4d&, float&, float&);
		Shape* getShape();
		void setShape(Shape*);
		BoundingBox* getLeft();
		BoundingBox* getRight();
		Point4d getMidPoint();
		void setRight(BoundingBox*);
		void setLeft(BoundingBox*);

	protected:
		float minX, minY, minZ, maxX, maxY, maxZ;
		Shape* s;
		BoundingBox* left;
		BoundingBox* right;
		void initialize();

};

inline BoundingBox::BoundingBox(){
	left = NULL;
	right = NULL;
	s = NULL;
}

inline string BoundingBox::getType(){return "Bounding Box";}

inline Point4d BoundingBox::getMin(){return Point4d(minX, minY, minZ, 1);}

inline Point4d BoundingBox::getMax(){return Point4d(maxX, maxY, maxZ, 1);}

inline Shape* BoundingBox::getShape(){return s;}

inline void BoundingBox::setShape(Shape* s){this->s = s;}

inline BoundingBox* BoundingBox::getLeft(){return left;}

inline BoundingBox* BoundingBox::getRight(){return right;}

inline void BoundingBox::setRight(BoundingBox* rb){right = rb; initialize();}

inline void BoundingBox::setLeft(BoundingBox* lb){left = lb; initialize();}

#endif

