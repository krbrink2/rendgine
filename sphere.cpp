#include <iostream>
#include <math.h>
#include "sphere.h"
using namespace std;

// ---- Default Constructor ----
Sphere::Sphere():
	Object(),
	r(1),
	c(Point3D())
{}

// ---- Constructor ----
Sphere::Sphere(double _r, Point3D _c):
	Object(),
	r(_r),
	c(_c)
{}

// Function name:		clone
// Function purpose:	Allocated identical sphere
// Parameters:			None
// Return value:		Pointer to new sphere
// Any other output:	None
Sphere* Sphere::clone(void){
	return new Sphere(*this);
}

Point3D Sphere::getMinPoint(){
	return Point3D(c.x-r, c.y-r, c.z-r);
}

Point3D Sphere::getMaxPoint(){
	return Point3D(c.x+r, c.y+r, c.z+r);
}

Point3D Sphere::getMedPoint(){
	return c;
}

void Sphere::addPrimitives(std::vector<Object*>& vect){
	vect.push_back(this);
}

// Function name:		hit
// Function purpose:	Tests intersection for ray, records shading info is hits.
// Parameters:			
//		ray:		Ray being traced
//		sr:			ShadeRec to store info
// Return value:		True if intersects
// Any other output:	None
bool Sphere::hit(const Ray& ray, ShadeRec& sr){
	double A = ray.d * ray.d;
	double B = 2*(ray.o - c) * ray.d;
	double C = (ray.o - c) * (ray.o - c) - r*r;
	double disc = B*B - 4*A*C;

	if(disc < 0){
		return false;
	}
	double t0 = (-B + sqrt(disc))/(2*A);
	double t1 = (-B - sqrt(disc))/(2*A);
	double newt;
	if(t0 < 0 && t1 < 0){
		return false;
	}
	else if(t0 < 0 && t1 > 0){
		newt = t1;
	}
	else if(t0 > 0 && t1 < 0){
		newt = t0;
	}
	else if(t0 > 0 && t1 > 0){
		newt = min(t0, t1);
	}

	if(newt < sr.t){
		// Register hit
		sr.hitObject = true;
		sr.t = newt;
		sr.hitPoint = ray.o + newt*ray.d;
		sr.hitNormal = sr.hitPoint - c;
		sr.hitNormal.normalize();
		sr.hitShader = sdr;

		// Push hitPoint away from surface slightly
		sr.hitPoint.x += sr.hitNormal.x * .000001;
		sr.hitPoint.y += sr.hitNormal.y * .000001;
		sr.hitPoint.z += sr.hitNormal.z * .000001;

		return true;
	}
	// Not a closer hit
	return false;
}


