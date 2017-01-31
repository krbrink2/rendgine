#include "shaderec.h"

// ---- Constructor ----
ShadeRec::ShadeRec(World& _w): w(_w) {
	hitObject = false;
	t = kHugeValue;
	hitColor = _w.backgroundColor;
}

// ---- Copy constructor ----
ShadeRec::ShadeRec(const ShadeRec& sr):
	w(sr.w),
	hitObject(sr.hitObject),
	t(sr.t),
	hitPoint(sr.hitPoint),
	hitNormal(sr.hitNormal),
	hitColor(sr.hitColor);
{}

// ---- Assignment Operator ----
ShadeRec& ShadeRec::operator=(const ShadeRec& rhs){
	w = rhs.w;
	hitObject = rhs.hitObject;
	t = rhs.t;
	hitPoint = rhs.hitPoint;
	hitNormal = rhs.hitNormal;
	hitColor(rhs.hitColor);
	return *this;
}