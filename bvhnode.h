#ifndef BVHNODE_H
#define BVHNODE_H
#include <vector>
#include "object.h"
#include "shaderec.h"
#include "utils.h"

#define NUM_BVH_TESTS		(3)
#define TERMINATE_NUMBER	(8)

class World;

void buildBVH(const int targetIndex);

class BVHNode{
public:
	BVHNode();

	bool hit(const Ray& ray, ShadeRec& sr) const;
	bool hitBB(const Ray& ray) const;
	Point3D getMaxPoint() const;
	Point3D getMinPoint() const;
	Point3D getMedPoint() const;
	double getSurfaceArea() const;
	void computePoints();
	double getSAH() const;

	int leftChildIndex, rightChildIndex;
	std::vector<Object*> primitives;
	Point3D minPoint, maxPoint;
	void buildTestChildren(BVHNode& left, BVHNode& right, double bound, char dim);
};

#endif