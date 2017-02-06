#ifndef SHADER_H
#define SHADER_H
#include "Normal.h"
#include "RGBColor.h"

// ---- Forward decalrations ----

class World;

// ---- Class declaration ----
class Shader{
public:
	Shader();
	Shader(const Shader& sdr);
	Shader& operator=(const Shader& rhs);
	~Shader();

	virtual RGBColor shade(const World& w, const Normal& N);
	virtual RGBColor operator()(const World& w, const Normal& N);

	RGBColor c;

protected:
private:
};

#endif