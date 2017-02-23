#ifndef ASHIKHMIN_H
#define ASHIKHMIN_H
#include "shader.h"

class Ashikhmin: public Shader{
public:
	Ashikhmin();
	Ashikhmin(int _exp);
	Ashikhmin(const Ashikhmin& ash);
	Ashikhmin& operator=(const Ashikhmin& rhs);
	~Ashikhmin();

	RGBColor shade(const World& w, const ShadeRec& sr);
	Ashikhmin* clone();

private:
	int exp;

};









#endif