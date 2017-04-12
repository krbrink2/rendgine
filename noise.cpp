
#include "noise.h"
#include <cmath>
#include "world.h"
#include "shaderec.h"

// ---- Default constructor ----
Noise::Noise():
	Shader()
{}

// ---- Copy consructor ----
// Noise::Noise(const Ashikhmin& ash):
// 	Shader(ash),
// 	nu(ash.nu),
// 	nv(ash.nv),
// 	kdiff(ash.kdiff),
// 	kspec(ash.kspec)
// 	{}

// ---- Assignment operator ----
// Noise& Noise::operator=(const Noise& rhs){
// 	c = rhs.c;
// 	nu = rhs.nu;
// 	nv = rhs.nv;
// 	kdiff = rhs.kdiff;
// 	kspec = rhs.kdiff;
// 	return *this;
// }

// ---- Destructor ----
// Noise::~Noise(){
// }

// Function name:		shade
// Function purpose:	BRDf
// Parameters:			World for reference, sr for data
// Return value:		Color
// Any other output:	none
RGBColor Noise::shade(const World& w, const ShadeRec& sr){
	RGBColor accum(0,0,0);
	return accum;
}

// Function name:		clone
// Function purpose:	Returns pointer to clone of this Noise.
// Parameters:			none
// Return value:		Pointer to new shader.
// Any other output:	none
Shader* Noise::clone() const{
	return new Noise(*this);
}
