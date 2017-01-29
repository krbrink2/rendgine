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
