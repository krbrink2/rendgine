#ifndef SHADER_H
#define SHADER_H
//#include "object.h"
//#include "shaderec.h"
// World forward-declared
//#include "Ray.h"
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