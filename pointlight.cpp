#include "pointlight.h"

// ---- Default constructor ----
PointLight::PointLight():
	Light(),
	point(Point3D(0, 0, 0))
{}

RGBColor PointLight::getIrradiance(Point3D p){
	return color;
}