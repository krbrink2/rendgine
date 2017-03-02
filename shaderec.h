#ifndef SHADEREC_R
#define SHADEREC_R

#include "shader.h"
#include "utils.h"


class ShadeRec{
	public:
		bool hitObject;
		double t;
		Point3D hitPoint;
		Normal hitNormal;
		//RGBColor hitColor;
		Shader* hitShader;

		ShadeRec();									// Constructor
		//ShadeRec(const RGBColor& c);
};


#endif