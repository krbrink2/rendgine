#include <iostream>
#include <vector>
#include "lodepng.h"
#include "object.h"

// ---- Global variable declarations ----
double s;
int hres, vres;

// ---- Function declarations ----
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned hres, unsigned vres);

// ---- Main funciton ----
int main(int argc, char* argv[]){

	const char* pngName = "image.png";

	//generate some image
	hres = vres = 512;
	std::vector<unsigned char> image;
	image.resize(hres * vres * 4);
	for(int y = 0; y < vres; y++)
	for(int x = 0; x < hres; x++)
	{


		//@RESUME

  		image[4 * hres * y + 4 * x + 0] = 255 * !(x & y);
  		image[4 * hres * y + 4 * x + 1] = x ^ y;
  		image[4 * hres * y + 4 * x + 2] = x | y;
  		image[4 * hres * y + 4 * x + 3] = 255;


	}
 	encodeOneStep(pngName, image, hres, vres);


	return 0;
}

// ---- Function defintions
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned hres, unsigned vres)
{
	unsigned error = lodepng::encode(filename, image, hres, vres);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}