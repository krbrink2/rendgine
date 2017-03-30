#ifndef AREALIGHT_H
#define AREALIGHT_H
#include <vector>
#include "halton.hpp"
#include "light.h"
#include "object.h"
#include "pureColor.h"
#include "triangle.h"
#include "utils.h"
using namespace std;

class AreaLight : public Light, public Triangle{
public:
	AreaLight();
	AreaLight(const Point3D& _v0, const Point3D& _v1, const Point3D& _v2);
	RGBColor getIrradiance(const Point3D& p);
	Vector3D getDirection(const Point3D& p);
	void getSamples(vector< pair<Vector3D, RGBColor> >& vect, const Point3D p);

};



#endif