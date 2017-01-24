#include "plane.h"
#include "Constants.h"

// ---- Default Constructor ----
Plane::Plane(): a(Point3D()), n(Normal()) {

}

// ---- Constructor ----
Plane::Plane(Point3D _a, Normal _n): a(_a), n(_n) {

}

Plane::~Plane(){

}

bool Plane::hit(const Ray& ray, double& t){
	double dDotn = ray.d * n;
	if(dDotn < kEpsilon){
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