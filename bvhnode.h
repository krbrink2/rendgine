#ifndef BVHNODE_H
#define BVHNODE_H


class BVHNode{
public:
	BVHNode();

	bool hit(const Ray& ray, ShadeRec& sr);



}













#endif