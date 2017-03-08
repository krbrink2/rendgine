#include "world.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

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
	clearObjects();
	clearLights();
	bvh.clear();
}

// Function name:		build
// Function purpose:	Fill scene with objects, set up rendering params
// Parameters:			None
// Return value:		None
// Any other output:	None
void World::build(void){
	hres = HRES;
	vres = VRES;
	s = S;
	mjFineWidth = (double) s/NUM_SAMPLES;

	backgroundColor = RGBColor(0, 0, 0);
	E = EYE;
	lookat = LOOKAT;
	Vector3D upVect = UP;
	upVect.normalize();
	up = upVect;
	d = D;
	orthographic = ORTHO;

	// Add objects
	setViewCoords();
	//addDefaultObjects();
	//addBunny();
	addManySpheres(BENCHMARK_NUM_SPHERES);

	//@luces
	lights.push_back(new PointLight(Point3D(-.2, .4, .3)));
	lights.back()->color = RGBColor(255, 255, 255);
	//lights.push_back(new DirLight(Vector3D(-.1, -.1, 1)));
	//lights.back()->color = RGBColor(40, 30, 30);
	// lights.push_back(new PointLight(Point3D(15, -10, 10)));
	// lights.back()->color = RGBColor(4, 4, 6);

	if(USE_BVH){
		// Build BVH
		bvh.push_back(BVHNode());
		for(size_t i = 0; i < objects.size(); i++){
			// Have this object add its primitives to the bvh root
			objects[i]->addPrimitives(bvh.back().primitives);
		}
		std::cout << "> Building bounding volume hierarchy..." << std::endl;
		buildBVH(0);
		std::cout << "> Bounding volume hierarchy successfully built." << std::endl;
	}
	
}

// Function name:		clearObjects
// Function purpose:	Deletes all Objects
// Parameters:			none
// Return value:		none
// Any other output:	none
void World::clearObjects(void){
	for(size_t i = 0; i < objects.size(); i++){
		delete objects[i];
		objects[i] = NULL;
	}
	objects.clear();
}

// Function name:		clearLights
// Function purpose:	Deletes all Lights.
// Parameters:			none
// Return value:		none
// Any other output:	none
void World::clearLights(void){
	for(size_t i = 0; i < lights.size(); i++){
		delete lights[i];
		lights[i] = NULL;
	}
	lights.clear();
}

// Function name:		addDefaultObjects
// Function purpose:	Puts some triangles and spheres into scene
// Parameters:			None
// Return value:		None
// Any other output:	None
void World::addDefaultObjects(void){
	// Plane
	Normal n(-1, 1, 5.2);
	n.normalize();
	objects.push_back(new Plane(Point3D(0, 0, -10), n));
	objects.back()->sdr->c = RGBColor(255, 0, 0);

	// Sphere 0
	objects.push_back(new Sphere(5, Point3D(0, 0, 0)));
	Ashikhmin ash;
	ash.kspec = ash.kdiff = .5;
	ash.c = RGBColor(255, 80, 20);
	objects.back()->setShader(ash);

	// Sphere 1
	objects.push_back(new Sphere(6, Point3D(-10, 12, -10)));
	objects.back()->sdr->c = RGBColor(0, 0, 255);	

	// Triangle0
	objects.push_back(new Triangle(
		Point3D(0, 0, -10),
		Point3D(-10, 12, -10),
		Point3D(-10, -12, -10)));
	objects.back()->sdr->c = RGBColor(0, 255, 255);
	// Triangle1
	objects.push_back(new Triangle(
		Point3D(4, 4, -10),
		Point3D(15, 10, -10),
		Point3D(0, 15, -10)));
	objects.back()->sdr->c = RGBColor(255, 0, 255);
}

// Function name:		addBunny
// Function purpose:	Adds bunny.obj to objects vector.
// Parameters:			none
// Return value:		none
// Any other output:	Reports if load failed.
void World::addBunny(void){
	//clearObjects();
	const char bunny[128] = "bunny.obj";
	Mesh* bunnyPtr = new Mesh(bunny, Point3D(0, 0, 0));
	Ashikhmin ash;
	ash.c = RGBColor(226, 114, 91);
	bunnyPtr->setShader(ash);
	//bunnyPtr->sdr = ash.clone();	//@TODO get mesh.setShader to stop chopping
	if(!bunnyPtr->loaded){
		cout << "Not loaded!!!" << endl;
	}
	else
		objects.push_back(bunnyPtr);
}

void World::addManySpheres(int num){
	for(int i = 0; i < num; i++){
		objects.push_back(new Sphere(.02, Point3D(rand_float(), rand_float(), rand_float())));
		Ashikhmin ash;
		ash.c = RGBColor(rand_int(0, 256), rand_int(0, 256),rand_int(0, 256));
		objects.back()->sdr = ash.clone();

	}
}


