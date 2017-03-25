#include "mirror.h"

Mirror::Mirror():
	Shader(){
	// Pass	
}

RGBColor Mirror::shade(const World& w, const AhdeRec& sr){
	if(sr.numBounces >= MAX_BOUNCES - 1){
		// Can't bounce again.
		return RGBColor(0,0,0);
	}
	// Generate new ray
	Vector3D toOrigin = -sr.ray.d;
	Vector3D foo = toOrigin - (toOrigin dot sr.hitNormal)*sr.hitNormal;
	Ray newRay(sr.hitPoint, sr.hitNormal - 2*foo);

	// Generate new ShadeRec
	ShadeRec newSr(sr);
	newSr.numBounces++;
	newSr.ray = newRay;
	worldPtr->traceRay(newRay, newSr);
	if(newSr.hitObject){
		return sr.hitShader->shade(worldPtr, newSr);
	}
	else{
		return worldPtr->backgroundColor;
	}
}

Mirror* Mirror::clone(){
	return new Mirror(*this);
}