#ifndef BVHNODE_H
#define BVHNODE_H
#include <vector>
#include "object.h"
#include "shaderec.h"
#include "utils.h"

#define NUM_BVH_TESTS		(3)
#define TERMINATE_NUMBER	(8)

class World;


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
	double getSAH();

	BVHNode* leftChild;
	BVHNode* rightChild;
	std::vector<Object*> primitives;

protected:
	Point3D minPoint, maxPoint;
	void buildTestChildren(BVHNode& left, BVHNode& right, float bound, char dim);
};

#endif