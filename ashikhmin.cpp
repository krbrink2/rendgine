#include "ashikhmin.h"
#include <cmath>
#include "world.h"
#include "shaderec.h"

// ---- Default constructor ----
Ashikhmin::Ashikhmin():
	Shader(),
	exp(100),
	nu(100),
	nv(100)
{}

// ---- Constructor ----
Ashikhmin::Ashikhmin(int _exp, int _nu, int _nv):
	Shader(),
	exp(_exp),
	nu(_nu),
	nv(_nv)
{}

// ---- Copy consructor ----
Ashikhmin::Ashikhmin(const Ashikhmin& ash):
	Shader(ash),
	exp(ash.exp),
	nu(ash.nu),
	nv(ash.nv)
{}

// ---- Assignment operator ----
Ashikhmin& Ashikhmin::operator=(const Ashikhmin& rhs){
	c = rhs.c;
	exp = rhs.exp;
	nu = rhs.nu;
	nv = rhs.nv;
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
		E.normalize();
		const Normal& N = sr.hitNormal;
		Vector3D H = (L + E)/2;

		if(N*L < 0)
			continue;

		RGBColor irradiance = worldPtr->lights[i]->getIrradiance(sr.hitPoint);

		// Diffuse
		RGBColor ashDiffuse = (irradiance * c)/255.0;
		ashDiffuse +=  (kdiff * (1 - kspec));
		ashDiffuse *= .3875076875;	// 28/(23*pi)
		ashDiffuse *= 1 - std::pow(1 - N*E/2, 5);
		ashDiffuse *= 1 - std::pow(1 - N*L/2, 5);
		accum += ashDiffuse;

		// Specular
		float ashSpecNorm	= std::sqrt((nu + 1)*(nv + 1))/(8*PI);
		float ashSpecExp	= exp;
		float ashSpecDenom	= H*L*max(N*L, N*E);
		float ashSpecFres	= kspec + (1 - kspec)*std::pow(1 - L*H, 5); //@RESUME
		RGBColor ashSpec = irradiance*kspec*ashSpecNorm*std::pow(max(N*H, 0), ashSpecExp)
			*ashSpecFres/ashSpecDenom;
		accum += ashSpec;
	}


	return accum;
}

Ashikhmin* Ashikhmin::clone(){
	return new Ashikhmin(*this);
}