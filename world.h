#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "controls.h"
#include "light.h"
#include "mesh.h"
#include "object.h"
#include "plane.h"
#include "shaderec.h"
#include "sphere.h"
#include "triangle.h"
#include "utils.h"
/*
#include "Point3D.h"
#include "Ray.h"
#include "RGBColor.h"*/

class World{
public:
	double s;
	double mjFineWidth;
	int hres, vres;
	RGBColor backgroundColor;
	std::vector<Object*> objects;
	std::vector<Light> lights;
	Point3D E;
	Point3D lookat;
	Vector3D up;
	double d;
	bool orthographic;

	Vector3D vx, vy, vz;			// Viewing coordinate system

	World(void);
	World(const World& w);
	World& operator=(const World& rhs);
	~World(void);

	void build(void);
	void addDefaultObjects(void);
	void addBunny(void);
	void clearObjects();
	void setViewCoords(void);
	void renderScene(void) const;
	RGBColor computePixelOrtho(const int x, const int y) const;
	RGBColor computePixelPerspec(const int x, const int y) const;
	void traceRay(const Ray& ray, ShadeRec& sr) const;
};

#endif