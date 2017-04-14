#ifndef NOISE_H
#define NOISE_H
#include "shader.h"

#define 		K_TABLE_SIZE 	(256)
#define 		K_TABLE_MASK	(K_TABLE_SIZE - 1)
#define 		SEED_VALUE		(253)	

class Noise: public Shader{
public:
	Noise();
	Noise(int _nu, int _nv);
	Noise(const Noise& ash);
	Noise& operator=(const Noise& rhs);
	~Noise();

	RGBColor shade(const World& w, const ShadeRec& sr);
	Shader* clone() const;

	int nu, nv;
	double kdiff, kspec;
private:

};









#endif