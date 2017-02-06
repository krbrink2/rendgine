#ifndef LIGHT_H
#define LIGHT_H
#include "Point3D.h"
#include "RGBColor.h"
#include "Vector3D.h"

class Light{
public:
	RGBColor c;

	Light();
	Light(const Light& l);
	virtual Light& operator=(const Light& rhs);
	~Light();

	virtual Vector3D getDirection(Point3D pnt);
	virtual bool testPath(Point3D pnt);
	virtual void setPoint(Point3D pnt);

	Vector3D dir;

protected:
	Point3D p;


};



#endif