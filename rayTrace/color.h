/********************************************************
/	color.h
/	Scot Halverson
/	Provides tools for creating and manipulating a color object
*/

#ifndef COLORH
#define COLORH 1

#include <algorithm>
using namespace std;

class Color {
	public:
		Color(); //default constructor
		~Color(); // default destructor
		Color(float, float, float); //constructor for RGB (A = 1)
		Color(float, float, float, float); //constructor for RGBA
		Color operator*(Color&);
		Color operator*(float);
		Color operator+(Color&);
		float getR();
		float getG();
		float getB();
		float getA();
		void clamp();


	private:
		float r,g,b,a;
};

//default constructor
inline Color::Color(){}

//Red accessor
inline float Color::getR(){return r;}

//Green accessor
inline float Color::getG(){return g;}

//Blue accessor
inline float Color::getB(){return b;}

//Alpha accessor
inline float Color::getA(){return a;}

//destructor.  Shouldn't need to do anything now...
inline Color::~Color(){}


#endif
