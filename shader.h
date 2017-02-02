#ifndef SHADER_H
#define SHADER_H
#include "world.h"
#include "RGBColor.h"

class Shader{
public:
	Shader();
	Shader(const Shader& sdr);
	Shader& operator=(const Shader& rhs);
	~Shader();

	virtual RGBColor shade(World& w) = 0;


protected:
private:
};

#endif