// Function name:		setViewCoords
// Function purpose:	Sets camera's orthonormal basis
// Parameters:			None
// Return value:		None
// Any other output:	None
void World::setViewCoords(void){
	vz = E - lookat;
	vz.normalize();

	vx = up ^ vz;
	vx.normalize();

	vy = vx ^ vz;
}

// Function name:		renderScene
// Function purpose:	Render scene to file "image.png"
// Parameters:			None
// Return value:		None
// Any other output:	Writes image file to disk
void World::renderScene(void) const{
	std::cout << "> Beginning render..." << std::endl;
	//generate some image
	const char* pngName = "image.png";
	std::vector<unsigned char> image;
	image.resize(hres * vres * 4);

	// For each pixel...
	for(int y = 0; y < vres; y++){
		for(int x = 0; x < hres; x++){
			RGBColor c;
			if(orthographic)
				c = computePixelOrtho(x, y);
			else
				// Change for perspective
				c = computePixelPerspec(x, y);
			image[4*hres*y + 4*x + 0] = c.r;
			image[4*hres*y + 4*x + 1] = c.g;
			image[4*hres*y + 4*x + 2] = c.b;
			image[4*hres*y + 4*x + 3] = 255;
		}
		// Report status
		if(y % 20 == 0){
			std::cout << "  >>" << ((float)y/VRES) << "%" << endl;
		}
	}
	encodeOneStep(pngName, image, hres, vres);
}

// Function name:		renderAnimation
// Function purpose:	Render animation to a000.png, a001.png, etc.
// Parameters:			none
// Return value:		none
// Any other output:	Writes image files to disk.
void World::renderAnimation(void){
	std::cout << "> Beginning animation render..." << std::endl;
	clearObjects();

	// Add sphere at default location
	objects.push_back(new Sphere(.01, Point3D(-.1, .2, .1)));
	Ashikhmin ash;
	ash.kspec = ash.kdiff = .5;
	ash.c = RGBColor(255, 80, 20);
	objects.back()->sdr = ash.clone();	//@TODO @BUG why does this chop/go to Shader?
	//objects.back()->setShader(ash);
	addBunny();
	// Add floor
	double floorScale = .3;
	double floorHeight = .037;
	objects.push_back(new Triangle(	Point3D(-floorScale, floorHeight+.00001, -floorScale+.00001),
									Point3D(-floorScale, floorHeight, floorScale),
									Point3D(floorScale, floorHeight, -floorScale)));
	objects.back()->sdr->c = RGBColor(255, 0, 0);
	objects.push_back(new Triangle(	Point3D(floorScale, floorHeight, -floorScale),
									Point3D(-floorScale, floorHeight, floorScale),
									Point3D(floorScale, floorHeight, floorScale)));
	objects.back()->sdr->c = RGBColor(0, 0, 255);

	Vector3D delta = ANIMATION_VECTOR;
	double gravity = -.001;

	// For each frame...
	for(int frame = 0; frame < NUM_FRAMES; frame++){
		std::cout << "> Rendering frame " << frame << endl;
		// Rebuild
		if(USE_BVH){
			bvh.clear();
			// Build BVH
			bvh.push_back(BVHNode());
			for(size_t i = 0; i < objects.size(); i++){
				// Have this object add its primitives to the bvh root
				objects[i]->addPrimitives(bvh.back().primitives);
			}
			std::cout << "> Building bounding volume hierarchy..." << std::endl;
			buildBVH(0);
			std::cout << "> Bounding volume hierarchy successfully built." << std::endl;
		}

		// Render image
		std::string pngName("a");
		std::stringstream ss;
		ss << std::setw(3) << std::setfill('0') << frame;
		pngName += ss.str();
		pngName += ".png";
		std::vector<unsigned char> image;
		image.resize(hres * vres * 4);
		// For each pixel...
		for(int y = 0; y < vres; y++){
			for(int x = 0; x < hres; x++){
				RGBColor c;
				if(orthographic)
					c = computePixelOrtho(x, y);
				else
					// Change for perspective
					c = computePixelPerspec(x, y);
				image[4*hres*y + 4*x + 0] = c.r;
				image[4*hres*y + 4*x + 1] = c.g;
				image[4*hres*y + 4*x + 2] = c.b;
				image[4*hres*y + 4*x + 3] = 255;
			}
			// Report status
			if(y % 20 == 0){
				std::cout << "  >>" << ((float)y/VRES) << "%" << endl;
			}
		}
		encodeOneStep(pngName.c_str(), image, hres, vres);
	
		// Update location
		double testHeight = ((Sphere*)(objects.front()))->c.y;
		testHeight -= ((Sphere*)(objects.front()))->r;
		testHeight += delta.y;
		if( testHeight <= floorHeight){
			delta.y = .8*-delta.y;

		}
		((Sphere*)(objects.front()))->c = ((Sphere*)(objects.front()))->c + delta;
		delta.y += gravity;
	}


}

