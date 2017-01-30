#ifndef WORLD_H
#define WORLD_H

#include "shaderec.h"
#include "object.h"
#include "RGBColor.h"

class World{
public:
	RGBColor backgroundColor;
	double s;
	int hres, vres;
	vector<Object*> objects;

	World(void);
	World(const World& w);
	World& operator=(const World& rhs);
	~World(void);

	void build(void);
	void renderScene(void) const;
	ShadeRec traceRay(Ray& ray);
};

#endif