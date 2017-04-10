#include "transparent.h"
#include "world.h"

extern World* worldPtr;

// ---- Constructor ----
Transparent::Transparent():
	Shader(){
	// Pass	
}

// Function name:		shade
// Function purpose:	BSDF
// Parameters:			World w for world reference.
// 						ShadeRec sr for bookkeeping.
// Return value:		Computed color.
// Any other output:	May write to sr.
RGBColor Transparent::shade(const World& w, const ShadeRec& sr){
	if(sr.numBounces >= MAX_BOUNCES - 1){
		// Can't bounce again.
		return RGBColor(0,0,0);
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

Transparent* Transparent::clone(){
	return new Transparent(*this);
}