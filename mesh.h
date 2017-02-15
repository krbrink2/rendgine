#ifndef MESH_H
#define MESH_H

#include "object.h"
#include "triangle.h"
#include "Point3D.h"
#include <vector>

class Mesh : public Object{
	Mesh();
	Mesh(const char* filename, Point3D _p);
	Mesh(const Mesh& mesh);
	Mesh& operator=(const Mesh& rhs);
	virtual ~Mesh();
	Mesh* clone();
	bool hit(const Ray& ray, ShadeRec& sr);	// Must these be declared?
	void clear(void);
	bool load(const char* filename);

	Point3D p;
	std::vector<Triangle*> faces;

};







#endif