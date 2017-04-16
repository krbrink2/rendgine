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

	int x0, x1, y0, y1, z0, z1;
	x0 = floor(p.x);
	x1 = ceil(p.x);
	y0 = floor(p.y);
	y1 = ceil(p.y);
	z0 = floor(p.z);
	z1 = ceil(p.z);
	// The best variable names, full stop.
	// double aaa, aab, aba, abb, baa, bab, bba, bbb;
	// aaa = valueTable[INDEX(x0, y0, z0)];
	// aab = valueTable[INDEX(x0, y0, z1)];
	// aba = valueTable[INDEX(x0, y1, z0)];
	// abb = valueTable[INDEX(x0, y1, z1)];
	// baa = valueTable[INDEX(x1, y0, z0)];
	// bab = valueTable[INDEX(x1, y0, z1)];
	// bba = valueTable[INDEX(x1, y1, z0)];
	// bbb = valueTable[INDEX(x1, y1, z1)];

	// // Interpolate out x dimension.
	// double aa, ab, ba, bb;
	// aa = lerp(aaa, baa, fmod(p.x, 1.0));
	// ab = lerp(aab, bab, fmod(p.x, 1.0));
	// ba = lerp(aba, bba, fmod(p.x, 1.0));
	// bb = lerp(abb, bbb, fmod(p.x, 1.0));

	// // Interpolate out y dimension.
	// double a, b;
	// a = lerp(aa, ba, fmod(p.y, 1.0));
	// b = lerp(ab, bb, fmod(p.y, 1.0));

	// // Interpolate out z dimension.
	// double val;
	// val = lerp(a, b, fmod(p.z, 1.0));

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


	return val * c;
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
  return ((1 - t)*a) + (t*b);
}




