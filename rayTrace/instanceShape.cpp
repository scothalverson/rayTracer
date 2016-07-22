#include "instanceShape.h"
InstanceShape::InstanceShape(){
	transforms.push_front(new Matrix4x4());
	inverseTransforms.push_front(new Matrix4x4());
}


 InstanceShape::~InstanceShape(){};

void InstanceShape::addTransform(Matrix4x4 mat, Matrix4x4 inv){
	Matrix4x4 matOld = *transforms.front();
	Matrix4x4* newMat  = new Matrix4x4(mat * matOld);
	
	//cout << newMat->ToString() << endl;

	transforms.push_front(newMat);

	Matrix4x4 invOld = *inverseTransforms.front();
	Matrix4x4* newInv  = new Matrix4x4(inv * invOld);

	//cout << newInv->ToString() << endl;
	//cout << mat.ToString() << inv.ToString(); 
	
	inverseTransforms.push_front(newInv);
	
	inverseTranspose = inverseTransforms.front()->transpose();
	//cout << inverseTransforms.front()->ToString();
}

void InstanceShape::removeTransform(){
	transforms.pop_front();
	inverseTransforms.pop_front();

}

Matrix4x4* InstanceShape::getTransform(){return transforms.front();}

Matrix4x4* InstanceShape::getInverseTransform(){return inverseTransforms.front();}


