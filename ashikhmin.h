#ifndef ASHIKHMIN_H
#define ASHIKHMIN_H
#include "shader.h"

class Ashikhmin: public Shader{
public:
	Ashikhmin();
	Ashikhmin(int _exp, int _nu, int _nv);
	Ashikhmin(const Ashikhmin& ash);
	Ashikhmin& operator=(const Ashikhmin& rhs);
	~Ashikhmin();

	RGBColor shade(const World& w, const ShadeRec& sr);
	Ashikhmin* clone();

	int exp, nu, nv;
	double kdiff, kspec;
private:

};









#endif