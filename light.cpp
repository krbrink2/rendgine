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
	// vect = p - pnt;
	Vector3D vect;
	return vect;
}

bool Light::testPath(Point3D pnt){
	return false;
}