#ifndef LIGHT_H
#define LIGHT_H
#include "Point3D.h"
#include "RGBColor.h"
#include "Vector3D.h"

class Light{
public:
	Light();
	virtual ~Light();
	virtual RGBColor getIrradiance(const Point3D& p) = 0;
	virtual Vector3D getDirection(const Point3D& p) = 0;

	RGBColor color;


};



#endif