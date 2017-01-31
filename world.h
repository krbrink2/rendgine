#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "object.h"
#include "plane.h"
#include "shaderec.h"
#include "sphere.h"
#include "Ray.h"
#include "RGBColor.h"

class World{
public:
	double s;
	int hres, vres;
	RGBColor backgroundColor;
	std::vector<Object*> objects;

	World(void);
	World(const World& w);
	World& operator=(const World& rhs);
	~World(void);

	void build(void);
	void renderScene(void) const;
	RGBColor computePixel(const int x, const int y) const;
	void traceRay(const Ray& ray, ShadeRec& sr) const;
};

#endif