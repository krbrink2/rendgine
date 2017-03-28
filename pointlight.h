#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "light.h"
using namespace std;

class PointLight: public Light{
public:
	PointLight();
	PointLight(const Point3D& p);
	RGBColor getIrradiance(const Point3D& p);
	Vector3D getDirection(const Point3D& p);
	void getSamples(vector< pair<Vector3D, RGBColor> >& vect, const Point3D p);
	Point3D point;
};





#endif