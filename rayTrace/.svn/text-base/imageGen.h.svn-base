/********************************************************
/	imageGen.h
/	Scot Halverson
/	Provides tools for creating and manipulating an image buffer and performing output
*/

#ifndef IMAGEGENH
#define IMAGEGENH 1

#include <cstdlib>
#include "../cs5721GraphicsLib/PNGImage.h"
#include <string>
#include "scene.h"

class ImageGen {
	public:
		ImageGen();
		ImageGen(Scene*, string, int);
		~ImageGen();
		void generateArray();
		void generateFile();
	
	private:	
		Scene* s;
		float* colorArray;
		int width, height, sampleMultiplier;
		string fileName; 
		Camera* currentCam;
};

#include "imageGen.cpp"
#endif
