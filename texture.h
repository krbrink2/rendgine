#ifndef TEXTURE_H
#define TEXTURE_H
#include "shader.h"


class Texture: public Shader{
public:
	Texture();
	RGBColor shade(const World& w, const ShadeRec& sr);
	Shader* clone() const;
	void setup(void);
	double lerp(double a, double b, double t) const;


};



#endif
