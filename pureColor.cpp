#include "pureColor.h"
#include "world.h"
#include "shaderec.h"

// ---- Default constructor ----
PureColor::PureColor():
	Shader()
{}

PureColor::PureColor(double r, double g, double b):
	Shader()
{
	c = RGBColor(r, g, b);
}

PureColor::PureColor(RGBColor _color):
	Shader()
{
	c = _color;
}

RGBColor PureColor::shade(const World& w, const ShadeRec& sr){
	return c;
}

PureColor* PureColor::clone(){
	return new PureColor(*this);
}