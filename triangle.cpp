#include <math.h>
#include "triangle.h"

// ---- Default Constructor ----
Triangle::Triangle():
	Object(),
	v0(0, 0, 0),
	v1(0, 0, 1),
	v2(1, 0, 0),
	n(0, 1, 0)
{}

Triangle::Triangle(const Point3D& _v0, const Point3D& _v1, const Point3D& _v2):
	Object(),
	v0(_v0),
	v1(_v1),
	v2(_v2)
{
	n = (v1 - v0) ^ (v2 - v0);
	n.normalize();
}

/*
// ---- Copy constructor ----
Triangle::Triangle(const Triangle& t):
	Object(t),
	v0(t.v0),
	v1(t.v1),
	v2(t.v2),
	n(t.n)
{}

// ---- Assignment operator ----
Triangle& Triangle::operator=(const Triangle& rhs){
	v0 = rhs.v0;
	v1 = rhs.v1;
	v2 = rhs.v2;
	n = rhs.n;
	
	return *this;
}
*/

Triangle* Triangle::clone(void){
	return new Triangle(*this);
}

bool Triangle::hit(const Ray& ray, ShadeRec& sr){
	/*double dDotn = ray.d * n;
	if(fabs(dDotn) < kEpsilon){
		return false;
	}

	double newt = ((v0 - ray.o) * n)/dDotn;
	if(newt < 0 || newt > sr.t)
		return false;*/


	//@TODO MARK AS SUFFERN'S
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
		sr.hitShader = &sdr;

		// Push hitPoint away from surface slightly
		sr.hitPoint.x += sr.hitNormal.x * .000001;
		sr.hitPoint.y += sr.hitNormal.y * .000001;
		sr.hitPoint.z += sr.hitNormal.z * .000001;
		return true;
	}
	else
		return false;
}


















