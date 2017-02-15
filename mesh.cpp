#include "mesh.h"
#include <fstream>
#include <float.h>

const int MAX_VERTICES_PER_FACE = 255;

// ---- Constructor ----
Mesh::Mesh(): p(Point3D()), loaded(false), numTriangles(0) {
	sdr = Shader();
}

// ---- Constructor ----
Mesh::Mesh(const char* filename, const Point3D _p) : p(_p), loaded(false) {
	//@TODO make this load

}

// ---- Copy Constructor ----
Mesh::Mesh(const Mesh& mesh): Object(mesh), p(mesh.p), loaded(mesh.loaded), numTriangles(mesh.numTriangles) {
	sdr = mesh.sdr;
	for(size_t i = 0; i < mesh.faces.size(); i++)
		faces.push_back(mesh.faces[i]->clone());
}

// ---- Assignment operator ----
Mesh& Mesh::operator=(const Mesh& rhs){
	sdr = rhs.sdr;
	p = rhs.p;
	loaded = rhs.loaded;
	numTriangles = rhs.numTriangles;
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

bool Mesh::hit(const Ray& ray, ShadeRec& sr){
	//@TODO
	return false;
}

// Helper function
void Mesh::clear(void){
	for(size_t i = 0; i < faces.size(); i++){
		delete faces[i];
		faces[i] = NULL;
	}
	faces.clear();
	loaded = false;
	maxs = mins = Vector3D(0,0,0);
	numTriangles = 0;
}

bool Mesh::dataPass(const FILE* file; std::vector<Point3D>& vertices, \
	std::vector<Normal>& normals){
	maxs = Vector3D(-FLT_MAX);
	mins = Vector3D(FLT_MAX);

	vertices.clear();
	normals.clear();
	numTriangles = 0;

	char line[2048];
	while(fgets(line, sizeof(line), file)){

		// Strip trialing newline
		char* end = &line[strlen(line) - 1];
		if(*end == '\n ')
			*end = '\0';

		// Vertices
		if(line[0] == 'v' && line[1] == ' '){
			Point3D data;
			if(sscanf(line, "v %f %f %f", %data.x, %data.y, %data.z) == 3){
				maxs.x = max(maxs.x, data.x);
				mins.x = min(mins.x, data.x);
				maxs.y = max(maxs.y, data.y);
				mins.y = min(mins.y, data.y);
				maxs.z = max(maxs.z, data.y);
				mins.z = min(mins.z, data.y);
				vertices.push_back(data);
			}
		}


		// Normals
		if(line[0] == 'v' && line[1] == 'n'){
			Normal data;
			if(sscanf(line, "vn %f %f %f", &data.x, &data.y, &data.z) == 3){
				normals.push_back(data);
			}
		}
	}
	return true;
}


bool Mesh::facePass(const FILE* file; std::vector<Point3D>& vertices, \
	std::vector<Normal>& normals){



	return false;
}


bool Mesh::load(const char* filename){
	clear(); 		// Clear faces

	FILE* file = fopen(filename, "r");
	if(!file)
		return false;

	std::vector<Point3D> vertices;
	std::vector<Normal> normals;

	if(!dataPass(file, vertices, normals)){
		fclose(file);
		return false;
	}

	rewind(file);
	if(!facePass(file, vertices, normals)){
		fclose(file);
		return false;
	}

	fclose(file);
	loaded = true;


	return false;
}







// Function name:		
// Function purpose:	
// Parameters:			
// Return value:		
// Any other output:	








