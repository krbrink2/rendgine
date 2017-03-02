#include "mesh.h"
#include <iostream>

const int MAX_VERTICES_PER_FACE = 255;

// ---- Constructor ----
Mesh::Mesh():
	Object(),
	p(Point3D()),
	loaded(false),
	numTriangles(0)
{}

// ---- Constructor ----
Mesh::Mesh(const char* filename, const Point3D _p):
	Object(),
	p(_p)
{
	load(filename);

}

// ---- Copy Constructor ----
Mesh::Mesh(const Mesh& mesh):
	Object(mesh),
	p(mesh.p),
	loaded(mesh.loaded),
	numTriangles(mesh.numTriangles) 
{
	for(size_t i = 0; i < mesh.faces.size(); i++)
		faces.push_back(mesh.faces[i]->clone());
}

// ---- Assignment operator ----
Mesh& Mesh::operator=(const Mesh& rhs){
	sdr = rhs.sdr->clone();
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
	delete sdr;
}

Mesh* Mesh::clone(){
	return new Mesh(*this);
}

Point3D Mesh::getMinPoint(){
	Point3D minPoint;
	for(size_t i = 0; i < faces.size(); i++){
		Point3D testPoint = faces[i]->getMinPoint();
		minPoint.x = min(minPoint.x, testPoint.x);
		minPoint.y = min(minPoint.y, testPoint.y);
		minPoint.z = min(minPoint.z, testPoint.z);
	}
	return minPoint;
}

Point3D Mesh::getMaxPoint(){
	Point3D maxPoint;
	for(size_t i = 0; i < faces.size(); i++){
		Point3D testPoint = faces[i]->getMaxPoint();
		maxPoint.x = max(maxPoint.x, testPoint.x);
		maxPoint.y = max(maxPoint.y, testPoint.y);
		maxPoint.z = max(maxPoint.z, testPoint.z);
	}
	return maxPoint;
}

Point3D Mesh::getMedPoint(){
	return (getMinPoint() + getMaxPoint())*.5;
}

void Mesh::addPrimitives(std::vector<Object*>& vect){
	for(size_t i = 0; i < faces.size(); i++){
		faces[i]->addPrimitives(vect);
	}
}

bool Mesh::hit(const Ray& ray, ShadeRec& sr){
	for(size_t i = 0; i < faces.size(); i++){
		faces[i]->hit(ray, sr);
	}
	if(sr.hitObject && sr.hitNormal.z > 0){	// For debugging
		 return sr.hitObject;
	}
	return sr.hitObject;
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

void Mesh::setShader(const Shader& _sdr){
	sdr  = _sdr.clone();
	for(size_t i = 0; i < faces.size(); i++){
		faces[i]->sdr = _sdr.clone();
	}
}







// Function name:		
// Function purpose:	
// Parameters:			
// Return value:		
// Any other output:	








