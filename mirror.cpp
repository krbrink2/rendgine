#include "mirror.h"
#include "world.h"

extern World* worldPtr;

Mirror::Mirror():
	Shader(){
	// Pass	
}

RGBColor Mirror::shade(const World& w, const ShadeRec& sr){
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

Mirror* Mirror::clone(){
	return new Mirror(*this);
}