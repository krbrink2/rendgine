#include "dirlight.h"
#include "world.h"
#include <iostream>

extern World* worldPtr;

// ---- Default constructor ----
DirLight::DirLight():
	Light(),
	direction(Vector3D(1, 1, -1))
{}

// ---- Constructor ----
DirLight::DirLight(const Vector3D& dir):
	Light(){
	direction = dir;
	direction.normalize();

}

RGBColor DirLight::getIrradiance(const Point3D& p){
	// Check to see if p is in a shadow.
	Ray ray;
	ray.o = p;
	ray.d = direction;
	ray.d.normalize();
	ShadeRec sr;
	worldPtr->traceRay(ray, sr);

	if(sr.hitObject){
		return RGBColor(0,0,0);
	}
	else
		return color;
}

Vector3D DirLight::getDirection(const Point3D& p){
	return direction;
}