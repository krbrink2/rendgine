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

// ---- Copy consructor ----
// Noise::Noise(const Ashikhmin& ash):
// 	Shader(ash),
// 	nu(ash.nu),
// 	nv(ash.nv),
// 	kdiff(ash.kdiff),
// 	kspec(ash.kspec)
// 	{}

// ---- Assignment operator ----
// Noise& Noise::operator=(const Noise& rhs){
// 	c = rhs.c;
// 	nu = rhs.nu;
// 	nv = rhs.nv;
// 	kdiff = rhs.kdiff;
// 	kspec = rhs.kdiff;
// 	return *this;
// }

// ---- Destructor ----
// Noise::~Noise(){
// }

// Function name:		shade
// Function purpose:	BRDf
// Parameters:			World for reference, sr for data
// Return value:		Color
// Any other output:	none
RGBColor Noise::shade(const World& w, const ShadeRec& sr){
	const Point3D& p = sr.hitPoint;

	double x0, x1, y0, y1, z0, z1;
	// The best variable names, full stop.
	double aaa, aab, aba, abb, baa, bab, bba, bbb;
	aaa = valueTable[INDEX((int)floor(p.x), (int)floor(p.y), (int)floor(p.z))];
	aab = valueTable[INDEX((int)floor(p.x), (int)floor(p.y), (int)ceil(p.z))];
	aba = valueTable[INDEX((int)floor(p.x), (int)ceil(p.y), (int)floor(p.z))];
	abb = valueTable[INDEX((int)floor(p.x), (int)ceil(p.y), (int)ceil(p.z))];
	baa = valueTable[INDEX((int)ceil(p.x), (int)floor(p.y), (int)floor(p.z))];
	bab = valueTable[INDEX((int)ceil(p.x), (int)floor(p.y), (int)ceil(p.z))];
	bba = valueTable[INDEX((int)ceil(p.x), (int)ceil(p.y), (int)floor(p.z))];
	bbb = valueTable[INDEX((int)ceil(p.x), (int)ceil(p.y), (int)ceil(p.z))];

	// Interpolate out x dimension.
	double aa, ab, ba, bb;
	aa = lerp(aaa, baa, fmod(p.x, 1.0));
	ab = lerp(aab, bab, fmod(p.x, 1.0));
	ba = lerp(aba, bba, fmod(p.x, 1.0));
	bb = lerp(abb, bbb, fmod(p.x, 1.0));

	// Interpolate out y dimension.
	double a, b;
	a = lerp(aa, ba, fmod(p.y, 1.0));
	b = lerp(ab, bb, fmod(p.z, 1.0));

	// Interpolate out z dimension.
	double val;
	val = lerp(a, b, fmod(p.z, 1.0));

	return c * val;
}

// Function name:		clone
// Function purpose:	Returns pointer to clone of this Noise.
// Parameters:			none
// Return value:		Pointer to new shader.
// Any other output:	none
Shader* Noise::clone() const{
	return new Noise(*this);
}

void Noise::setup(void){
	set_rand_seed(SEED_VALUE);
	for(int i = 0; i < K_TABLE_SIZE; i++){
		//valueTable[i] = 1.0 - 2.0*rand_float();	// Why range [-1.0, 1.0]?
		valueTable[i] = rand_float(0, 1);
	}
}

double Noise::lerp(double a, double b, double t) const{
  return (1 - t)*a + t*b;
}




