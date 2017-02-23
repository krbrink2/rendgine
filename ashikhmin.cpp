#include "ashikhmin.h"
#include "world.h"
#include "shadrec.h"

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

RGBColor Ashikhmin::shade(const World& w, const ShadeRec& sr){


	return RGBColor(45, 45, 45);
}