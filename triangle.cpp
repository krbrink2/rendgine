#include <math.h>
#include "triangle.h"

// ---- Default Constructor ----
Triangle::Triangle():
	Object(),
	v0(0, 0, 0),
	v1(0, 0, 1),
	v2(1, 0, 0),
	n(0, 1, 0){
}

// Constructor
Triangle::Triangle(const Point3D& _v0, const Point3D& _v1, const Point3D& _v2):
	Object(),
	v0(_v0),
	v1(_v1),
	v2(_v2)
{
	generateNormal();
	n.normalize();
}

// Function name:		clone
// Function purpose:	Allocate identical triangle
// Parameters:			None
// Return value:		Pointer to identical triangle
// Any other output:	None
Triangle* Triangle::clone(void){
	return new Triangle(*this);
}

Point3D Triangle::getMinPoint(){
	double x = min(v0.x, min(v1.x, v2.x));
	double y = min(v0.y, min(v1.y, v2.y));
	double z = min(v0.z, min(v1.z, v2.z));
	return Point3D(x, y, z);
}

Point3D Triangle::getMaxPoint(){
	double x = max(v0.x, max(v1.x, v2.x));
	double y = max(v0.y, max(v1.y, v2.y));
	double z = max(v0.z, max(v1.z, v2.z));
	return Point3D(x, y, z);
}

Point3D Triangle::getMedPoint(){
	return (getMinPoint() + getMaxPoint())*.5;
}

void Triangle::addPrimitives(std::vector<Object*>& vect){
	vect.push_back(this);
}

// Function name:		hit
// Function purpose:	Test if ray hits triangle, record info if so.
// Parameters:			
//		ray:		Ray being traced
//		sr:			ShadeRec to store values
// Return value:		True if ray 
// Any other output:	Writes to sr
bool Triangle::hit(const Ray& ray, ShadeRec& sr){
	// The below math is courtesy of Suffern's Ray Tracing from the Ground Up
	double	a = v0.x - v1.x,
			b = v0.x - v2.x,
			c = ray.d.x,
			d = v0.x - ray.o.x;
	double	e = v0.y - v1.y,
			f = v0.y - v2.y,
			g = ray.d.y,
			h = v0.y - ray.o.y;
	double	i = v0.z - v1.z,
			j = v0.z - v2.z,
			k = ray.d.z,
			l = v0.z - ray.o.z;

	double	m = f*k - g*j,
			n = h*k - g*l,
			p = f*l - h*j;
	double	q = g*i - e*k,
			s = e*j - f*i;

	double	inv_denom = 1.0 / (a*m + b*q + c*s);

	double	e1 = d*m - b*n - c*p,
			beta = e1 * inv_denom;

	if(beta < 0.0)
		return false;

	double	r = e*l - h*i,
			e2 = a*n + d*q + c*r,
			gamma = e2 * inv_denom;

	if(gamma < 0.0)
		return false;
	if(beta + gamma > 1.0)
		return false;

	double	e3 = a*p - b*r + d*s,
			newt = e3*inv_denom;

	if(newt < kEpsilon)
		return false;

	if(newt > 0 && newt < sr.t){
		// Register hit
		sr.hitObject = true;
		sr.t = newt;
		sr.hitPoint = ray.o + newt*ray.d;
		sr.hitNormal = this->n;
		sr.hitShader = sdr;

		// Push hitPoint away from surface slightly
		sr.hitPoint.x += sr.hitNormal.x * .000001;
		sr.hitPoint.y += sr.hitNormal.y * .000001;
		sr.hitPoint.z += sr.hitNormal.z * .000001;
		return true;
	}
	else
		return false;
}

void Triangle::generateNormal(void){
	n = (v1 - v0) ^ (v2 - v0);
	n.normalize();
}

















