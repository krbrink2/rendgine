#ifndef DIRLIGHT_H
#define DIRLIGHT_H
#include "light.h"

class DirLight: public Light{
public:
	DirLight();
	DirLight(const Vector3D& dir);
	RGBColor getIrradiance(const Point3D& p);
	Vector3D getDirection(const Point3D& p);

	Vector3D direction;

};


#endif