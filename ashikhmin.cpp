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
	RGBColor accum(0,0,0);

	// For each light...
	for(size_t i = 0; i < worldPtr->lights.size(); i++){
		Vector3D L = worldPtr->lights[i]->getDirection(sr.hitPoint);
		Vector3D E = worldPtr->E - sr.hitPoint;
		Vector3D H = L + E;
		const Normal& N = sr.hitNormal;
		E.normalize();
		H.normalize();

		RGBColor ashDiffuse = worldPtr->lights[i]->getIrradiance(sr.hitPoint);
		//ashDiffuse +=  (kdiff * (1 - kspec));

		accum += ashDiffuse;
	}


	return accum;
}

Ashikhmin* Ashikhmin::clone(){
	return new Ashikhmin(*this);
}