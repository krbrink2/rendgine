#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "bvhnode.h"
#include "areaLight.h"
#include "ashikhmin.h"
#include "checkerboard.h"
#include "controls.h"
#include "dirlight.h"
#include "light.h"
#include "mesh.h"
#include "mirror.h"
#include "object.h"
#include "plane.h"
#include "pointlight.h"
#include "pureColor.h"
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
	std::vector<Light*> lights;
	Point3D E;
	Point3D lookat;
	Vector3D up;
	double d;
	bool orthographic;

	Vector3D vx, vy, vz;			// Viewing coordinate system

	std::vector<BVHNode> bvh;

	World(void);
	World(const World& w);
	World& operator=(const World& rhs);
	~World(void);

	void build(void);
	void addDefaultObjects(void);
	void addBunny(const Matrix& matrix, Shader& _sdr);
	void addManyBunnies(int numBunnies);
	void addManySpheres(int num);
	void clearObjects(void);
	void clearLights(void);
	void setViewCoords(void);
	void renderScene(void) const;
	void renderAnimation(void);
	RGBColor computePixelOrtho(const int x, const int y) const;
	RGBColor computePixelPerspec(const int x, const int y) const;
	void traceRay(const Ray& ray, ShadeRec& sr) const;
};

#endif