//default constructor
inline ImageGen::ImageGen(){}

//constructor taking in a scene and a file name
ImageGen::ImageGen(Scene* s, string fileName, int sm){
	this->s = s;
	sampleMultiplier = sm;	
	list<Camera*> cameras = s->getCameras();	
	list<Camera*>::iterator it;
	for (it = cameras.begin(); it != cameras.end(); it++){
		currentCam = *it;	
		this->width = currentCam->getWidth();
		this->height = currentCam->getHeight();
		this->colorArray = new float[width * height * 3 ];
		this->fileName = currentCam->getName() + "." + fileName;
		
		generateArray();
		
		generateFile();
	}	
}

//default destructor.  nothing new is created, so nothing to destroy.
inline ImageGen::~ImageGen(){}

//generates the one dimensional RGB array
void ImageGen::generateArray(){
	int sampleMultiplier = currentCam->getSampleMultiplier();
	int sm2 = sampleMultiplier * sampleMultiplier;
	Ray4d tempRay;
	Color tempColor, tempColor2;
	
	s->generateBoundingBox();

	int percentDiv = height / 10;
	float percentDone; 

	for(int a = 0; a < height; a++){
		for (int b = 0; b < width; b++){
			// need to average n*n colors to generate a pixel
			for (int c = 0; c < sampleMultiplier; c++){// subpixel height
				for (int d = 0; d < sampleMultiplier; d++){ //subpixel width
					// get the ray
					tempRay = currentCam->getRay(b * sampleMultiplier + d, a * sampleMultiplier + c);
					// sum the colors
					tempColor2 = s->getColorBoundingVolumes(tempRay);
					tempColor = tempColor + tempColor2;
				}
			}	
		
			
			// divide the color values by the number of rays summed			
			tempColor = Color(tempColor.getR() / sm2, tempColor.getG() / sm2, tempColor.getB() / sm2);
			colorArray[(a*width + b) * 3 + 0] = tempColor.getR();
			colorArray[(a*width + b) * 3 + 1] = tempColor.getG();
			colorArray[(a*width + b) * 3 + 2] = tempColor.getB();
			tempColor = Color(0,0,0);
		}
		if (a % percentDiv == 0){
			percentDone = ((float)a / (float)height) * 100.0;
			cout << percentDone << "%" << endl;
		}
	}
}

//given a filename, dimensions, and a pixel array, create a PNG
inline void ImageGen::generateFile(){
	cs5721::PNGImage pngimage;
	pngimage.writeFileData(fileName, width, height, colorArray);
}
