#ifndef SHADER_H
#define SHADER_H
#include "Normal.h"
#include "RGBColor.h"

// ---- Forward decalrations ----

class World;
class ShadeRec;

// ---- Globals ----
extern World* worldPtr;

// ---- Class declaration ----
class Shader{
public:
	Shader();
	Shader(const Shader& sdr);
	Shader& operator=(const Shader& rhs);
	virtual ~Shader();

	virtual RGBColor shade(const World& w, const ShadeRec& sr);
	virtual RGBColor operator()(const World& w, const ShadeRec& sr);
	virtual Shader* clone() const;

	RGBColor c;

protected:
private:
};

#endif