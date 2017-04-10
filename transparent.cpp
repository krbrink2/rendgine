#include "transparent.h"
#include "world.h"

extern World* worldPtr;

// ---- Constructor ----
Transparent::Transparent():
	Shader(),
	second(new Shader),
	mix(.5)
{
	second->c = RGBColor(0, 255, 0);
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
	Point3D point = sr.hitPoint - .0001*sr.hitNormal;
	Vector3D direction = sr.ray.direction;
	Ray newRay(point, direction);
	ShadeRec newSr;
	newSr.ray = newRay;	// Why do I do this in mirror?
	worldPtr->traceRay(newRay, newSr);
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


	/*
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
}*/