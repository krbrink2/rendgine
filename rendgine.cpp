#include <iostream>
#include <vector>
#include "lodepng.h"
#include "object.h"

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);

int main(int argc, char* argv[]){

	const char* pngName = "image.png";

	//generate some image
	unsigned width = 512, height = 512;
	std::vector<unsigned char> image;
	image.resize(width * height * 4);
	for(unsigned y = 0; y < height; y++)
	for(unsigned x = 0; x < width; x++)
	{
  		image[4 * width * y + 4 * x + 0] = 255 * !(x & y);
  		image[4 * width * y + 4 * x + 1] = x ^ y;
  		image[4 * width * y + 4 * x + 2] = x | y;
  		image[4 * width * y + 4 * x + 3] = 255;
	}
 	encodeOneStep(pngName, image, width, height);


	return 0;
}

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	unsigned error = lodepng::encode(filename, image, width, height);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}