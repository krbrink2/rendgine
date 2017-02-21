#ifndef POINTLIGHT_H
#def POINTLIGHT_H
#include "light.h"

class PointLight: public Light{
public:
	PointLight();
	Point3D point;
}





#endif