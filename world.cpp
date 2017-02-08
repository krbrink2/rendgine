#include "world.h"
#include <math.h>
#include <assert.h>
#include <iostream>

extern void encodeOneStep(const char* filename, std::vector<unsigned char>& image, \
 unsigned hres, unsigned vres);

// ---- Constructor ----
World::World(void){
	backgroundColor = RGBColor(0, 0, 0);
}

// ---- Copy constructor ----
World::World(const World& w):
	s(w.s),
	hres(w.hres),
	vres(w.vres),
	backgroundColor(w.backgroundColor)
{
	for(size_t i = 0; i < w.objects.size(); i++){
		objects.push_back(w.objects[i]->clone());
	}
}

// ---- Assignment operator ----
World& World::operator=(const World& w){
	backgroundColor = w.backgroundColor;
	s = w.s;
	vres = w.vres;
	hres = w.hres;
	for(size_t i = 0; i < w.objects.size(); i++){
		objects.push_back(objects[i]->clone());
	}
	return *this;
}

// ---- Destuctor ----
World::~World(){
	for(size_t i = 0; i < objects.size(); i++){
		delete objects[i];
		objects[i] = NULL;
	}
	objects.clear();
}

void World::build(void){
	hres = vres = 512;
	s = .1;
	mjCoarseWidth = (int)(s/SQRT_NUM_SAMPLES);
	mjFineWidth = (int)(s/NUM_SAMPLES);

	backgroundColor = RGBColor(0, 0, 0);
	E = Point3D(0, 0, 0);
	orthographic = true;

	// Add objects
	// Plane
	Normal n(-1, 1, 1);
	n.normalize();
	objects.push_back(new Plane(Point3D(0, 0, -100), n));
	objects[0]->sdr.c = RGBColor(255, 0, 0);
	// Sphere 0
	objects.push_back(new Sphere(5, Point3D(0, 0, -100)));
	objects[1]->sdr.c = RGBColor(0, 255, 0);	
	// Spehre 1
	objects.push_back(new Sphere(6, Point3D(-10, 12, -100)));
	objects[2]->sdr.c = RGBColor(0, 0, 255);	
	// Triangle
	objects.push_back(new Triangle(
		Point3D(0, 0, -100),
		Point3D(-10, 12, -100),
		Point3D(-10, -12, -100)));
	objects[3]->sdr.c = RGBColor(0, 255, 255);

    // Add lights
    Light l;
    Vector3D dir(1, 0, -1);
	dir.normalize();
	l.dir = dir;
	lights.push_back(l); 
}

void World::renderScene(void) const{
	//generate some image
	const char* pngName = "image.png";
	std::vector<unsigned char> image;
	image.resize(hres * vres * 4);

	// For each pixel...
	for(int y = 0; y < vres; y++)
	for(int x = 0; x < hres; x++){
		RGBColor c;
		if(orthographic)
			c = computePixelOrtho(x, y);
		else
			// Change for perspective
			c = computePixelOrtho(x, y);
		image[4*hres*y + 4*x + 0] = c.r;
		image[4*hres*y + 4*x + 1] = c.g;
		image[4*hres*y + 4*x + 2] = c.b;
		image[4*hres*y + 4*x + 3] = 255;
	}
	encodeOneStep(pngName, image, hres, vres);
}

RGBColor World::computePixelOrtho(const int x, const int y) const{
	bool fineBoxes[NUM_SAMPLES][NUM_SAMPLES] = {0};	// True if occupied
	RGBColor accum(0, 0, 0);

	// For each sample...
	for(size_t coarsei = 0; coarsei < SQRT_NUM_SAMPLES; coarsei++){
		for(size_t coarsej = 0; coarsej < SQRT_NUM_SAMPLES; coarsej++){

			// The flow control here is super wonky.
			// 	May want to fix it.
			
			// Choose an arbitrary fineBox - make sure no conflicts.
			// 	Randomly choose a fineBoxIndex
			int finei = rand_int(0, SQRT_NUM_SAMPLES);
			int finej = rand_int(0, SQRT_NUM_SAMPLES);
			int indexi, indexj;
			bool lookForFineBox = true;
			while(lookForFineBox){
				indexi = coarsei*SQRT_NUM_SAMPLES + finei;
				indexj = coarsej*SQRT_NUM_SAMPLES + finej;
				lookForFineBox = false; // Innocent until proven guilty
				// Check if its a good index
				for(size_t a = 0; a < NUM_SAMPLES; a++){
					if( fineBoxes[a][indexj] || fineBoxes[indexi][a] ){
						// Its taken. Try next one.
						lookForFineBox = true;	// Proven guilty.
						break;
					}
				}

				if(!lookForFineBox)
					// Innocent. Not proven guilty.
					break;


				// Guilty, so try the next one.
				finej++;
				finej %= SQRT_NUM_SAMPLES;
				if(finej == 0){
					finei++;
					finei %= SQRT_NUM_SAMPLES;
				}
				// Loop back to top
			}

			// Mark as used
			fineBoxes[indexi][indexj] = true;


			// Create ray
			// Generate orthographic origin
			double wx = s*(x - hres/2) + \
				mjCoarseWidth*(coarsej - SQRT_NUM_SAMPLES/2) + \
				mjFineWidth*(finej - SQRT_NUM_SAMPLES/2 + .5);
			double wy = -( s*(y - vres/2 + .5) + \
				mjCoarseWidth*(coarsei - SQRT_NUM_SAMPLES/2) + \
				mjFineWidth*(finei - SQRT_NUM_SAMPLES/2 + .5) );
			Point3D o = Point3D(wx, wy, 0);
			// Generate direction
			Vector3D d = Vector3D(0, 0, -1);
			// Create ray
			Ray ray(o, d);
			// Trace ray
			ShadeRec sr(backgroundColor);
			traceRay(ray, sr);
			if(sr.hitObject){
				accum += sr.hitShader->shade(*this, sr.hitNormal);
			} else{
				accum += backgroundColor;
			}
		}
	}

	accum /= NUM_SAMPLES;
	return accum;
}

void World::traceRay(const Ray& ray, ShadeRec& sr) const{

	// Let every object check against this ray,
	//	using sr to record information.
	for(size_t i = 0; i < objects.size(); i++){
		objects[i]->hit(ray, sr);
	}
}

Point3D World::getOrigin(int x, int y) const{
	return Point3D();	//@TODO
}




