#include "texture.h"
#include <cmath>
#include "world.h"
#include "shaderec.h"


// ---- Default constructor ----
Texture::Texture():
	Shader()
{
}

// Function name:		shade
// Function purpose:	BRDf
// Parameters:			World for reference, sr for data
// Return value:		Color
// Any other output:	none
RGBColor Texture::shade(const World& w, const ShadeRec& sr){
	RGBColor accum;
	return accum;

}

// Function name:		clone
// Function purpose:	Returns pointer to clone of this Texture.
// Parameters:			none
// Return value:		Pointer to new shader.
// Any other output:	none
Shader* Texture::clone() const{
	return new Texture(*this);
}

