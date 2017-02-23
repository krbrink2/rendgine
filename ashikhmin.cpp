#include "ashikhmin.h"
#include "world.h"
#include "shaderec.h"

// ---- Default constructor ----
Ashikhmin::Ashikhmin():
	Shader(),
	exp(100)
{}

// ---- Constructor ----
Ashikhmin::Ashikhmin(int _exp):
	Shader(),
	exp(_exp)
{}

// ---- Copy consructor ----
Ashikhmin::Ashikhmin(const Ashikhmin& ash):
	Shader(ash),
	exp(ash.exp){
}

// ---- Assignment operator ----
Ashikhmin& Ashikhmin::operator=(const Ashikhmin& rhs){
	c = rhs.c;
	exp = rhs.exp;
	return *this;
}

// ---- Destructor ----
Ashikhmin::~Ashikhmin(){
}

RGBColor Ashikhmin::shade(const World& w, const ShadeRec& sr){


	return RGBColor(45, 45, 45);
}

Ashikhmin* Ashikhmin::clone(){
	return new Ashikhmin(*this);
}