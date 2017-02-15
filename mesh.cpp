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
Mesh::Mesh(const Mesh& mesh): p(mesh.p) {
	sdr = mesh.sdr();
	for(size_t i = 0; i < mesh.faces.size(); i++)
		faces.push_back(mesh.faces[i]->clone());
}

// ---- Assignment operator ----
Mesh& Mesh::operator=(const Mesh& rhs){
	sdr = rhs.sdr;
	p = rhs.p;
	for(size_t i = 0; i < rhs.faces.size(); i++){
		faces.push_back(rhs.faces[i]->clone());
	}
	return *this;
}

// ---- Destructor ----
Mesh::~Mesh(){
	clear();
}

Mesh* Mesh::clone(){
	return new Mesh(*this);
}

bool Mesh::hit(const Ray& ray, ShadeRed& sr){
	//@TODO
}

// Helper function
void Mesh::clear(void){
	for(size_t i = 0; i < faces.size(); i++){
		delete faces[i];
		faces[i] = NULL;
	}
	faces.clear();	
}

bool Mesh::load(const char* filename){
	clear(); 		// Clear faces
	
}







// Function name:		
// Function purpose:	
// Parameters:			
// Return value:		
// Any other output:	








