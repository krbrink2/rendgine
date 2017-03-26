#include "pureColor.h"
#include "world.h"
#include "shaderec.h"

// ---- Default constructor ----
PureColor::PureColor():
	Shader()
{}

RGBColor PureColor::shade(const World& w, const ShadeRec& sr){
	return c;
}

PureColor* PureColor::clone(){
	return new PureColor(*this);
}