#include <iostream>
#include <math.h>
#include "plane.h"

// ---- Default Constructor ----
Plane::Plane(): a(Point3D()), n(Normal()) {
	sdr = Shader();
}

// ---- Constructor ----
Plane::Plane(Point3D _a, Normal _n): a(_a), n(_n) {
	sdr = Shader();
}

Plane::~Plane(){

}

Plane* Plane::clone(void){
	return new Plane(*this);
}

bool Plane::hit(const Ray& ray, double& t){
	double dDotn = ray.d * n;
	if(fabs(dDotn) < kEpsilon){
		return false;
	}
	
	double newt = ((a - ray.o)*n)/dDotn;
	if(newt > 0 && newt < t){
		t = newt;
		return true;
	}
	else{
		return false;
	}
}

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
		sr.hitColor = color;
		sr.hitShader = &sdr;
		return true;
	}
	else
		return false;
}