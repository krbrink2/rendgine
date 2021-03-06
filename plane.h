#ifndef PLANE_H
#define PLANE_H
#include <vector>
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

	Plane* clone(void);
	Point3D getMaxPoint();
	Point3D getMinPoint();
	Point3D getMedPoint();
	void addPrimitives(std::vector<Object*>& vect);
	bool hit(const Ray& ray, ShadeRec& sr);

protected:
	Point3D a;		// Anchor point
	Normal n;		// Plane normal
};

#endif