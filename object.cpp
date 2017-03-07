#include "object.h"

// ---- Default constructor ----
Object::Object():
	sdr(new Shader())
{}

// ---- Copy constructor ----
Object::Object(const Object& obj):
	sdr(obj.sdr->clone())
{}

// ---- Destructor ----
Object::~Object(){
	if(sdr != NULL)
		delete sdr;
}

void Object::setShader(const Shader& _sdr){
	if(sdr != NULL)
		delete sdr;
	sdr = _sdr.clone();
}