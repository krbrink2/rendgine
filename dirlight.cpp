#include "dirlight.h"

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
	return color;
}

Vector3D DirLight::getDirection(const Point3D& p){
	//Vector3D foo = -direction;
	return -direction;//foo;
}