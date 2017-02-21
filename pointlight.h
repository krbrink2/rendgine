#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "light.h"

class PointLight: public Light{
public:
	PointLight();
	RGBColor getIrradiance(Point3D p);
	Point3D point;
};





#endif