#include "areaLight.h"

AreaLight::AreaLight():
	Light(),
	Triangle()
{
	delete sdr;
	sdr = new PureColor(255, 255, 255);
}

RGBColor AreaLight::getIrradiance(const Point3D& p){
	return RGBColor(255, 0, 0); //@TODO modify
}


Vector3D AreaLight::getDirection(const Point3D& p){
	return Vector3D(0,0,0); //@TODO modify
}