#ifndef NOISE_H
#define NOISE_H
#include "shader.h"

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
