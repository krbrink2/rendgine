#ifndef LIGHT_H
#define LIGHT_H
#include <vector>
#include "shaderec.h"
#include "Point3D.h"
#include "Ray.h"
#include "RGBColor.h"
#include "Vector3D.h"
using namespace std;

// Forward declarations
class World;

// Globals
extern World* worldPtr;

class Light{
public:
	Light();
	virtual ~Light();
	virtual RGBColor getIrradiance(const Point3D& p) = 0;
	virtual Vector3D getDirection(const Point3D& p) = 0;
	virtual void getSamples(vector< pair<Vector3D, RGBColor> >& vect, const Point3D p) = 0;
	//virtual void addSamples(const Point3D point, std::vector< std::pair<Ray, RGBColor> >& vect) = 0;
		//@TODO implement the above

	RGBColor color;


};



#endif