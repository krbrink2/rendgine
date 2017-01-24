#include <iostream>
#include <vector>
#include "lodepng.h"
#include "object.h"
#include "plane.h"

#include "Constants.h"
#include "Normal.h"
#include "Point3D.h"
#include "Ray.h"
#include "Vector3D.h"
using namespace std;

// ---- Global variable declarations ----
double s;
int hres, vres;
vector<Object*> objects;

// ---- Function declarations ----
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned hres, unsigned vres);

// ---- Main funciton ----
int main(int argc, char* argv[]){

	// Initialize global variables
	hres = vres = 512;
	s = .1;

	// Add objects
	Normal n(-1, 1, 1);
	n.normalize();
	Object* newPlane = new Plane(Point3D(0, 0, -10), n);
	objects.push_back(newPlane); //new Plane(Point3D(0, 0, -10), Normal(-1, 1, 1)));

	//generate some image
	const char* pngName = "image.png";
	std::vector<unsigned char> image;
	image.resize(hres * vres * 4);

	// For each pixel...
	for(int y = 0; y < vres; y++)
	for(int x = 0; x < hres; x++)
	{

		// Set to default color
		image[4*hres*y + 4*x + 0] = 0;
		image[4*hres*y + 4*x + 1] = 0;
		image[4*hres*y + 4*x + 2] = 0; 
		image[4*hres*y + 4*x + 3] = 255;


		// Create ray
		double wx = s*(x - hres/2 + .5);
		double wy = s*(y - vres/2 + .5);
		Point3D o = Point3D(wx, wy, 0);
		Vector3D d = Vector3D(0, 0, -1);
		Ray ray = Ray(0, d);

		double tmin = kHugeValue;

		// For each object:
		for(size_t i = 0; i < objects.size(); i++){
			// Test for ray-object intersection
			if(objects[i]->hit(ray, tmin)){
				// If intersection, color this pixel
				cout << "!!!" << endl;
				image[4*hres*y + 4*x + 0] = objects[i]->color.r;
				image[4*hres*y + 4*x + 1] = objects[i]->color.g;
				image[4*hres*y + 4*x + 2] = objects[i]->color.b;
				image[4*hres*y + 4*x + 0] = 255;
			}

		}

  		/*image[4 * hres * y + 4 * x + 0] = 255 * !(x & y);
  		image[4 * hres * y + 4 * x + 1] = x ^ y;
  		image[4 * hres * y + 4 * x + 2] = x | y;
  		image[4 * hres * y + 4 * x + 3] = 255;*/


	}

	// Destroy objects
	for(size_t i = 0; i < objects.size(); i++){
		delete objects[i];
		objects[i] = NULL;
	}
	objects.clear();

 	encodeOneStep(pngName, image, hres, vres);


	return 0;
}

// ---- Function defintions
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned hres, unsigned vres)
{
	unsigned error = lodepng::encode(filename, image, hres, vres);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}