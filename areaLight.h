#ifndef AREALIGHT_H
#define AREALIGHT_H
#include <vector>
#include "light.h"
#include "object.h"
#include "pureColor.h"
#include "triangle.h"
#include "Constants.h"
#include "Normal.h"
#include "Point3D.h"
#include "Ray.h"


class AreaLight : public Light, public Triangle{
public:
	AreaLight();
	RGBColor getIrradiance(const Point3D& p);
	Vector3D getDirection(const Point3D& p);

};



#endif