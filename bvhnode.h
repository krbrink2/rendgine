#ifndef BVHNODE_H
#define BVHNODE_H
#include <vector>
#include "object.h"
#include "shaderec.h"
#include "utils.h"

#define NUM_BVH_TESTS	(4)

class BVHNode{
public:
	BVHNode();

	bool hit(const Ray& ray, ShadeRec& sr);
	bool hitBB(const Ray& ray);
	Point3D getMaxPoint();
	Point3D getMinPoint();
	Point3D getMedPoint();
	double getSurfaceArea();
	void computePoints();
	void build();

	BVHNode* leftChild;
	BVHNode* rightChild;
	std::vector<Object*> primitives;

protected:
	Point3D minPoint, maxPoint;
};

#endif