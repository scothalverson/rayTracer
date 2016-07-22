/********************************************************
/	camera.h
/	Scot Halverson
/	Provides tools for creating and manipulating a camera object for a ray tracer
*/

#ifndef CAMERAH
#define CAMERAH 1

#include "point4d.h"
#include "vector4d.h"
#include "ray4d.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>

class Camera {
	public:
		Camera();
		Camera(Ray4d&, float, float, string);
		Camera(Ray4d&, string);
		~Camera();
		void initView(int height, int width);
		int getWidth();
		int getHeight();
		Ray4d getRay(int, int);
		string getName();
		int getSampleMultiplier();
		void setSampleMultiplier(int sm);

	private:
		int width, height, sampleMultiplier;
		float l, r, b, t;
		void generateRays(int width, int height);
		void generateImagePlane();
		Point4d e;
		Vector4d d, uVec, vVec, wVec;
		float focalLength, fov;
		float *imageData;
		Ray4d *rays;
		string name;
};
// default constructor
inline Camera::Camera(){}

//destructor
inline Camera::~Camera(){
	delete [] rays;
}

// creates an array of Rays and calls the function to create them
inline void Camera::generateRays(int width, int height){	
	this->rays = new Ray4d[width * height * sampleMultiplier * sampleMultiplier];
	this->generateImagePlane();
}

// accessor for height in pixels
inline int Camera::getHeight(){return height;}

// accessor for width in pixels
inline int Camera::getWidth(){return width;}

// accessor for rays
inline Ray4d Camera::getRay(int w, int h){
	return rays[width * sampleMultiplier * h + w];
}

// gets the name of the camera
inline string Camera::getName(){
	return name;
}

inline int Camera::getSampleMultiplier(){return sampleMultiplier;}

inline void Camera::setSampleMultiplier(int sm){ sampleMultiplier = sm; cout << "Samples: " << sm*sm << endl;}

#endif
