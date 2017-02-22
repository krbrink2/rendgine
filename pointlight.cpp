#include "pointlight.h"
#include "world.h"

// ---- Default constructor ----
PointLight::PointLight():
	Light(),
	point(Point3D(0, 0, 0))
{}

// ---- Constructor ----
PointLight::PointLight(const Point3D& p):
	Light(),
	point(p)
{}

RGBColor PointLight::getIrradiance(const Point3D& p){
	// Check to see if this point is in shadow.

	return color;
}

Vector3D PointLight::getDirection(const Point3D& p){
	Vector3D direction = point - p;
	direction.normalize();
	return direction;
}