#include "plane.h"

// ---- Default Constructor ----
Plane::Plane(): a(Point3D()), n(Normal()) {

}

// ---- Constructor ----
Plane::Plane(Point3D _a, Normal _n): a(_a), n(_n) {

}

Plane::~Plane(){

}