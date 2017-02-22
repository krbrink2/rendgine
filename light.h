#ifndef LIGHT_H
#define LIGHT_H
#include "shaderec.h"
#include "Point3D.h"
#include "Ray.h"
#include "RGBColor.h"
#include "Vector3D.h"

// Forward declarations
class World;

// Globals
extern World* worldPtr;

class Light{
public:
	Light();
	virtual ~Light();
	virtual RGBColor getIrradiance(const Point3D& p) = 0;
	virtual Vector3D getDirection(const Point3D& p) = 0;

	RGBColor color;


};



#endif