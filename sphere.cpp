#include <iostream>
#include <math.h>
#include "sphere.h"
#include "Constants.h"
using namespace std;

// ---- Default Constructor ----
Sphere::Sphere(): r(1), c(Point3D()){
	sdr = Shader();
}

// ---- Constructor ----
Sphere::Sphere(double _r, Point3D _c): r(_r), c(_c){
	sdr = Shader();
}

/*
// ---- Copy constructor ----
Sphere::Sphere(const Sphere& s):
	object(s),
	r(s.r),
	c(s.c){
	sdr = Shader();
}

// ---- Assignment operator ----
Sphere& Sphere::operator=(const Sphere& rhs){
	color = rhs.color;
	r = rhs.r;
	c = rhs.c;
	sdr = rhs.sdr;
	return *this;
}

// ---- Destructor ----
Sphere::~Sphere(){
}
*/

Sphere* Sphere::clone(void){
	return new Sphere(*this);
}

bool Sphere::hit(const Ray& ray, double& t){
	double A = ray.d * ray.d;
	double B = 2*(ray.o - c) * ray.d;
	double C = (ray.o - c) * (ray.o - c) - r*r;
	double disc = B*B - 4*A*C;


	if(disc < 0){
		return false;
	}
	else{
		return true;
	}


	//@TODO
	if(fabs(disc) < kEpsilon){

	}
	
}

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
		sr.hitShader = &sdr;

		// Push hitPoint away from surface slightly
		sr.hitPoint.x += sr.hitNormal.x * .000001;
		sr.hitPoint.y += sr.hitNormal.y * .000001;
		sr.hitPoint.z += sr.hitNormal.z * .000001;

		return true;
	}
	// Not a closer hit
	return false;
}


