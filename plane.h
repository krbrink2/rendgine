#ifndef PLANE_H
#define PLANE_H
#include "object.h"
#include "shaderec.h"
#include "Constants.h"
#include "Normal.h"
#include "Point3D.h"
#include "Ray.h"
#include "Vector3D.h"

class Plane: public Object
{
public:
	Plane();
	Plane(Point3D _a, Normal _n);
	~Plane();

	Plane* clone(void);
	bool hit(const Ray& ray, double& t);
	bool hit(const Ray& ray, ShadeRec& sr);

protected:
	Point3D a;		// Anchor point
	Normal n;		// Plane normal
};

#endif