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

	// Generate hemisphereical samples
	Vector3D samples[GLOSSY_NUM_SAMPLES];
	setSamples(samples);

	// Generate R: perfect reflection direction.
	Vector3D toOrigin = -sr.ray.d;
	Vector3D R = toOrigin - (sr.hitNormal*toOrigin)*sr.hitNormal;
	R = sr.hitNormal - 2*R;

	// Generate orthonormal basis.
	Vector3D U, V, W;
	W = R;
	U = (UP + Vector3D(.0001, .0001, .0001)) ^ W;	// Cross product with pertrubed up.
	U.normalize();
	V = U ^ W;
	
	// Transform each sample to the reflected basis.
	for(int i = 0; i < GLOSSY_NUM_SAMPLES; i++){
		// Generate sample direction
		Vector3D dir = 	samples[i].x*U + 
						samples[i].y*V +
						samples[i].z*W;
		// Reflect if beneath surface.
		if(sr.hitNormal * dir < 0){
			Vector3D dir = 	-samples[i].x*U + 
							-samples[i].y*V +
							samples[i].z*W;
		}
		samples[i] = dir;
	}


	// Shoot ray in new direction.
	RGBColor accum(0,0,0);
	for(int i = 0; i < GLOSSY_NUM_SAMPLES; i++){
		// Generate new ShadeRec
		ShadeRec newSr;
		newSr.numBounces = sr.numBounces + 1;
		// Generate new ray to trace
		Ray newRay(sr.hitPoint, samples[i]);
		newSr.ray = newRay;
		worldPtr->traceRay(newRay, newSr);
		if(newSr.hitObject){
			accum = accum + newSr.hitShader->shade(*worldPtr, newSr);
		}
		else{
			accum = accum + worldPtr->backgroundColor;
		}
	}

	// Normalize accum
	accum = accum / GLOSSY_NUM_SAMPLES;
	return accum;
}

// Function name:		clone
// Function purpose:	Returns pointer to clone of this Glossy.
// Parameters:			none
// Return value:		Pointer to new shader.
// Any other output:	none
Shader* Glossy::clone() const{
	return new Glossy(*this);
}	


// Function name:		setSamples
// Function purpose:	Adds hemisphereical sample Vector3d's to samples array.
// Parameters:			Pointer to array to add samples to.
// Return value:		none
// Any other output:	Writes to samples array.
void Glossy::setSamples(Vector3D* samples){
	// Get halton samples
	//@TODO cite
	std::pair<double, double> randPairs[GLOSSY_NUM_SAMPLES];
	for(int i = 0; i < GLOSSY_NUM_SAMPLES; i++){
		double* rands = halton(i, 2);
		randPairs[i].first = rands[0];
		randPairs[i].second = rands[1];
		delete rands;
	}

	// Convert them to hemisphereical samples.
	hemisphereize(randPairs, samples);
}

// Function name:		hemisphereize
// Function purpose:	Turns randPairs points into hemisphereical samples.
// Parameters:			randPairs: array of input points
//						sampels: array of output Vector3D's
// Return value:		none
// Any other output:	Writes to samples array.
void Glossy::hemisphereize(const std::pair<double, double>* randPairs, Vector3D* samples){
	// Pretty much taken verbatum from RTftGU
	for(int j = 0; j < GLOSSY_NUM_SAMPLES; j++) {
		float cos_phi = cos(2.0 * PI * randPairs[j].first);
		float sin_phi = sin(2.0 * PI * randPairs[j].first);	
		float cos_theta = pow((1.0 - randPairs[j].second), 1.0 / (exp + 1.0));
		float sin_theta = sqrt (1.0 - cos_theta * cos_theta);
		float pu = sin_theta * cos_phi;
		float pv = sin_theta * sin_phi;
		float pw = cos_theta;
		samples[j] = Vector3D(pu, pv, pw);
	}
}





