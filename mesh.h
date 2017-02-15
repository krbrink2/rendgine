#ifndef MESH_H
#define MESH_H

#include "object.h"
#include "triangle.h"
#include "Point3D.h"
#include "Vector3D.h"
#include <vector>
#include <fstream>
#include <float.h>
#include <string.h>

class Mesh : public Object{
public:
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
	bool loaded;
	std::vector<Triangle*> faces;


private:
	bool dataPass(FILE* file, std::vector<Point3D>& vertices, 
		std::vector<Normal>& normals);
	bool facePass(FILE* file, std::vector<Point3D>& vertices, 
		std::vector<Normal>& normals);
	Vector3D maxs;
	Vector3D mins;
	int numTriangles;
};







#endif