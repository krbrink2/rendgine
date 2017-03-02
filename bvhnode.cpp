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

void BVHNode::buildTestChildren(BVHNode& left, BVHNode& right, float bound, char dim){
	for(size_t i = 0; i < primitives.size(); i++){
		// If this primitive is on the left, put it into left child.
		double minVal, maxVal;
		if(dim == 'x'){
			minVal = primitives[i].getMinPoint().x;
			maxVal = primitives[i].getMaxPoint().x;
		}
		else if(dim == 'y'){
			minVal = primitives[i].getMinPoint().y;
			maxVal = primitives[i].getMaxPoint().y;
		}
		else{
			minVal = primitives[i].getMinPoint().z;
			maxVal = primitives[i].getMaxPoint().z;
		}

		if(maxVal < bound){
			left.primitives.push_back(primitives[i]);
		}
		else{
			right.primitives.push_back(primitives[i]);
		}
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
	int medianIdx = NUM_BVH_TESTS;
	Point3D medianPoint(0,0,0);
	for(size_t i = 0; i < primitives.size(); i++){
		medianPoint += primitives[i].getMedPoint();
	}
	medianPoint.x /= (float)(primitives.size());
	medianPoint.y /= (float)(primitives.size());
	medianPoint.z /= (float)(primitives.size());

	// Build median test children
	buildTestChildren(xLefts[medianIdx], xRights[medianIdx], medianPoint.x, 'x');
	buildTestChildren(yLefts[medianIdx], yRights[medianIdx], medianPoint.y, 'y');
	buildTestChildren(zLefts[medianIdx], zRights[medianIdx], medianPoint.z, 'z');
	// Other x's
	double xInc = (maxPoint.x - minPoint.x)/(2*NUM_BVH_TESTS + 2);
	double yInc = (maxPoint.y - minPoint.y)/(2*NUM_BVH_TESTS + 2);
	double zInc = (maxPoint.z - minPoint.z)/(2*NUM_BVH_TESTS + 2);
	//for(size_t i = 0; i < )


	return;
}
