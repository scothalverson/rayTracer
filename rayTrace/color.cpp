#include "color.h"

//RGBA constructor
Color::Color(float r, float g, float b, float a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

// clamp function.  ensures that RGBA values lie between 0.0 and 1.0
void Color::clamp(){
	float maxVal = max(r, max(g, b));
	if ( maxVal > 1.0){
		r = r / maxVal;
		g = g / maxVal;
		b = b / maxVal; 
	}
	if (r < 0.0){r = 0.0;}
	else if (r > 1.0){r = 1.0;}
	if (g < 0.0){g = 0.0;}
	else if (g > 1.0){g = 1.0;}
	if (b < 0.0){b = 0.0;}
	else if (b > 1.0){b = 1.0;}
	if (a < 0.0){a = 0.0;}
	else if (a > 1.0){a = 1.0;}
}

//RGB constructor.  Assumes alpha = 1
Color::Color(float r, float g, float b){

	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1;
}

//color multiplier.  multiplies values of individual intensities for RGBA
Color Color::operator*(Color& c){
	return Color(c.getR() * r, c.getG() * g, c.getB() * b, c.getA() * a);
}

//color adder.  adds values of individual intensities
Color Color::operator+(Color& c){
	return Color(c.getR() + r, c.getG() + g, c.getB() + b, c.getA() + a);
}

//color scalar multiplier.  multiplies individual intensities by a scalar
Color Color::operator*(float scalar){
	return Color(scalar * r, scalar * g, scalar * b, scalar * a);
}
