#ifndef PURECOLOR_H
#define PURECOLOR_H
#include "shader.h"

class PureColor: public Shader{
public:
	PureColor();
	PureColor(double r, double g, double b);
	PureColor(RGBColor _color);
	/*PureColor(const PureColor& rhs);
	PureColor& operator=(const PureColor& rhs);*/
	~PureColor();
	RGBColor shade(const World& w, const ShadeRec& sr);
	PureColor* clone();
};

#endif