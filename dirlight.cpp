#include "dirlight.h"

// ---- Default constructor ----
DirLight::DirLight():
	Light(),
	direction(Vector3D(1, 1, -1))
{}

RGBColor DirLight::getIrradiance(Point3D p){
	return color;
}