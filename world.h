#ifndef WORLD_H
#define WORLD_H

#include "RGBColor.h"

class World{
public:
	RGBColor backgroundColor;

	World(void);
	World(const World& w);
	World& operator=(const World& rhs);
	~World(void);

	void build(void);
	void render_scene(void) const;
};

#endif