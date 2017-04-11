#include "mesh.h"
#include <iostream>

const int MAX_VERTICES_PER_FACE = 255;

// ---- Constructor ----
Mesh::Mesh():
	Object(),
	loaded(false),
	numTriangles(0)
{}

// ---- Constructor ----
Mesh::Mesh(const char* filename):
	Object()
{
	load(filename);

}

// ---- Copy Constructor ----
Mesh::Mesh(const Mesh& mesh):
	Object(mesh),
	loaded(mesh.loaded),
	numTriangles(mesh.numTriangles) 
{
	instances = mesh.instances;
	for(size_t i = 0; i < mesh.faces.size(); i++)
		faces.push_back(mesh.faces[i]->clone());
}

// ---- Assignment operator ----
Mesh& Mesh::operator=(const Mesh& rhs){
	sdr = rhs.sdr->clone();
	loaded = rhs.loaded;
	numTriangles = rhs.numTriangles;
	instances = rhs.instances;
	for(size_t i = 0; i < rhs.faces.size(); i++){
		faces.push_back(rhs.faces[i]->clone());
	}
	return *this;
}

// ---- Destructor ----
Mesh::~Mesh(){
	clear();
}

// Function name:		clone
// Function purpose:	Returns pointer to new clone of this Mesh.
// Parameters:			none
// Return value:		Pointer to new clone.
// Any other output:	none
Mesh* Mesh::clone(){
	return new Mesh(*this);
}

// Function name:		getMinPoint
// Return value:		minPoint of this mesh volume
Point3D Mesh::getMinPoint(){
	Point3D minPoint(kHugeValue, kHugeValue, kHugeValue);
	// For each instance...
	for(const instance_t& inst : instances){
		const Matrix& matrix = inst.matrix;
		// For each face...
		for(size_t i = 0; i < faces.size(); i++){
			Point3D testPoint = matrix * faces[i]->getMinPoint();
			minPoint.x = min(minPoint.x, testPoint.x);
			minPoint.y = min(minPoint.y, testPoint.y);
			minPoint.z = min(minPoint.z, testPoint.z);
		}
	}
	return minPoint;

/*	// How it was done before:
	Point3D minPoint(kHugeValue, kHugeValue, kHugeValue);
	// For each face...
	for(size_t i = 0; i < faces.size(); i++){
		Point3D testPoint = faces[i]->getMinPoint();
		minPoint.x = min(minPoint.x, testPoint.x);
		minPoint.y = min(minPoint.y, testPoint.y);
		minPoint.z = min(minPoint.z, testPoint.z);
	}
	return minPoint;
*/
}

// Function name:		getMaxPoint
// Parameters:			maxPoint of this mesh volue
Point3D Mesh::getMaxPoint(){
	Point3D maxPoint(-kHugeValue, -kHugeValue, -kHugeValue);
	// For each instace...
	for(const instance_t& inst : instances){
		const Matrix& matrix = inst.matrix;
		// For each face...
		for(size_t i = 0; i < faces.size(); i++){
			Point3D testPoint = matrix * faces[i]->getMaxPoint();
			maxPoint.x = max(maxPoint.x, testPoint.x);
			maxPoint.y = max(maxPoint.y, testPoint.y);
			maxPoint.z = max(maxPoint.z, testPoint.z);
		}
	}
	return maxPoint;
}

// Function name:		getMedPoint
// Parameters:			Median point of this mesh volume.
Point3D Mesh::getMedPoint(){
	return (getMinPoint() + getMaxPoint())*.5;
}

// Function name:		addPrimitives
// Function purpose:	Adds this mesh's primitives to vect.
void Mesh::addPrimitives(std::vector<Object*>& vect){
	// This will be pretty ad-hoc...
	// For each instance...
	for(const auto& inst : instances){
		const Matrix& matrix = inst.matrix;
		// For each face...
		for(size_t i = 0; i < faces.size(); i++){
			vect.push_back(new Triangle(
				matrix * faces[i]->v0,
				matrix * faces[i]->v1,
				matrix * faces[i]->v2));
			vect.back()->sdr = inst.sdr;
			//faces[i]->addPrimitives(vect);
		}
	}
}

