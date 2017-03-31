#include "checkerboard.h"
#include <cmath>
#include "world.h"
#include "shaderec.h"

// ---- Default constructor ----
Checkerboard::Checkerboard():
	Shader()
{}

Checkerboard::Checkerboard(const RGBColor _c):
	Shader()
{
	c = _c;
}


// Function name:		shade
// Function purpose:	BRDf
// Parameters:			World for reference, sr for data
// Return value:		Color
// Any other output:	none
RGBColor Checkerboard::shade(const World& w, const ShadeRec& sr){
	// Shader already has material + color.
	// BRDF also needs N, E, and L.
	// Pass in N.
	// Get E and L from worldPtr.

	RGBColor accum(0, 0, 0);
	//Vector3D& E = worldPtr->E;

	// For each light...
	for(size_t i = 0; i < worldPtr->lights.size(); i++){
		vector<std::pair<Vector3D, RGBColor> > samples;
		worldPtr->lights[i]->getSamples(samples, sr.hitPoint);
		// For each sample...
		for(auto sample : samples){
			// May want to put this in another function.
			Vector3D& L = sample.first;
			double NDotL = clamp((sr.hitNormal * L), 0, 1);
			accum += (c * NDotL * sample.second)/256;
		}
	}

	// Checkerboard it.
	double foo = floor(sr.hitPoint.x) + floor(sr.hitPoint.y) + floor(sr.hitPoint.z);
	foo = fabs(fmod(foo, 2.0));
	if(foo < 1.0){
		accum = accum*.5;
	}

	// Clamp color
	accum.r = clamp(accum.r, 0, 255);
	accum.g = clamp(accum.g, 0, 255);
	accum.b = clamp(accum.b, 0, 255);


	return accum;
}

// Function name:		clone
// Function purpose:	Returns pointer to clone of this Checkerboard.
// Parameters:			none
// Return value:		Pointer to new shader.
// Any other output:	none
Checkerboard* Checkerboard::clone(){
	return new Checkerboard(*this);
}	