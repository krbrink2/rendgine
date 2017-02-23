#include <iostream>
#include <math.h>
#include "plane.h"

// ---- Default Constructor ----
Plane::Plane():
	Object(),
	a(Point3D()),
	n(Normal())
{}

// ---- Constructor ----
Plane::Plane(Point3D _a, Normal _n):
	Object(),
	a(_a),
	n(_n)
{}

// Function name:		clone
// Function purpose:	Allocate identical sphere
// Parameters:			None
// Return value:		Pointer to new sphere
// Any other output:	None
Plane* Plane::clone(void){
	return new Plane(*this);
}

// Function name:		hit
// Function purpose:	Test ray intersection
// Parameters:			
// 		ray:		Ray being traced
//		sr:			ShadeRec to record values
// Return value:		True if intersects
// Any other output:	Writes to sr
bool Plane::hit(const Ray& ray, ShadeRec& sr){
	double dDotn = ray.d * n;
	if(fabs(dDotn) < kEpsilon){	// parallel
		return false;
	}

	double newt = ((a - ray.o)*n)/dDotn;
	if(newt > 0 && newt < sr.t){
		// register hit
		sr.hitObject = true;
		sr.t = newt;
		sr.hitPoint = ray.o + newt*ray.d;
		sr.hitNormal = n;
		sr.hitShader = sdr;

		// Push hitPoint away from surface slightly
		sr.hitPoint.x += sr.hitNormal.x * .000001;
		sr.hitPoint.y += sr.hitNormal.y * .000001;
		sr.hitPoint.z += sr.hitNormal.z * .000001;
		
		return true;
	}
	else
		return false;
}