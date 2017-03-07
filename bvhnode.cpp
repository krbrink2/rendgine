#include "bvhnode.h"
#include <cmath>
#include <cassert>
#include "world.h"

extern World* worldPtr;

BVHNode::BVHNode():
	leftChildIndex(-1),
	rightChildIndex(-1),
	minPoint(Point3D(0,0,0)),
	maxPoint(Point3D(0,0,0))
{}

bool BVHNode::hit(const Ray& ray, ShadeRec& sr) const{
	bool val = false;
	// If leaf...
	if(leftChildIndex == -1){
		// Sanity check
		assert(rightChildIndex == -1);

		for(auto ptr : primitives){
			val |= ptr->hit(ray, sr);
		}
	}

	// If non-leaf...
	else{
		if(worldPtr->bvh[leftChildIndex].hitBB(ray)){
			val |= worldPtr->bvh[leftChildIndex].hit(ray, sr);
		}
		if(worldPtr->bvh[rightChildIndex].hitBB(ray)){
			val |= worldPtr->bvh[rightChildIndex].hit(ray, sr);
		}
	}
	return val;
}

bool BVHNode::hitBB(const Ray& ray) const{
	// Code taken from
	// 	https://tavianator.com/fast-branchless-raybounding-box-intersections/
	//@TODO 									//@CITE!!!!!!!!!!!!!!!!!!!!!!!!
	double tmin = -kHugeValue, tmax = kHugeValue;
	if(std::fabs(ray.d.x) > kEpsilon){
		double t1 = (minPoint.x - ray.o.x)/ray.d.x;
		double t2 = (maxPoint.x - ray.o.x)/ray.d.x;
		tmin = max(tmin, min(t1, t2));
		tmax = min(tmax, max(t1, t2));
	}
	if(std::fabs(ray.d.y) > kEpsilon){
		double t1 = (minPoint.y - ray.o.x)/ray.d.y;
		double t2 = (maxPoint.y - ray.o.x)/ray.d.y;
		tmin = max(tmin, min(t1, t2));
		tmax = min(tmax, max(t1, t2));
	}
	if(std::fabs(ray.d.z) > kEpsilon){
		double t1 = (minPoint.z - ray.o.x)/ray.d.z;
		double t2 = (maxPoint.z - ray.o.x)/ray.d.z;
		tmin = max(tmin, min(t1, t2));
		tmax = min(tmax, max(t1, t2));
	}
	return tmax > tmin && tmax > 0;
}

Point3D BVHNode::getMaxPoint() const{
	return maxPoint;
}

Point3D BVHNode::getMinPoint() const{
	return minPoint;
}

Point3D BVHNode::getMedPoint() const{
	return (maxPoint + minPoint)*.5;
}

