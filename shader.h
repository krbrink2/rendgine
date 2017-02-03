#ifndef SHADER_H
#define SHADER_H
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

	virtual RGBColor shade(const World& w);


protected:
private:
};

#endif