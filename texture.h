#ifndef TEXTURE_H
#define TEXTURE_H
#include "shader.h"
#include <vector>


class Texture: public Shader{
public:
	Texture();
    Texture(const char* filename);
	RGBColor shade(const World& w, const ShadeRec& sr);
	Shader* clone() const;
	void loadImage(const char* filename);

    std::vector<unsigned char> image;
    unsigned width, height;


};



#endif
