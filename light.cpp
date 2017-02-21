#include "light.h"

// ---- Default constructor ----
Light::Light():
	color(RGBColor(255, 255, 255))
{}

/*
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

// Function name:		getDirection
// Function purpose:	Get direction from a point to this light
// Parameters:			
//		pnt: 		 A point to get direction from
// Return value:		Direcition to this light
// Any other output:	None
Vector3D Light::getDirection(Point3D pnt){
	Vector3D vect = p - pnt;
	vect.normalize();
	return vect;
}
*/

// Under construction below...
/*
bool Light::testPath(Point3D pnt){
	return false;
}*/


// Function name:		setPoint
// Function purpose:	Set value for pnt member
// Parameters:			Value to set pnt as
// Return value:		None
// Any other output:	None
/*void Light::setPoint(Point3D pnt){
	p = pnt;
}*/