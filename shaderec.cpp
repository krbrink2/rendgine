#include "shaderec.h"

// ---- Constructor ----
ShadeRec::ShadeRec(void){
	hitObject = false;
	t = kHugeValue;
	hitColor = RGBColor(0, 0, 0);
	hitShader = NULL;
}

// ---- Constructor ----
ShadeRec::ShadeRec(const RGBColor& c):
	hitObject(false),
	t(kHugeValue),
	hitColor(c),
	hitShader(NULL)
	{}

/*
// ---- Copy constructor ----
ShadeRec::ShadeRec(const ShadeRec& sr):
	hitObject(sr.hitObject),
	t(sr.t),
	hitPoint(sr.hitPoint),
	hitNormal(sr.hitNormal),
	hitColor(sr.hitColor),
	hitShader(sr.hitShader)
{}

// ---- Assignment Operator ----
ShadeRec& ShadeRec::operator=(const ShadeRec& rhs){
	hitObject = rhs.hitObject;
	t = rhs.t;
	hitPoint = rhs.hitPoint;
	hitNormal = rhs.hitNormal;
	hitColor = rhs.hitColor;
	hitShader = rhs.hitShader;
	return *this;
}

// ---- Destructor ----
ShadeRec::~ShadeRec(void){}
*/