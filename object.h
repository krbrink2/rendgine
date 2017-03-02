#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include "shader.h"
#include "shaderec.h"
#include "utils.h"

class Object
{
public:
	Object();
	Object(const Object& obj);
	virtual ~Object();
	virtual Object* clone() = 0;
	//virtual bool hit(const Ray& ray, double& t) = 0;
	virtual bool hit(const Ray& ray, ShadeRec& sr) = 0;
	virtual Point3D getMaxPoint() = 0;
	virtual Point3D getMinPoint() = 0;
	virtual Point3D getMedPoint() = 0;
	virtual void addPrimitives(std::vector<Object*>& vect) = 0;

	Shader* sdr;

protected:

};

#endif