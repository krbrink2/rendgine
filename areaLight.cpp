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

AreaLight* AreaLight::clone(void){
	return new AreaLight(*this);
}

RGBColor AreaLight::getIrradiance(const Point3D& p){
	assert(0);
	return RGBColor(255, 0, 0); // DO NOT USE

}


Vector3D AreaLight::getDirection(const Point3D& p){
	assert(0);
	return Vector3D(0,0,0); // DO NOT USE
}

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

// bool AreaLight::hit(const Ray& ray, ShadeRec& sr){
// 	// The below math is courtesy of Suffern's Ray Tracing from the Ground Up
// 	double	a = v0.x - v1.x,
// 			b = v0.x - v2.x,
// 			c = ray.d.x,
// 			d = v0.x - ray.o.x;
// 	double	e = v0.y - v1.y,
// 			f = v0.y - v2.y,
// 			g = ray.d.y,
// 			h = v0.y - ray.o.y;
// 	double	i = v0.z - v1.z,
// 			j = v0.z - v2.z,
// 			k = ray.d.z,
// 			l = v0.z - ray.o.z;

// 	double	m = f*k - g*j,
// 			n = h*k - g*l,
// 			p = f*l - h*j;
// 	double	q = g*i - e*k,
// 			s = e*j - f*i;

// 	double	inv_denom = 1.0 / (a*m + b*q + c*s);

// 	double	e1 = d*m - b*n - c*p,
// 			beta = e1 * inv_denom;

// 	if(beta < 0.0)
// 		return false;

// 	double	r = e*l - h*i,
// 			e2 = a*n + d*q + c*r,
// 			gamma = e2 * inv_denom;

// 	if(gamma < 0.0)
// 		return false;
// 	if(beta + gamma > 1.0)
// 		return false;

// 	double	e3 = a*p - b*r + d*s,
// 			newt = e3*inv_denom;

// 	if(newt < kEpsilon)
// 		return false;

// 	if(newt > 0 && newt < sr.t){
// 		// Register hit
// 		sr.hitObject = true;
// 		sr.t = newt;
// 		sr.hitPoint = ray.o + newt*ray.d;
// 		sr.hitNormal = this->n;
// 		sr.hitShader = sdr;

// 		// Push hitPoint away from surface slightly
// 		sr.hitPoint.x += sr.hitNormal.x * .000001;
// 		sr.hitPoint.y += sr.hitNormal.y * .000001;
// 		sr.hitPoint.z += sr.hitNormal.z * .000001;
// 		return true;
// 	}
// 	else
// 		return false;
// }