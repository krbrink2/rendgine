#ifndef SHADEREC_R
#define SHADEREC_R

#include "shader.h"
#include "utils.h"


class ShadeRec{
	public:
		ShadeRec();

		bool hitObject;
		double t;
		Point3D hitPoint;
		Normal hitNormal;
		Ray ray;
		int numBounces;
		Shader* hitShader;
};


#endif