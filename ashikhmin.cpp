#include "ashikhmin.h"
#include <cmath>
#include "world.h"
#include "shaderec.h"

// ---- Default constructor ----
Ashikhmin::Ashikhmin():
	Shader(),
	nu(100),
	nv(100)
{}

// ---- Constructor ----
Ashikhmin::Ashikhmin(int _nu, int _nv):
	Shader(),
	nu(_nu),
	nv(_nv)
{}

// ---- Copy consructor ----
Ashikhmin::Ashikhmin(const Ashikhmin& ash):
	Shader(ash),
	nu(ash.nu),
	nv(ash.nv)
{}

// ---- Assignment operator ----
Ashikhmin& Ashikhmin::operator=(const Ashikhmin& rhs){
	c = rhs.c;
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
		Vector3D H = L + E;
		H.normalize();

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
		//float ashSpecNorm	= std::sqrt((nu + 1)*(nv + 1))/(8*PI);
		float ashSpecNorm	= 1;//(nu+1)/(8*PI);
		float ashSpecExp	= nu;
		float ashSpecDenom	= 1;//H*L*max(N*L, N*E);
		float ashSpecFres	= 1;//kspec + (1 - kspec)*std::pow(1 - L*H, 5);
		RGBColor ashSpec = irradiance*ashSpecNorm*std::pow(max(N*H, 0), ashSpecExp)
			*ashSpecFres/ashSpecDenom;
		accum += ashSpec;
	}

	// Clamp color
	accum.r = clamp(accum.r, 0, 255);
	accum.g = clamp(accum.g, 0, 255);
	accum.b = clamp(accum.b, 0, 255);
	return accum;
}

Ashikhmin* Ashikhmin::clone(){
	return new Ashikhmin(*this);
}	