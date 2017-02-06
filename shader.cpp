#include "shader.h"
#include "world.h"

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

RGBColor Shader::shade(const World& w, const Normal& N){
	// Shader already has material + color.
	// BRDF also needs N, E, and L.
	// Pass in N.
	// Get E and L from worldPtr.

	RGBColor accum(0, 0, 0);
	//Vector3D& E = worldPtr->E;

	for(size_t i = 0; i < worldPtr->lights.size(); i++){
		// May want to put this in another function.
		Vector3D L = worldPtr->lights[i].dir;
		accum += c * (N * L);
	}

	return RGBColor(255, 255, 255);
	return accum;

	
}

RGBColor Shader::operator()(const World& w, const Normal& N){
	return shade(w, N);
}


