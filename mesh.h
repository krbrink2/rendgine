#ifndef MESH_H
#define MESH_H
#include <vector>
#include "object.h"
#include "triangle.h"
#include "Point3D.h"
#include "Vector3D.h"
#include <vector>
#include <fstream>
#include <float.h>
#include <string.h>

typedef struct {
	Matrix matrix;
	Shader* sdr;
	std::vector<Triangle*> faces;
} instance_t;

class Mesh : public Object{
public:
	Mesh();
	Mesh(const char* filename);
	Mesh(const Mesh& mesh);
	Mesh& operator=(const Mesh& rhs);
	virtual ~Mesh();
	Object* clone() const;
	Point3D getMaxPoint();
	Point3D getMinPoint();
	Point3D getMedPoint();
	void addPrimitives(std::vector<Object*>& vect);
	bool hit(const Ray& ray, ShadeRec& sr);	// Must these be declared?
	void clear(void);
	bool load(const char* filename);
	void setShader(const Shader* _sdr);
	void addInstance(const Matrix& matrix, Shader* _sdr);

	std::vector<instance_t> instances;
	bool loaded;
	// faces only serves as a basis for instances
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