#include "pureColor.h"
#include "world.h"
#include "shaderec.h"

// ---- Default constructor ----
PureColor::PureColor():
	Shader()
{}

// ---- Constructor ----
PureColor::PureColor(double r, double g, double b):
	Shader()
{
	c = RGBColor(r, g, b);
}

// ---- Constructor ----
PureColor::PureColor(RGBColor _color):
	Shader()
{
	c = _color;
}

// ---- Destructor ----
PureColor::~PureColor(){
	return;
}

// Function name:		shade
// Function purpose:	BRDF
// Parameters:			World this is taking place in.
// 						ShadeRec for bookkeeing.
// Return value:		Shaded color.
// Any other output:	none
RGBColor PureColor::shade(const World& w, const ShadeRec& sr){
	return c;
}

// Function name:		clone
// Function purpose:	Returns pointer to copy of this PureColor.
// Parameters:			none
// Return value:		Pointer to new PureColor.
// Any other output:	none
Shader* PureColor::clone() const{
	return new PureColor(*this);
}