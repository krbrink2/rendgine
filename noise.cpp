#include "noise.h"
#include <cmath>
#include "world.h"
#include "shaderec.h"
#include <cmath>
//using namespace std;


// ---- Default constructor ----
Noise::Noise():
	Shader()
{
	setup();
}

// Function name:		shade
// Function purpose:	BRDf
// Parameters:			World for reference, sr for data
// Return value:		Color
// Any other output:	none
RGBColor Noise::shade(const World& w, const ShadeRec& sr){
	const Point3D p = sr.hitPoint * NOISE_FACTOR;

	// Get color.

	int x0, x1, y0, y1, z0, z1;
	x0 = floor(p.x);
	x1 = ceil(p.x);
	y0 = floor(p.y);
	y1 = ceil(p.y);
	z0 = floor(p.z);
	z1 = ceil(p.z);
	// The best variable names, full stop.
	double aaa, aab, aba, abb, baa, bab, bba, bbb;
	aaa = valueTable[INDEX(x0, y0, z0)];
	aab = valueTable[INDEX(x0, y0, z1)];
	aba = valueTable[INDEX(x0, y1, z0)];
	abb = valueTable[INDEX(x0, y1, z1)];
	baa = valueTable[INDEX(x1, y0, z0)];
	bab = valueTable[INDEX(x1, y0, z1)];
	bba = valueTable[INDEX(x1, y1, z0)];
	bbb = valueTable[INDEX(x1, y1, z1)];

	// Interpolate out x dimension.
	double fx, fy, fz;
	fx = p.x - floor(p.x);
	fy = p.y - floor(p.y);
	fz = p.z - floor(p.z);

	double aa, ab, ba, bb;
	aa = lerp(aaa, baa, fx);
	ab = lerp(aba, bba, fx);
	ba = lerp(aab, bab, fx);
	bb = lerp(abb, bbb, fx);

	// Interpolate out y dimension.
	double a, b;
	a = lerp(aa, ab, fy);
	b = lerp(ba, bb, fy);

	// Interpolate out z dimension.
	double val;
	val = lerp(a, b, fz);


	// Now, do lambertian shading.


	RGBColor accum(0, 0, 0);

	// For each light...
	for(size_t i = 0; i < worldPtr->lights.size(); i++){
		vector<std::pair<Vector3D, RGBColor> > samples;
		worldPtr->lights[i]->getSamples(samples, sr.hitPoint);
		// For each sample...
		for(auto sample : samples){
			// May want to put this in another function.
			Vector3D& L = sample.first;
			double NDotL = clamp((sr.hitNormal * L), 0, 1);
			accum += (val * c * NDotL * sample.second)/256;
		}
	}

	// Clamp color
	accum.r = clamp(accum.r, 0, 255);
	accum.g = clamp(accum.g, 0, 255);
	accum.b = clamp(accum.b, 0, 255);

	return accum;

}

// Function name:		clone
// Function purpose:	Returns pointer to clone of this Noise.
// Parameters:			none
// Return value:		Pointer to new shader.
// Any other output:	none
Shader* Noise::clone() const{
	return new Noise(*this);
}


// Function name:		setup
// Function purpose:	Initilizes valueTable full of pseudorandom values.
// Parameters:			none
// Return value:		none
// Any other output:	Writes to valueTable array.
void Noise::setup(void){
	set_rand_seed(SEED_VALUE);
	for(int i = 0; i < K_TABLE_SIZE; i++){
		//valueTable[i] = 1.0 - 2.0*rand_float();	// Why range [-1.0, 1.0]?
		valueTable[i] = rand_float(0, 1);
	}
}

// Function name:		lerp
// Function purpose:	Linear interpretation
// Parameters:			First value a
// 						Second value b
//						Interpolation amount t
// Return value:		Interpolated value
// Any other output:	none
double Noise::lerp(double a, double b, double t) const{
  return ((1 - t)*a) + (t*b);
}


