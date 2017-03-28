#include "pointlight.h"
#include "world.h"

// ---- Default constructor ----
PointLight::PointLight():
	Light(),
	point(Point3D(0, 0, 0))
{}

// ---- Constructor ----
PointLight::PointLight(const Point3D& p):
	Light(),
	point(p)
{}

// Function name:		getIrradiance
// Function purpose:	Find irradiance point p receives from this light source.
// Parameters:			Point p
// Return value:		Irradiance
// Any other output:	none
RGBColor PointLight::getIrradiance(const Point3D& p){
	// Check to see if this point is in shadow.
	Ray ray;
	ShadeRec sr;
	ray.o = p;
	ray.d = point - p;
	ray.d.normalize();
	worldPtr->traceRay(ray, sr);
	double distance = point.distance(p);

	if(sr.hitObject && sr.t < distance){
		return RGBColor(0,0,0);
	}
	else
		return color;
}

// Function name:		getDirection
// Function purpose:	Get direction to this light from p.
Vector3D PointLight::getDirection(const Point3D& p){
	Vector3D direction = point - p;
	direction.normalize();
	return direction;
}

void PointLight::getSamples(vector< pair<Vector3D, RGBColor> >& vect, const Point3D p){
	vect.push_back(pair<Vector3D, RGBColor>(getDirection(p), getIrradiance(p)));
}