#include "shader.h"
#include "world.h"
#include "shaderec.h"
#include <iostream>

extern World* worldPtr;

// ---- Default constructor ----
Shader::Shader():
	c(RGBColor(0, 1, 0))	// Default to green because why not.
{}

// ---- Copy constructor ----
Shader::Shader(const Shader& sdr):
	c(sdr.c)
{}

// ---- Assignment operator ----
Shader& Shader::operator=(const Shader& rhs){
	c = rhs.c;
	return *this;
}

// ---- Destructor ----
Shader::~Shader(){}

// Function name:		shade
// Function purpose:	Lambertian BRDF
// Parameters:			
//		w:			Scene info including eye, lights, and other objects
//		n:			Normal
// Return value:		Computed value
// Any other output:	None
RGBColor Shader::shade(const World& w, const ShadeRec& sr){
	// Shader already has material + color.
	// BRDF also needs N, E, and L.
	// Pass in N.
	// Get E and L from worldPtr.

	RGBColor accum(0, 0, 0);
	//Vector3D& E = worldPtr->E;

	for(size_t i = 0; i < worldPtr->lights.size(); i++){
		// May want to put this in another function.
		Vector3D L = worldPtr->lights[i]->getDirection(sr.hitPoint);
		double NDotL = clamp((sr.hitNormal * L), 0, 1);
		accum += (c * NDotL * worldPtr->lights[i]->getIrradiance(sr.hitPoint))/256;
	}

	// Clamp color
	accum.r = clamp(accum.r, 0, 255);
	accum.g = clamp(accum.g, 0, 255);
	accum.b = clamp(accum.b, 0, 255);

	return accum;
}

// Function name:		"()" operator
// Function purpose:	Allows this shader to act like a functor. Wrapper for shade function.
// Parameters:			Same as shade function.
// Return value:		Computed shader value
// Any other output:	None
RGBColor Shader::operator()(const World& w, const ShadeRec& sr){
	return shade(w, sr);
}


