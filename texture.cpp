#include "texture.h"
#include <cmath>
#include "world.h"
#include "shaderec.h"

extern std::pair<unsigned, unsigned> decodeOneStep(const char* filename, std::vector<unsigned char>& image);

// ---- Default constructor ----
Texture::Texture():
	Shader()
{
	width = height = 0;
}

// ---- Constructor ----
Texture::Texture(const char* filename):
	Shader()
{
	loadImage(filename);
}

// Function name:		shade
// Function purpose:	BRDf
// Parameters:			World for reference, sr for data
// Return value:		Color
// Any other output:	none
RGBColor Texture::shade(const World& w, const ShadeRec& sr){
	
	// Get textel

	RGBColor textel;
	textel = RGBColor(150, 100, 15);

	// For now, just do uv's by taking normal xy's.
	int u, v;
	u = ((sr.hitNormal.x/2.0) + .5)*width;
	v = (-(sr.hitNormal.y/2.0) + .5)*height;
	int index = 4*(v*width + u);
	textel.r = image[index];
	textel.g = image[index + 1];
	textel.b = image[index + 2];

	// Now do lamberian shading

	RGBColor accum(0, 0, 0);

	// For each light...
	for(size_t i = 0; i < worldPtr->lights.size(); i++){
		vector<std::pair<Vector3D, RGBColor> > samples;
		worldPtr->lights[i]->getSamples(samples, sr.hitPoint);
		// For each sample...
		for(auto sample : samples){
			// May want to put this in another function.
			Vector3D& L = sample.first;
			double NDotL = clamp((sr.hitNormal * L), 0, 1);
			accum += (textel * NDotL * sample.second)/256;
		}
	}

	// Clamp color
	accum.r = clamp(accum.r, 0, 255);
	accum.g = clamp(accum.g, 0, 255);
	accum.b = clamp(accum.b, 0, 255);

	return accum;

}

// Function name:		clone
// Function purpose:	Returns pointer to clone of this Texture.
// Parameters:			none
// Return value:		Pointer to new shader.
// Any other output:	none
Shader* Texture::clone() const{
	return new Texture(*this);
}

// Function name:		loadImage
// Function purpose:	Loads filename into image vector.
// Parameters:			filename: string name of texture file.
// Return value:		none
// Any other output:	Writes to image member vector.
void Texture::loadImage(const char* filename){
	std::pair<unsigned, unsigned> wh = decodeOneStep(filename, image);
	width = wh.first;
	height = wh.second;
}
