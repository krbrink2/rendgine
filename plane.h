#ifndef PLANE_H
#define PLANE_H
#include "Normal.h"
#include "Point3D.h"
#include "Ray.h"
#include "Vector3D.h"

class Plane: public object
{
public:
	Plane();
	Plane(Point3D _a, Normal _n);
	~Plane();

	virtual bool hit(const Ray& ray, double& t);

protected:
	Point3D a;		// Anchor point
	Normal n;		// Plane normal
};

#endif