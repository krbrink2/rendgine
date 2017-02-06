#include "light.h"

//@TODO: all of this

// ---- Default constructor ----
Light::Light(){
	
}

// ---- Copy Constructor ----
Light::Light(const Light& l):
	c(l.c),
	dir(l.dir){}

// ---- Assignment operator ----
Light& Light::operator=(const Light& rhs){
	c = rhs.c;
	dir = rhs.dir;
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