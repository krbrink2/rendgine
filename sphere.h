#ifndef SPHERE_H
#define SPHERE_H
#include <vector>
#include "object.h"
#include "shaderec.h"
#include "utils.h"

class Sphere: public Object
{
public:
	Sphere();
	Sphere(double _r, Point3D _c);

	Sphere* clone(void);
	Point3D getMaxPoint();
	Point3D getMinPoint();
	Point3D getMedPoint();
	void addPrimitives(std::vector<Object*>& vect);
	bool hit(const Ray& ray, ShadeRec& sr);

	double r;
	Point3D c;

protected:

private:

};


#endif