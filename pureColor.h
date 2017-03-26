#ifndef PURECOLOR_H
#define PURECOLOR_H
#include "shader.h"

class PureColor: public Shader{
public:
	PureColor();
	RGBColor shade(const World& w, const ShadeRec& sr);
	PureColor* clone();
};

#endif