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
using namespace std;

#define AREALIGHT_NUM_SAMPLES 		(8)


class AreaLight : public Light, public Triangle{
public:
	AreaLight();
	RGBColor getIrradiance(const Point3D& p);
	Vector3D getDirection(const Point3D& p);
	void getSamples(vector< pair<Vector3D, RGBColor> >& vect, const Point3D p) = 0;

};



#endif