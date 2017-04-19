#include "glossy.h"
#include <cmath>
#include "world.h"
#include "shaderec.h"

// ---- Default constructor ----
Glossy::Glossy():
	Shader(),
	exp(10)
{}


// Function name:		shade
// Function purpose:	BRDf
// Parameters:			World for reference, sr for data
// Return value:		Color
// Any other output:	none
RGBColor Glossy::shade(const World& w, const ShadeRec& sr){
	if(sr.numBounces >= MAX_BOUNCES - 1){
		// Can't bounce again.
		return c;
	}
	// Generate new ray
	Vector3D toOrigin = -sr.ray.d;
	Vector3D foo = toOrigin - (sr.hitNormal*toOrigin)*sr.hitNormal;
	Ray newRay(sr.hitPoint, sr.hitNormal - 2*foo);

	// Generate new ShadeRec
	ShadeRec newSr;
	newSr.numBounces = sr.numBounces + 1;
	newSr.ray = newRay;
	worldPtr->traceRay(newRay, newSr);
	if(newSr.hitObject){
		RGBColor c = newSr.hitShader->shade(*worldPtr, newSr);
		return c;
	}
	else{
		return worldPtr->backgroundColor;
	}

}

// Function name:		clone
// Function purpose:	Returns pointer to clone of this Glossy.
// Parameters:			none
// Return value:		Pointer to new shader.
// Any other output:	none
Shader* Glossy::clone() const{
	return new Glossy(*this);
}	