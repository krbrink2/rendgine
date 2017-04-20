#include "transparent.h"
#include "world.h"

extern World* worldPtr;

// ---- Constructor ----
Transparent::Transparent():
	Shader(),
	second(new Shader),
	mix(.5)
{
	second->c = RGBColor(0, 0, 255);
}

// Function name:		shade
// Function purpose:	BSDF
// Parameters:			World w for world reference.
// 						ShadeRec sr for bookkeeping.
// Return value:		Computed color.
// Any other output:	May write to sr.
RGBColor Transparent::shade(const World& w, const ShadeRec& sr){
	// Trace another ray
	// Creat new origin, push it to other side of hit point.
	Point3D point = sr.hitPoint;
	// If we are on the back side of the surface, move to front side.
	if(sr.ray.d * sr.hitNormal < 0){
		point.x -= .001*sr.hitNormal.x;
		point.y -= .001*sr.hitNormal.y;
		point.z -= .001*sr.hitNormal.z;
	}
	Vector3D direction = sr.ray.d;
	Ray newRay(point, direction);
	ShadeRec newSr;
	newSr.ray = newRay;	// Why do I do this in mirror?
	worldPtr->traceRay(newRay, newSr);

	// Calculate colors
	RGBColor firstColor;
	if(newSr.hitObject){
		firstColor = newSr.hitShader->shade(*worldPtr, newSr);
	}
	else{
		firstColor = worldPtr->backgroundColor;
	}


	// Run second shader
	RGBColor secondColor = second->shade(*worldPtr, sr);

	// Mix and return colors
	return (1 - mix)*firstColor + mix*secondColor;
}

// Function name:		clone
// Function purpose:	Returns pointer to new copy of this Transparent.
// Parameters:			none
// Return value:		Pointer to new Transparent copy.
// Any other output:	Allocates memory.
Shader* Transparent::clone() const{
	return new Transparent(*this);
}