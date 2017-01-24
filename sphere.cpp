#include <iostream>
#include <math.h>
#include "sphere.h"
#include "Constants.h"
using namespace std;

// ---- Default Constructor ----
Sphere::Sphere(): r(1), c(Point3D()) {

}

// ---- Constructor ----
Sphere::Sphere(double _r, Point3D _c): r(_r), c(_c) {

}

Sphere::~Sphere(){

}

bool Sphere::hit(const Ray& ray, double& t){
	double A = ray.d * ray.d;
	double B = 2*(ray.o - c) * ray.d;
	double C = (ray.o - c) * (ray.o - c) - r*r;
	double disc = B*B - 4*A*C;


	if(disc < 0){
		cout << "A" << endl;
		return false;
	}
	else{
		//cout << "B" << endl;
		return true;
	}


	//@TODO
	if(fabs(disc) < kEpsilon){

	}
	
}