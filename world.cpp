#include "world.h"

// ---- Constructor ----
World::World(void){
	backgroundColor = RGBColor(0, 0, 0);
}

// ---- Copy constructor ----
World::World(const World& w):
	backgroundColor(w.backgroundColor)
{}

// ---- Assignment operator ----
World& World::operator=(const World& w){
	backgroundColor = w.backgroundColor;
	return *this;
}

// ---- Destuctor ----
World::~World(){}

void World::renderScene(void){
	//@TODO
}

ShadeRec World::traceRay(Ray& ray){
	ShadeRec sr(*this);

	// Let every object check against this ray,
	//	using sr to record information.
	for(size_t i = 0; i < objects.size(); i++){
		objects[i].hit(ray, sr);
	}
}
