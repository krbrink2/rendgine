#include "world.h"

// ---- Constructor ----
World::World(void){
	backgroundColor = RGBColor(0, 0, 0);
}

// ---- Copy constructor ----
World::World(const World& w):
	.s(w.s),
	.hres(w.hres),
	.vres(w.vres),
	backgroundColor(w.backgroundColor)
{
	for(size_t i = 0; i < w.objects.size(); i++){
		objects.pushBack(new Object(w.objects[i]));
	}
}

// ---- Assignment operator ----
World& World::operator=(const World& w){
	backgroundColor = w.backgroundColor;
	s = w.s;
	vres = w.vres;
	hres = w.hres;
	for(size_t i = 0; i < w.objects.size(); i++){
		objects.pushBack(new Object(w.objects[i]));
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
	backgroundColor = RGBColor(0, 0, 0);

	// Add objects
	Normal n(-1, 1, 1);
	n.normalize();
	objects.push_back(new Plane(Point3D(0, 0, -10), n));
	objects[0]->color = RGBColor(255, 0, 0);
	objects.push_back(new Sphere(5, Point3D(0, 0, -10)));
	objects[1]->color = RGBColor(0, 255, 0);	
}

void World::renderScene(void){
	//generate some image
	const char* pngName = "image.png";
	std::vector<unsigned char> image;
	image.resize(hres * vres * 4);

	// For each pixel...
	for(int y = 0; y < vres; y++)
		for(int x = 0; x < hres; x++){
			RGBColor c = computePixel(int x, int y);
			image[4*hres*y + 4*x + 0] = c.r;
			image[4*hres*y + 4*x + 1] = c.g;
			image[4*hres*y + 4*x + 2] = c.b;
			image[4*hres*y + 4*x + 3] = 255;
		}
}

RGBColor World::computePixel(const int x, const int y){
	// Create ray
	double wx = s*(x - hres/2 + .5);
	double wy = s*(y - vres/2 + .5);
	Point3D o = Point3D(wx, wy, 0);
	Vector3D d = Vector3D(0, 0, -1);
	Ray ray = Ray(o, d);

	// Trace ray
	ShadeRec sr(this);
	traceRay(ray, sr);
	return sr.hitColor;
}

void World::traceRay(const Ray& ray, ShadeRec& sr){

	// Let every object check against this ray,
	//	using sr to record information.
	for(size_t i = 0; i < objects.size(); i++){
		objects[i].hit(ray, sr);
	}
}
