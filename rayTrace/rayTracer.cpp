

#include <stdio.h>
#include <stdlib.h>
#include <fstream>


#include "imageGen.h"

#include "lambertianShader.h"
#include "normalShader.h"
#include "phongShader.h"
#include "blinnPhongShader.h"
#include "triangle.h"
#include "sphere.h"
#include "camera.h"

#include "../rdlLanguageParser/RDL_Lexer.hpp"
#include "../rdlLanguageParser/RDL_Parser.hpp"



using namespace std;

int main(int argc, char *argv[]){

	bool verboseMode = false;  // default to verbose mode off
	string outFile = "output.png"; // default output file
	string inFile = ""; // default input file (might need to change later...)
	int width = 1024, height = 768, samples = 8; // default image dimensions

	for (int a = 0; a < argc; a++){ // loop through arguments
		string s(argv[a]); 
		
		if (s == "-v"){ // verbose mode switch
			cout << "Verbose mode: on" << endl;
			verboseMode = true;
		}
		else if(s == "-f"){ // input file switch and name
			if ((a+1) < argc){
				inFile = string(argv[a+1]);
				a++;
			}
		}
		else if(s == "--width"){ // width switch and value
			if ((a+1) < argc){
				width = atoi(argv[a+1]);
				a++;
			}
		}
		else if(s == "--height"){ // height switch and value
			if ((a+1) < argc){
				height = atoi(argv[a+1]);
				a++;
			}
		}
		else if(s == "--samples"){ // width switch and value
			if ((a+1) < argc){
				samples = atoi(argv[a+1]);
				a++;
			}
		}
		else if(s == "-o"){ // output file switch and name
			if ((a+1) < argc){
				outFile = string(argv[a+1]);
				a++;
			}
		}	
		else if (a != 0) { 	// argument default case that ignores anything that is not one of the above.
					// note that it does not throw an error for argument 0, which is the executable name	
			cout << "Warning: argument \"" << s << "\" is not supported." << endl;		
		}
	}	

	if (inFile == "")
    		exit(EXIT_FAILURE);

	Scene* s = new Scene();	
	s->setSampleDepth(samples);
	

  	// Attempt to open the file and parse it.                              
  	try {

    	// create a stream from f and pass as arg to lexer                                                                
   	 std::ifstream f_in;
    	f_in.open( inFile.c_str(), std::ios::in );

    	RDL_Lexer lexer( f_in );
    	RDL_Parser parser( lexer );
	
	
	//specify scene	
	
	s->setVerbose(verboseMode);
	s->setRecursiveDepth(7);
    	parser.startRule(s);

  	} catch(std::exception& e) {
    		std::cerr << "exception: " << e.what() << std::endl;
  	}
	s->setShaders();
	s->setRes(width, height);
	//s->generateBoundingBox();
	

	//generate image(s)
	ImageGen(s, outFile, samples);
	
	return 0;
}
