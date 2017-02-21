#ifndef LIGHT_H
#define LIGHT_H
#include "Point3D.h"
#include "RGBColor.h"
#include "Vector3D.h"

class Light{
public:
	Light();
	//Light(const Light& l);
	//virtual Light& operator=(const Light& rhs);
	//~Light();
	RGBColor getIrradiance(Point3D p) = 0;

	RGBColor color;


};



#endif