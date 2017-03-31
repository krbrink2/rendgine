#ifndef Checkerboard_H
#define Checkerboard_H
#include "shader.h"
#include <cmath>

class Checkerboard: public Shader{
public:
	Checkerboard();
	Checkerboard(const RGBColor _c);

	RGBColor shade(const World& w, const ShadeRec& sr);
	Checkerboard* clone();

private:

};









#endif