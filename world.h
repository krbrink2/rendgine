#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "light.h"
#include "object.h"
#include "plane.h"
#include "shaderec.h"
#include "sphere.h"
#include "triangle.h"
#include "Point3D.h"
#include "Ray.h"
#include "RGBColor.h"

#define NUM_SAMPLES 		16
#define SQRT_NUM_SAMPLES	4

class World{
public:
	double s;
	double mjCoarseWidth;
	double mjFineWidth;
	int hres, vres;
	RGBColor backgroundColor;
	std::vector<Object*> objects;
	std::vector<Light> lights;
	Point3D E;
	bool orthographic;

	World(void);
	World(const World& w);
	World& operator=(const World& rhs);
	~World(void);

	void build(void);
	void renderScene(void) const;
	RGBColor computePixelOrtho(const int x, const int y) const;
	RGBColor computePixelPerspec(const int x, const int y) const;
	void traceRay(const Ray& ray, ShadeRec& sr) const;
};

#endif