// Function name:		hit
// Function purpose:	hit function for this mesh object
// Parameters:			ray to trace, sr to record.
// Return value:		True if hit
// Any other output:	Writes to sr
bool Mesh::hit(const Ray& ray, ShadeRec& sr){
	for(size_t i = 0; i < faces.size(); i++){
		faces[i]->hit(ray, sr);
	}
	return sr.hitObject;
}

// Function name:		clear
// Function purpose:	Frees and resets this mesh
// Any other output:	none
void Mesh::clear(void){
	// Clear faces
	for(size_t i = 0; i < faces.size(); i++){
		delete faces[i];
		faces[i] = NULL;
	}
	faces.clear();
	// Clear instances
	for(auto&& instance : instances){
		// Delete sdr
		if(instance.sdr != NULL)
			delete sdr;
		sdr = NULL;
		// Clear instaces.faces
		for(Triangle* tri : instance.faces){
			if(tri != NULL)
				delete tri;
			tri = NULL;
		}
		instance.faces.clear();
	}
	instances.clear();
	loaded = false;
	maxs = mins = Vector3D(0,0,0);
	numTriangles = 0;
}

// Function name:		dataPass
// Function purpose:	Helper: pulls vertices and normals from file.
// Parameters:			file to read, vertex and normal arrays to push to.
// Return value:		True if successful.
// Any other output:	none
bool Mesh::dataPass(FILE* file, std::vector<Point3D>& vertices, 
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
		if(*end == '\n')
			*end = '\0';

		// Vertices
		if(line[0] == 'v' && line[1] == ' '){
			Point3D data;
			if(sscanf(line, "v %lf %lf %lf", &data.x, &data.y, &data.z) == 3){
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
			if(sscanf(line, "vn %lf %lf %lf", &data.x, &data.y, &data.z) == 3){
				normals.push_back(data);
			}
		}
	}
	//std::cout << maxs.x << " " << maxs.y << " " << maxs.z << std::endl;
	return true;
}

