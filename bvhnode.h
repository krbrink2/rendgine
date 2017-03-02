#ifndef BVHNODE_H
#define BVHNODE_H
#include <vector>
#include "object.h"
#include "Point3D.h"

class BVHNode{
public:
	BVHNode();

	bool hit(const Ray& ray, ShadeRec& sr);
	bool hitBB(const Ray& ray);
	Point3D getMaxPoint();
	Point3D getMinPoint();
	Point3D getMedPoint();
	double getSurfaceArea();
	void build();

	BVHNode* leftChild;
	BVHNode* rightChild;
	std::vector<Object*> primitives;

protected:
	computePoints();
	Point3D minPoint, maxPoint;
}

#endif