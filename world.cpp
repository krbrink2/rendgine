#include "world.h"

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
	backgroundColor = RGBColor(0, 0, 0);
	E = Point3D(0, 0, 100);

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
		RGBColor c = computePixel(x, y);
		image[4*hres*y + 4*x + 0] = c.r;
		image[4*hres*y + 4*x + 1] = c.g;
		image[4*hres*y + 4*x + 2] = c.b;
		image[4*hres*y + 4*x + 3] = 255;
	}
	encodeOneStep(pngName, image, hres, vres);
}

RGBColor World::computePixel(const int x, const int y) const{
	// Create ray
	double wx = s*(x - hres/2 + .5);
	double wy = -s*(y - vres/2 + .5);
	Point3D o = Point3D(wx, wy, 0);
	Vector3D d = Vector3D(0, 0, -1);
	Ray ray = Ray(o, d);

	// Trace ray
	ShadeRec sr(backgroundColor);
	traceRay(ray, sr);
	if(sr.hitObject){
		RGBColor retval = sr.hitShader->shade(*this, sr.hitNormal);	// Segfault
		return retval;
	} else{
		return backgroundColor;
	}

}

void World::traceRay(const Ray& ray, ShadeRec& sr) const{

	// Let every object check against this ray,
	//	using sr to record information.
	for(size_t i = 0; i < objects.size(); i++){
		objects[i]->hit(ray, sr);
	}
}
