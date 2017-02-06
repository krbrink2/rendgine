#include <iostream>
#include <vector>
#include "lodepng.h"
#include "object.h"
#include "plane.h"
#include "shaderec.h"
#include "sphere.h"
#include "world.h"

#include "Constants.h"
#include "Normal.h"
#include "Point3D.h"
#include "Ray.h"
#include "Vector3D.h"
using namespace std;

// ---- Global variable declarations ----
/*double s;
int hres, vres;
vector<Object*> objects;*/
World* worldPtr;

// ---- Function declarations ----
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned hres, unsigned vres);

int foo(void){
	return 0;
}

// ---- Main funciton ----
int main(int argc, char* argv[]){

	worldPtr = new World();
	worldPtr->build();
	worldPtr->renderScene();
	return 0;


}

// ---- Function defintions ----
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned hres, unsigned vres)
{
	unsigned error = lodepng::encode(filename, image, hres, vres);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}