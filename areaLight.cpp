#include "areaLight.h"
#include <cassert>
#include <cmath>
#include "world.h"

AreaLight::AreaLight():
	Light(),
	Triangle()
{
	delete sdr;
	sdr = new PureColor(255, 255, 255);
	worldPtr->lights.push_back(this);
}

AreaLight::AreaLight(const Point3D& _v0, const Point3D& _v1, const Point3D& _v2) :
	Light(),
	Triangle(_v0, _v1, _v2)
{
	delete sdr;
	sdr = new PureColor(255, 255, 255);
	worldPtr->lights.push_back(this);
}

// Function name:		clone
// Function purpose:	Returns new clone of this AreaLight.
// Parameters:			none
// Return value:		Pointer to new clone.
// Any other output:	none
Object* AreaLight::clone(void) const{
	return new AreaLight(*this);
}

// Function name:		getIrradiance
// Function purpose:	None. Should not be called.
//		Only used to fullfil inheritance.
// Parameters:			
// Return value:		
// Any other output:	
RGBColor AreaLight::getIrradiance(const Point3D& p){
	assert(0);
	return RGBColor(255, 0, 0); // DO NOT USE

}

// Function name:		getDirection
// Function purpose:	None. Do not call.
// Parameters:			x
// Return value:		x
// Any other output:	x
Vector3D AreaLight::getDirection(const Point3D& p){
	assert(0);
	return Vector3D(0,0,0); // DO NOT USE
}

// Function name:		getSamples
// Function purpose:	Gets sample directions & colors for this light.
// Parameters:			vect to add samples to.
// 						p to get samples relative to.					
// Return value:		none
// Any other output:	Pushed to vect.
void AreaLight::getSamples(vector< pair<Vector3D, RGBColor> >& vect, const Point3D p){
	// Using random barycentric sampling from 
	//	https://chrischoy.github.io/research/barycentric-coordinate-for-mesh-sampling/

	// Generate quasirandom 2D points
	std::pair<double, double> randPairs[AREALIGHT_NUM_SAMPLES];
	for(int i = 0; i < AREALIGHT_NUM_SAMPLES; i++){
		//@TODO make this quasirandom
		double* rands = halton(i, 2);
		// Quasirandom
		randPairs[i].first 	= rands[0];
		randPairs[i].second	= rands[1];
		delete rands;
		// Pseudorandom
		// randPairs[i].first 	= rand_float(0, 1);
		// randPairs[i].second	= rand_float(0, 1);
	}
	// Transform randPairs into 3D points on triangle
	Point3D samplePoints[AREALIGHT_NUM_SAMPLES];
	for(int i = 0; i < AREALIGHT_NUM_SAMPLES; i++){
		double a = sqrt(randPairs[i].first);
		double b = randPairs[i].second;
		samplePoints[i] = (1 - a)*v0 + a*(1 - b)*v1 + a*b*v2;
		// Offset sample slightly from surface
		samplePoints[i].x += .0001*n.x;
		samplePoints[i].y += .0001*n.y;
		samplePoints[i].z += .0001*n.z;
	}

	// For each sample, find irradiance & direction.
	for(int i = 0; i < AREALIGHT_NUM_SAMPLES; i++){
		Vector3D direction = samplePoints[i] - p;
		direction.normalize();
		RGBColor irradiance = RGBColor(0,0,0);
		Ray ray(p, direction);
		ShadeRec sr;
		worldPtr->traceRay(ray, sr);
		if(sr.t >= p.distance(samplePoints[i])){
			// Will need to modify if using fog.
			irradiance = color / AREALIGHT_NUM_SAMPLES;
		}
		// Push to vect
		vect.push_back(pair<Vector3D, RGBColor>(direction, irradiance));
	}		
	return;
}

