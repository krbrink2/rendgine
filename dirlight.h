#ifndef DIRLIGHT_H
#define DIRLIGHT_H
#include "light.h"

class DirLight: public Light{
public:
	DirLight();
	RGBColor getIrradiance(Point3D p);

	Vector3D direction;

};


#endif