#include "bvhnode.h"

BVHNode::BVHNode(){

}

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