#ifndef TRANSPARENT_H
#define TRANSPARENT_H
#include "controls.h"
#include "shaderec.h"
#include "shader.h"
#include "utils.h"

class Transparent: public Shader{
public:
	Transparent();

	RGBColor shade(const World& w, const ShadeRec& sr);
	Shader* clone() const;

	Shader* second; // Secondary shader effect
	double mix; 	// High value is in favor of second shader above.
};


#endif