#ifndef OBJECT_H
#define OBJECT_H
#include "Ray.h"
#include "RGBColor.h"

class Object
{
public:
	Object();
	~Object();
	virtual bool hit(const Ray& ray, double& t) = 0;

	RGBColor color;	

protected:


};

#endif