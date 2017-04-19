#ifndef GLOSSY_H
#define GLOSSY_H
#include "shader.h"
#include "halton.hpp"

class Glossy: public Shader{
public:
	Glossy();

	RGBColor shade(const World& w, const ShadeRec& sr);
	Shader* clone() const;
	void setSamples(Vector3D* samples);
	void hemisphereize(const std::pair<double, double>* randPairs, Vector3D* samples);

	double exp;
};





#endif