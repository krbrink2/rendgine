#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "object.h"
#include "Constants.h"
#include "Normal.h"
#include "Point3D.h"
#include "Ray.h"

class Triangle: public Object
{
public:
	Triangle();
	Triangle(const Point3D& _v0, const Point3D& _v1, const Point3D& _v2);
	/*
	Triangle(const Triangle& t);
	virtual Triangle& operator=(const Triangle& rhs);
	virtual ~Triangle();
	*/

	virtual Triangle* clone(void);
	//virtual bool hit(const Ray& ray, double& t) = 0;
	virtual bool hit(const Ray& ray, ShadeRec& sr);

	Point3D v0, v1, v2;
	Normal n;

};



#endif