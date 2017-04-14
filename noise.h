#ifndef NOISE_H
#define NOISE_H
#include "shader.h"

#define 	K_TABLE_SIZE	(256)
#define 	K_TABLE_MASK 	(K_TABLE_SIZE - 1)
#define 	SEED_VALUE		(253)

class Noise: public Shader{
public:
	Noise();
	//Noise(const Noise& _noise);
	//Noise& operator=(const Noise& rhs);
	//~Noise();

	RGBColor shade(const World& w, const ShadeRec& sr);
	Shader* clone() const;

};





#endif
