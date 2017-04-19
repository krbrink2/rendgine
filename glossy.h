#ifndef GLOSSY_H
#define GLOSSY_H
#include "shader.h"

class Glossy: public Shader{
public:
	Glossy();

	RGBColor shade(const World& w, const ShadeRec& sr);
	Shader* clone() const;

	double exp;
};





#endif