// Function name:		facePass
// Function purpose:	Helper; reads faces from file, adds them to faces vector.
// Parameters:			file to read, vertices and normals for generating faces.
// Return value:		True if successful.
// Any other output:	Writes to faces vector.
bool Mesh::facePass(FILE* file, std::vector<Point3D>& 	vertices, 
	std::vector<Normal>& normals){

	numTriangles = 0;

	char line[2048];
	while(fgets(line, sizeof(line), file)){
		// Strip trailing newline
		char* end = &line[strlen(line) - 1];
		if(*end == '\n')
			*end = '\0';

		// Face
		if(line[0] == 'f' && line[1] == ' '){
			int numVerts = 0;
            int numNorms = 0;
            //int normIndices[MAX_VERTICES_PER_FACE];
            int vertIndices[MAX_VERTICES_PER_FACE];

            int vertidx,texidx,normidx;
            const char* cp = &line[2];
            while (*cp == ' ') cp++;
            while (sscanf(cp, "%d//%d", &vertidx, &normidx) == 2) {
                if( numVerts >= MAX_VERTICES_PER_FACE || vertidx > (int)vertices.size() - 0 ||
                    numNorms >= MAX_VERTICES_PER_FACE || normidx > (int)normals.size() - 0 )
                    return false;
                vertIndices[numVerts++] = vertidx;
                //normIndices[numNorms++] = normidx;
                while (*cp && *cp != ' ') cp++;
                while (*cp == ' ') cp++;
            }
            while (sscanf(cp, "%d/%d/%d", &vertidx, &texidx, &normidx) == 3) {
                if( numVerts >= MAX_VERTICES_PER_FACE || vertidx > (int)vertices.size() - 0 ||
                    numNorms >= MAX_VERTICES_PER_FACE || normidx > (int)normals.size() - 0 )
                    return false;
                vertIndices[numVerts++] = vertidx;
                //normIndices[numNorms++] = normidx;
                while (*cp && *cp != ' ') cp++;
                while (*cp == ' ') cp++;
            }
            while (sscanf(cp, "%d/%d", &vertidx, &texidx) == 2) {
                if( numVerts >= MAX_VERTICES_PER_FACE || vertidx > (int)vertices.size() - 0 )
                    return false;
                vertIndices[numVerts++] = vertidx;
                while (*cp && *cp != ' ') cp++;
                while (*cp == ' ') cp++;
            }
            while (sscanf(cp, "%d", &vertidx) == 1) {
                if( numVerts >= MAX_VERTICES_PER_FACE || vertidx > (int)vertices.size() - 0 )
                    return false;
                vertIndices[numVerts++] = vertidx;
                while (*cp && *cp != ' ') cp++;
                while (*cp == ' ') cp++;
            }

            if (*cp)
                return false;

            // world's most naive trianglization
            for( int i = 1; i < numVerts - 1; i++ ) {
            	/*
                vertexData.push_back( vertices[vertIndices[0] - 1] );
                vertexData.push_back( vertices[vertIndices[i] - 1] );               
                vertexData.push_back( vertices[vertIndices[i+1] - 1] );*/
                faces.push_back(new Triangle(	vertices[vertIndices[0] - 1],
                								vertices[vertIndices[i] - 1],
                								vertices[vertIndices[i+1] - 1]));


                /*
                // if we have a normal for each vertex, use them. Otherwise generate some
                // ugly facety normals just so we have something.
                if( numVerts == numNorms ) {
                    normalData.push_back( normals[normIndices[0] - 1] );
                    normalData.push_back( normals[normIndices[i] - 1] );
                    normalData.push_back( normals[normIndices[i+1] - 1] );      
                } else {
                    float3 v1 = vertices[vertIndices[0] - 1] - vertices[vertIndices[i] - 1];
                    float3 v2 = vertices[vertIndices[0] - 1] - vertices[vertIndices[i+1] - 1];
                    float3 n = v1.cross(v2).getNormalized();

                    normalData.push_back( n );
                    normalData.push_back( n );
                    normalData.push_back( n );
                }*/
                faces.back()->generateNormal();

                numTriangles++;
            }
		}
	}
	return true;
}

// Function name:		load
// Function purpose:	Loads .obj into this mesh.
// Parameters:			filename to read from.
// Return value:		True if successful
// Any other output:	Loads this mesh.
// Inspired by https://github.com/wdas/brdf/blob/master/src/brdf/SimpleModel.cpp
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


	return true;
}

// Function name:		setShader
// Function purpose:	Sets all shaders in this mesh to copy of _sdr.
// Parameters:			_sdr to be copied.
void Mesh::setShader(const Shader* _sdr){
	// Sets all children to point to same shader.
	if(sdr != NULL)
		delete sdr;
	sdr  = _sdr->clone();
	for(size_t i = 0; i < faces.size(); i++){
		faces[i]->setShader(_sdr);
	}
}

// Function name:		addInstance
// Function purpose:	Creates an instance of this mesh, modified
// 						by matrix, shaded with sdr.
// Parameters:			matrix for affine transformations.
//						sdr for shading.
// Return value:		none
// Any other output:	pushed to instances vector.
void Mesh::addInstance(const Matrix& matrix, Shader* _sdr){
	instance_t inst;
	inst.matrix = matrix;
	inst.sdr = _sdr;
	for(const Triangle* face : faces){
		inst.faces.push_back(new Triangle(
			matrix * face->v0,
			matrix * face->v1, 
			matrix * face->v2));
	}
	instances.push_back(inst);
}

