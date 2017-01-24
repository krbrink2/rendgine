#ifndef SPHERE_H
#define SPHERE_H
#include "object.h"
#include "Normal.h"
#include "Point3D.h"
#include "Ray.h"
#include "Vector3D.h"

class Sphere: public Object
{
public:
	Sphere();
	Sphere(double _r, Point3D _c);
	~Sphere();

	bool hit(const Ray& ray, double& t);

	double r;
	Point3D c;

protected:

private:

};


#endif