double BVHNode::getSurfaceArea() const{
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

// Helper function
void BVHNode::buildTestChildren(BVHNode& left, BVHNode& right, double bound, char dim){
	for(size_t i = 0; i < primitives.size(); i++){
		// Sort primitives.

		// If this primitive is on the left, put it into left child.
		double maxVal; //, minVal;
		if(dim == 'x'){
			maxVal = primitives[i]->getMaxPoint().x;
		}
		else if(dim == 'y'){
			maxVal = primitives[i]->getMaxPoint().y;
		}
		else{
			maxVal = primitives[i]->getMaxPoint().z;
		}

		if(maxVal < bound){
			left.primitives.push_back(primitives[i]);
		}
		else{
			right.primitives.push_back(primitives[i]);
		}
	}
}

void BVHNode::build(const int targetIndex){
	#define 	NODE 	worldPtr->bvh[targetIndex] 

	// You've got a bunch of primitives in your vector already.
	computePoints();

	// Terminate build at constant number.
	if(NODEprimitives.size() <= TERMINATE_NUMBER){
		NODEleftChildIndex = NODErightChildIndex = -1;
		return;
	}

	BVHNode xLefts[NUM_BVH_TESTS*2 + 1];
	BVHNode xRights[NUM_BVH_TESTS*2 + 1];
	BVHNode yLefts[NUM_BVH_TESTS*2 + 1];
	BVHNode yRights[NUM_BVH_TESTS*2 + 1];
	BVHNode zLefts[NUM_BVH_TESTS*2 + 1];
	BVHNode zRights[NUM_BVH_TESTS*2 + 1];
	int medianIdx = NUM_BVH_TESTS;
	Point3D medianPoint(0,0,0);
	for(size_t i = 0; i < NODEprimitives.size(); i++){
		medianPoint = medianPoint + NODEprimitives[i]->getMedPoint();
	}
	medianPoint.x /= (double)(NODEprimitives.size());
	medianPoint.y /= (double)(NODEprimitives.size());
	medianPoint.z /= (double)(NODEprimitives.size());

	// Build median test children
	buildTestChildren(xLefts[medianIdx], xRights[medianIdx], medianPoint.x, 'x');
	buildTestChildren(yLefts[medianIdx], yRights[medianIdx], medianPoint.y, 'y');
	buildTestChildren(zLefts[medianIdx], zRights[medianIdx], medianPoint.z, 'z');
	// Build test children on left
	double xInc = (medianPoint.x - NODEminPoint.x)/(2*NUM_BVH_TESTS + 2);
	double yInc = (medianPoint.y - NODEminPoint.y)/(2*NUM_BVH_TESTS + 2);
	double zInc = (medianPoint.z - NODEminPoint.z)/(2*NUM_BVH_TESTS + 2);
	for(size_t i = 0; i < NUM_BVH_TESTS; i++){
		buildTestChildren(xLefts[i], xRights[i], NODEminPoint.x + i*xInc, 'x');
		buildTestChildren(yLefts[i], yRights[i], NODEminPoint.y + i*yInc, 'y');
		buildTestChildren(zLefts[i], zRights[i], NODEminPoint.z + i*zInc, 'z');
	}
	// Build test children on right
	xInc = (NODEmaxPoint.x - medianPoint.x)/(2*NUM_BVH_TESTS + 2);
	yInc = (NODEmaxPoint.y - medianPoint.y)/(2*NUM_BVH_TESTS + 2);
	zInc = (NODEmaxPoint.z - medianPoint.z)/(2*NUM_BVH_TESTS + 2);
	for(size_t i = 0; i < NUM_BVH_TESTS; i++){
		buildTestChildren(xLefts[medianIdx + 1 + i], xRights[medianIdx + 1 + i], medianPoint.x + i*xInc, 'x');
		buildTestChildren(yLefts[medianIdx + 1 + i], yRights[medianIdx + 1 + i], medianPoint.y + i*yInc, 'y');
		buildTestChildren(zLefts[medianIdx + 1 + i], zRights[medianIdx + 1 + i], medianPoint.z + i*zInc, 'z');
	}

	// Find best test children
	double bestScore = kHugeValue;
	char bestDim = 'x';
	int bestIndex = 0;
	// For each attempt...
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
		leftChildIndex = rightChildIndex = -1;
		return;
	}
	// One of them is better!
	// Free to empty my pointers.
	primitives.clear();
	if(bestDim == 'x'){
		worldPtr->bvh.push_back(xLefts[bestIndex]);
	}
	else if(bestDim == 'y'){
		worldPtr->bvh.push_back(yLefts[bestIndex]);		//@BUG
	}
	else{
		worldPtr->bvh.push_back(zLefts[bestIndex]);
	}
	leftChildIndex = worldPtr->bvh.size() - 1;
	worldPtr->bvh[leftChildIndex].build();
	if(bestDim == 'x'){
		worldPtr->bvh.push_back(xRights[bestIndex]);
	}
	else if(bestDim == 'y'){
		worldPtr->bvh.push_back(yRights[bestIndex]);	
	}
	else{
		worldPtr->bvh.push_back(zRights[bestIndex]);
	}
	rightChildIndex = worldPtr->bvh.size() - 1;
	worldPtr->bvh[rightChildIndex].build();

	#undef 		NODE
}

// Get surface area heuristic value
double BVHNode::getSAH() const{
	double val = 0;
	// val = sum of surface area of each primitive's BB
	for(auto itr : primitives){
		Point3D maxPoint = itr->getMaxPoint();
		Point3D minPoint = itr->getMinPoint();
		val += 2*(maxPoint.x - minPoint.x)*(maxPoint.y - minPoint.y);
		val += 2*(maxPoint.y - minPoint.y)*(maxPoint.z - minPoint.z);
		val += 2*(maxPoint.z - minPoint.z)*(maxPoint.x - minPoint.x);
	}
	return primitives.size()*val;
}


