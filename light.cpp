#include "light.h"

//@TODO: all of this

// ---- Default constructor ----
Light::Light(){
	
}

// ---- Copy Constructor ----
Light::Light(const Light& l){
	
}

// ---- Assignment operator ----
Light& Light::operator=(const Light& rhs){
	return *this;
}

// ---- Destructor ----
Light::~Light(){}

Vector3D Light::getDirection(Point3D pnt){
	Vector3D vect = p - pnt;
	vect.normalize();
	return vect;
}

bool Light::testPath(Point3D pnt){
	return false;
}

void Light::setPoint(Point3D pnt){
	p = pnt;
}