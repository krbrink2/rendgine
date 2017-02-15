#include "mesh.h"
#include <ifstream>

// ---- Constructor ----
Mesh::Mesh(): p(Point3D()) {
	sdr = Shader();
}

// ---- Constructor ----
Mesh::Mesh(const char* filename, const Point3D _p) : p(_p) {
	//@TODO make this load

}

// ---- Copy Constructor ----
Mesh::Mesh(const Mesh& mesh):
	p(mesh.p),

