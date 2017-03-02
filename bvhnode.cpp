#include "bvhnode.h"

BVHNode::BVHNode()
{}

bool BVHNode::hit(const Ray& ray, ShadeRec& sr){
	return false;
}

bool BVHNode::hitBB(const Ray& ray){
	return false;
}

Point3D BVHNode::getMaxPoint(){
	return maxPoint;
}

Point3D BVHNode::getMinPoint(){
	return minPoint;
}

Point3D BVHNode::getMedPoint(){
	return (maxPoint + minPoint)*.5;
}

double BVHNode::getSurfaceArea(){
	return 2*(maxPoint.x - minPoint.x)
		+ 2*(maxPoint.y - minPoint.y)
		+ 2*(maxPoint.z - minPoint.z);
}

void BVHNode::computePoints(){
	minPoint = Point3D(kHugeValue, kHugeValue, kHugeValue);
	maxPoint = Point3D(-kHugeValue, -kHugeValue, -kHugeValue);
	for(size_t i = 0; i < primitives.size(); i++){
		Point3D testMaxPoint = primitives[i]->getMaxPoint();
		Point3D testMinPoint = primitives[i]->getMinPoint();

		maxPoint.x = max(maxPoint.x, testMaxPoint.x);
		maxPoint.y = max(maxPoint.y, testMaxPoint.y);
		maxPoint.z = max(maxPoint.z, testMaxPoint.z);

		minPoint.x = min(minPoint.x, testMinPoint.x);
		minPoint.y = min(minPoint.y, testMinPoint.y);
		minPoint.z = min(minPoint.z, testMinPoint.z);
	}
}

void BVHNode::build(){

	// You've got a bunch of primitives in your vector.

	BVHNode xLefts[NUM_BVH_TESTS*2 + 1];
	BVHNode xRights[NUM_BVH_TESTS*2 + 1];
	BVHNode yLefts[NUM_BVH_TESTS*2 + 1];
	BVHNode yRights[NUM_BVH_TESTS*2 + 1];
	BVHNode zLefts[NUM_BVH_TESTS*2 + 1];
	BVHNode zRights[NUM_BVH_TESTS*2 + 1];



	return;
}