// Function name:		computePixelOrtho
// Function purpose:	Evaluates a single pixel value in orthographic perspective
// Parameters:			
//		x:			x location of pixel
//		y:			y location of pixel
// Return value:		Pixel color
// Any other output:	None
RGBColor World::computePixelOrtho(const int x, const int y) const{
	bool fineBoxes[NUM_SAMPLES][NUM_SAMPLES] = {0};	// True if occupied
	RGBColor accum(0, 0, 0);


	// For each sample...
	for(size_t coarsei = 0; coarsei < SQRT_NUM_SAMPLES; coarsei++){
		for(size_t coarsej = 0; coarsej < SQRT_NUM_SAMPLES; coarsej++){
			// The flow control here is super wonky.
			// 	May want to fix it.
			
			// Choose an arbitrary fineBox - make sure no conflicts.
			int finei = rand_int(0, SQRT_NUM_SAMPLES-1);
			int finej = rand_int(0, SQRT_NUM_SAMPLES-1);
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
			double wx = s*(x - hres/2) + mjFineWidth*(indexj - NUM_SAMPLES/2 + .5);
			double wy = -( s*(y - vres/2 + .5) + mjFineWidth*(indexi - NUM_SAMPLES + .5) );
			Point3D o = Point3D(wx, wy, 0);
			// Generate direction
			Vector3D d = Vector3D(0, 0, -1);
			// Create ray
			Ray ray(o, d);
			// Trace ray
			ShadeRec sr;
			traceRay(ray, sr);
			if(sr.hitObject){
				accum += sr.hitShader->shade(*this, sr);
			} else{
				accum += backgroundColor;
			}
			// Loop back, generate next sample.
		}
	}

	accum /= NUM_SAMPLES;
	return accum;
}

// Function name:		computePixelPerspec
// Function purpose:	Compute single pixel value in perspective projection
// Parameters:			
//		x:			x location of pixel
//		y:			y locatino of pixel
// Return value:		RGB pixel value
// Any other output:	None
RGBColor World::computePixelPerspec(const int x, const int y) const{
	bool fineBoxes[NUM_SAMPLES][NUM_SAMPLES] = {0};	// True if occupied
	RGBColor accum(0, 0, 0);

	// For each sample...
	for(size_t coarsei = 0; coarsei < SQRT_NUM_SAMPLES; coarsei++){
		for(size_t coarsej = 0; coarsej < SQRT_NUM_SAMPLES; coarsej++){
			// The flow control here is super wonky.
			// 	May want to fix it.
			
			// Choose an arbitrary fineBox - make sure no conflicts.
			int finei = rand_int(0, SQRT_NUM_SAMPLES-1);
			int finej = rand_int(0, SQRT_NUM_SAMPLES-1);
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
			// Find ray origin
			Point3D o = E;//Point3D(wx, wy, 0);
			// Find point on viewplane
			double wx = s*(x - hres/2) + mjFineWidth*(indexj - NUM_SAMPLES/2 + .5);
			// Why ain't wy negative?
			double wy = ( s*(y - vres/2 + .5) + mjFineWidth*(indexi - NUM_SAMPLES + .5) );
			Vector3D vpp = E;
			vpp += (d * -vz);
			vpp += wx * vx;
			vpp += wy * vy;
			// Generate direction
			Vector3D d = vpp - E;
			d.normalize();
			// Create ray
			Ray ray(o, d);
			// Trace ray
			ShadeRec sr;
			traceRay(ray, sr);
			if(sr.hitObject){
				accum += sr.hitShader->shade(*this, sr);
			} else{
				accum += backgroundColor;
			}
			// Loop back, generate next sample.
		}
	}

	accum /= NUM_SAMPLES;
	return accum;
}

// Function name:		traceRay
// Function purpose:	Trace ray through scene, keeping track of hits in ShadeRec
// Parameters:			
//		ray:		The ray to trace
// 		sr:			A repository of hit and shading information
// Return value:		None (returns information thru sr)
// Any other output:	None
void World::traceRay(const Ray& ray, ShadeRec& sr) const{
	// Let objects check against this ray,
	//	using sr to record information.
	if(USE_BVH)
		bvh[0].hit(ray, sr);
	else{
		for(size_t i = 0; i < objects.size(); i++){
			objects[i]->hit(ray, sr);
		}
	}
}






