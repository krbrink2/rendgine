#include "bvhnode.h"
#include "world.h"

extern World* worldPtr;

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
			minVal = primitives[i]->getMinPoint().x;
			maxVal = primitives[i]->getMaxPoint().x;
		}
		else if(dim == 'y'){
			minVal = primitives[i]->getMinPoint().y;
			maxVal = primitives[i]->getMaxPoint().y;
		}
		else{
			minVal = primitives[i]->getMinPoint().z;
			maxVal = primitives[i]->getMaxPoint().z;
		}

		if(maxVal < bound){
			left.primitives.push_back(primitives[i]);
		}
		else{
			right.primitives.push_back(primitives[i]);
		}
		maxVal = minVal;
	}
}

void BVHNode::build(){
	// You've got a bunch of primitives in your vector already.

	// Terminate build at constant number.
	if(primitives.size() < TERMINATE_NUMBER)
		return;

	BVHNode xLefts[NUM_BVH_TESTS*2 + 1];
	BVHNode xRights[NUM_BVH_TESTS*2 + 1];
	BVHNode yLefts[NUM_BVH_TESTS*2 + 1];
	BVHNode yRights[NUM_BVH_TESTS*2 + 1];
	BVHNode zLefts[NUM_BVH_TESTS*2 + 1];
	BVHNode zRights[NUM_BVH_TESTS*2 + 1];
	int medianIdx = NUM_BVH_TESTS;
	Point3D medianPoint(0,0,0);
	for(size_t i = 0; i < primitives.size(); i++){
		medianPoint = medianPoint + primitives[i]->getMedPoint();
	}
	medianPoint.x /= (float)(primitives.size());
	medianPoint.y /= (float)(primitives.size());
	medianPoint.z /= (float)(primitives.size());

	// Build median test children
	buildTestChildren(xLefts[medianIdx], xRights[medianIdx], medianPoint.x, 'x');
	buildTestChildren(yLefts[medianIdx], yRights[medianIdx], medianPoint.y, 'y');
	buildTestChildren(zLefts[medianIdx], zRights[medianIdx], medianPoint.z, 'z');
	double xInc = (medianPoint.x - minPoint.x)/(2*NUM_BVH_TESTS + 2);
	double yInc = (medianPoint.y - minPoint.y)/(2*NUM_BVH_TESTS + 2);
	double zInc = (medianPoint.z - minPoint.z)/(2*NUM_BVH_TESTS + 2);
	for(size_t i = 0; i < NUM_BVH_TESTS; i++){
		buildTestChildren(xLefts[i], xRights[i], minPoint.x + i*xInc, 'x');
		buildTestChildren(yLefts[i], yRights[i], minPoint.y + i*yInc, 'y');
		buildTestChildren(zLefts[i], zRights[i], minPoint.z + i*zInc, 'z');
	}
	xInc = (maxPoint.x - medianPoint.x)/(2*NUM_BVH_TESTS + 2);
	yInc = (maxPoint.y - medianPoint.y)/(2*NUM_BVH_TESTS + 2);
	zInc = (maxPoint.z - medianPoint.z)/(2*NUM_BVH_TESTS + 2);
	for(size_t i = 0; i < NUM_BVH_TESTS; i++){
		buildTestChildren(xLefts[medianIdx + 1 + i], xRights[medianIdx + 1 + i], medianPoint.x + i*xInc, 'x');
		buildTestChildren(yLefts[medianIdx + 1 + i], yRights[medianIdx + 1 + i], medianPoint.y + i*yInc, 'y');
		buildTestChildren(zLefts[medianIdx + 1 + i], zRights[medianIdx + 1 + i], medianPoint.z + i*zInc, 'z');
	}

	// Find best test children
	double bestScore = kHugeValue;
	char bestDim = 'x';
	int bestIndex = medianIdx;
	for(size_t i = 0; i < NUM_BVH_TESTS*2 + 1; i++){
		double testScore = xLefts[i].getSAH() + xRights[i].getSAH();
		if(testScore < bestScore){
			bestScore = testScore;
			bestDim = 'x';
			bestIndex = i;
		}
		testScore = yLefts[i].getSAH() + yRights[i].getSAH();
		if(testScore < bestScore){
			bestScore = testScore;
			bestDim = 'y';
			bestIndex = i;
		}
		testScore = zLefts[i].getSAH() + zRights[i].getSAH();
		if(testScore < bestScore){
			bestScore = testScore;
			bestDim = 'z';
			bestIndex = i;
		}
	}
	// What if none is better?
	if(bestScore >= getSAH()){
		// Terminate!
		return;
		leftChild = rightChild = NULL;
	}
	// One of them is better!
	if(bestDim == 'x'){
		worldPtr->bvh.push_back(xLefts[bestIndex]);
	}
	else if(bestDim == 'y'){
		worldPtr->bvh.push_back(yLefts[bestIndex]);	
	}
	else{
		worldPtr->bvh.push_back(zLefts[bestIndex]);
	}
	leftChild = &(worldPtr->bvh.back());
	leftChild->build();
	if(bestDim == 'x'){
		worldPtr->bvh.push_back(xRights[bestIndex]);
	}
	else if(bestDim == 'y'){
		worldPtr->bvh.push_back(yRights[bestIndex]);	
	}
	else{
		worldPtr->bvh.push_back(zRights[bestIndex]);
	}
	rightChild = &(worldPtr->bvh.back());
	leftChild->build();

	return;
}


double BVHNode::getSAH(){
	double val = 0;
	for(auto itr : primitives){
		Point3D maxPoint = itr->getMaxPoint();
		Point3D minPoint = itr->getMinPoint();
		val += 2*(maxPoint.x - minPoint.x)*(maxPoint.y - minPoint.y);
		val += 2*(maxPoint.y - minPoint.y)*(maxPoint.z - minPoint.z);
		val += 2*(maxPoint.z - minPoint.z)*(maxPoint.x - minPoint.x);
	}
	return primitives.size()*val;
}


