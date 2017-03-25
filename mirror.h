#ifndef MIRROR_H
#define MIRROR_H
#include "controls.h"
#include "shaderec.h"
#include "shader.h"
#include "utils.h"

class Mirror: public Shader{
public:
	Mirror();

	RGBColor shade(const World& w, const ShadeRec& sr);
	Mirror* clone();

};


#endif