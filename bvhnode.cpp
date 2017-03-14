#include "bvhnode.h"
#include <cmath>
#include <cassert>
#include "world.h"

extern World* worldPtr;

// ---- Default constructor ----
BVHNode::BVHNode():
	leftChildIndex(-1),
	rightChildIndex(-1),
	minPoint(Point3D(0,0,0)),
	maxPoint(Point3D(0,0,0))
{}

// Function name:		hit
// Function purpose:	Used for ray intersection
// Parameters:			Ray to intersect, ShadeRec for recording.
// Return value:		True if hit.
// Any other output:	Writes to sr.
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

// Function name:		hitBB
// Function purpose:	Find if Ray hits this bounding volume.
// Parameters:			Ray to follow.
// Return value:		True if hit.
// Any other output:	none
bool BVHNode::hitBB(const Ray& ray) const{
	// Code taken from
	// 	https://tavianator.com/fast-branchless-raybounding-box-intersections/
	double tmin = -kHugeValue, tmax = kHugeValue;
	if(std::fabs(ray.d.x) > kEpsilon){
		double t1 = (minPoint.x - ray.o.x)/ray.d.x;
		double t2 = (maxPoint.x - ray.o.x)/ray.d.x;
		tmin = max(tmin, min(t1, t2));
		tmax = min(tmax, max(t1, t2));
	}
	if(std::fabs(ray.d.y) > kEpsilon){
		double t1 = (minPoint.y - ray.o.y)/ray.d.y;
		double t2 = (maxPoint.y - ray.o.y)/ray.d.y;
		tmin = max(tmin, min(t1, t2));
		tmax = min(tmax, max(t1, t2));
	}
	if(std::fabs(ray.d.z) > kEpsilon){
		double t1 = (minPoint.z - ray.o.z)/ray.d.z;
		double t2 = (maxPoint.z - ray.o.z)/ray.d.z;
		tmin = max(tmin, min(t1, t2));
		tmax = min(tmax, max(t1, t2));
	}
	return tmax > tmin && tmax > 0;
}

// Getter for maxPoint
Point3D BVHNode::getMaxPoint() const{
	return maxPoint;
}

// Getter for minPoint
Point3D BVHNode::getMinPoint() const{
	return minPoint;
}

// Getter for median point
Point3D BVHNode::getMedPoint() const{
	return (maxPoint + minPoint)*.5;
}

// Function name:		getSurfaceArea
// Function purpose:	Returns surface area for
//	surface area heuristic.
// Parameters:			none
// Return value:		Surface area
// Any other output:	none
double BVHNode::getSurfaceArea() const{
	return 2*(maxPoint.x - minPoint.x)
		+ 2*(maxPoint.y - minPoint.y)
		+ 2*(maxPoint.z - minPoint.z);
}

// Function name:		computePoints
// Function purpose:	Sets minPoint and maxPoint
// Parameters:			none
// Return value:		none
// Any other output:	none
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

// Function name:		buildTestChildren
// Function purpose:	Helpter for buildBVH;
//	builds left and right BVHNodes as possible split candidates.
// Parameters:			Blank left and right BVHNode references,
//	bound for split, and dim as x, y, or z dimension.
// Return value:		none
// Any other output:	Writes to left and right
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

// Function name:		buildBVH
// Function purpose:	Given an index into worldPtr->bvh, builds that subtree.
// Parameters:			targetIndex to be built
// Return value:		none
// Any other output:	Pushes to worldPtr->bvh
void buildBVH(const int targetIndex){
	#define 	NODE 	worldPtr->bvh[targetIndex] 

	// You've got a bunch of primitives in your vector already.
	NODE.computePoints();

	// Terminate build at constant number.
	if(NODE.primitives.size() <= TERMINATE_NUMBER){
		NODE.leftChildIndex = NODE.rightChildIndex = -1;
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
	for(size_t i = 0; i < NODE.primitives.size(); i++){
		medianPoint = medianPoint + NODE.primitives[i]->getMedPoint();
	}
	medianPoint.x /= (double)(NODE.primitives.size());
	medianPoint.y /= (double)(NODE.primitives.size());
	medianPoint.z /= (double)(NODE.primitives.size());

	// Build median test children
	NODE.buildTestChildren(xLefts[medianIdx], xRights[medianIdx], medianPoint.x, 'x');
	NODE.buildTestChildren(yLefts[medianIdx], yRights[medianIdx], medianPoint.y, 'y');
	NODE.buildTestChildren(zLefts[medianIdx], zRights[medianIdx], medianPoint.z, 'z');
	// Build test children on left
	double xInc = (medianPoint.x - NODE.minPoint.x)/(2*NUM_BVH_TESTS + 2);
	double yInc = (medianPoint.y - NODE.minPoint.y)/(2*NUM_BVH_TESTS + 2);
	double zInc = (medianPoint.z - NODE.minPoint.z)/(2*NUM_BVH_TESTS + 2);
	for(size_t i = 0; i < NUM_BVH_TESTS; i++){
		NODE.buildTestChildren(xLefts[i], xRights[i], NODE.minPoint.x + i*xInc, 'x');
		NODE.buildTestChildren(yLefts[i], yRights[i], NODE.minPoint.y + i*yInc, 'y');
		NODE.buildTestChildren(zLefts[i], zRights[i], NODE.minPoint.z + i*zInc, 'z');
	}
	// Build test children on right
	xInc = (NODE.maxPoint.x - medianPoint.x)/(2*NUM_BVH_TESTS + 2);
	yInc = (NODE.maxPoint.y - medianPoint.y)/(2*NUM_BVH_TESTS + 2);
	zInc = (NODE.maxPoint.z - medianPoint.z)/(2*NUM_BVH_TESTS + 2);
	for(size_t i = 0; i < NUM_BVH_TESTS; i++){
		NODE.buildTestChildren(xLefts[medianIdx + 1 + i], xRights[medianIdx + 1 + i], medianPoint.x + i*xInc, 'x');
		NODE.buildTestChildren(yLefts[medianIdx + 1 + i], yRights[medianIdx + 1 + i], medianPoint.y + i*yInc, 'y');
		NODE.buildTestChildren(zLefts[medianIdx + 1 + i], zRights[medianIdx + 1 + i], medianPoint.z + i*zInc, 'z');
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
	if(bestScore >= NODE.getSAH()){
		// Terminate!
		NODE.leftChildIndex = NODE.rightChildIndex = -1;
		return;
	}
	// One of them is better!
	// Free to empty my pointers.
	NODE.primitives.clear();
	if(bestDim == 'x'){
		worldPtr->bvh.push_back(xLefts[bestIndex]);
	}
	else if(bestDim == 'y'){
		worldPtr->bvh.push_back(yLefts[bestIndex]);
	}
	else{
		worldPtr->bvh.push_back(zLefts[bestIndex]);
	}
	NODE.leftChildIndex = worldPtr->bvh.size() - 1;
	buildBVH(NODE.leftChildIndex);
	if(bestDim == 'x'){
		worldPtr->bvh.push_back(xRights[bestIndex]);
	}
	else if(bestDim == 'y'){
		worldPtr->bvh.push_back(yRights[bestIndex]);	
	}
	else{
		worldPtr->bvh.push_back(zRights[bestIndex]);
	}
	NODE.rightChildIndex = worldPtr->bvh.size() - 1;
	buildBVH(NODE.rightChildIndex);

	#undef 		NODE
}

// Function name:		getSAH
// Function purpose:	Finds surface area heuristic value.
// Parameters:			none
// Return value:		SAH value
// Any other output:	none
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


