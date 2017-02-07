#ifndef OBJECT_H
#define OBJECT_H
#include "shader.h"
#include "shaderec.h"
#include "Ray.h"
#include "RGBColor.h"

class Object
{
public:
	Object();
	Object(const Object& obj);
	virtual Object& operator=(const Object& rhs);
	virtual ~Object();
	virtual Object* clone() = 0;
	//virtual bool hit(const Ray& ray, double& t) = 0;
	virtual bool hit(const Ray& ray, ShadeRec& sr) = 0;

	Shader sdr;

protected:

};

#endif