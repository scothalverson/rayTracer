#include "camera.h"

//constructor taking in a ray representing the view direction and origin, a focal length, a feild of view, and a name
Camera::Camera(Ray4d& ray, float focalLength, float fov, string name){
	this->name = name;	
	this->e = ray.getOrigin();
	this->d = ray.getDirection();
	this->focalLength = focalLength;
	this->fov = fov;
}

//constructor taking in just a ray (view point & direction) and a name.  focal length and FOV are given default values
Camera::Camera(Ray4d& ray, string name){
	this->name = name;	
	this->e = ray.getOrigin();
	this->d = ray.getDirection();
	this->focalLength = 1.0;
	this->fov = 90;
}

//sets the dimensions for the viewing window and creates the correspoinding rays
void Camera::initView(int width, int height){
	if (width > 0 && height > 0){
		this->width = width;
		this->height = height;
		this->imageData = new float(width * height * 3);
		this->generateRays(width, height);
	}

	else{
		cerr << "Invalid image dimensions!" << endl;
	}
}

// initializes the rays that have previously been declared
void Camera::generateImagePlane(){

	//generate u,v,w
	//set w to be exactly opposite of the viewing direction, and make sure it is normalized
	wVec = -d.normalize();

	// create a temporary vector for 'up'
	Vector4d vTemp(0,1,0);
	//set v to be perpendicular to w and the 'up' vector
	uVec = vTemp.crossProduct(wVec).normalize();
	
	//finally, set u to be perpendicular to both v and w.  This should be roughly representative of the 'up' vector, but part of the orthonormal basis.
	vVec = wVec.crossProduct(uVec).normalize();

	//compute l, r, b, & t
	
	//calculate modifier for field of view first...
	float pi = std::atan(1.0f) * 4.0f;
	
	float fovMod = tan(fov*pi/(2*180));

	//cout << "Fov Mod = " << fovMod << endl;

	r = ((float)width/(float)height) * fovMod * (focalLength);
	l = -r;
	t = fovMod * (focalLength);
	b = -t;
	
	//delcare u & v, the pixel locations for the current pixel
	float u, v;
	Vector4d tempVector;
	srand48 (time (0));
	
	for (int heightCounter = 0; heightCounter < height * sampleMultiplier; heightCounter++){
		for (int widthCounter = 0; widthCounter < width * sampleMultiplier; widthCounter++){

			u = l + (r - l)*(widthCounter + (drand48() - 0.5))/(width * sampleMultiplier);			
			v = b + (t - b)*(heightCounter + (drand48() - 0.5))/(height * sampleMultiplier);
			
			//set ray direction
			tempVector = Vector4d(wVec*(-focalLength) + uVec * u + vVec * v).normalize();

			//set ray origin
			rays[width * sampleMultiplier * heightCounter + widthCounter] = Ray4d(e, tempVector);
			rays[width * sampleMultiplier * heightCounter + widthCounter].sampleX = heightCounter % sampleMultiplier;
			rays[width * sampleMultiplier * heightCounter + widthCounter].sampleY = widthCounter % sampleMultiplier;
			rays[width * sampleMultiplier * heightCounter + widthCounter].maxSampleX = sampleMultiplier;
			rays[width * sampleMultiplier * heightCounter + widthCounter].maxSampleY = sampleMultiplier;
		}	
	}
}




