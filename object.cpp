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

// Function name:		setShader
// Function purpose:	sets sdr to be copy of _sdr.
// Parameters:			_sdr to be copied.
// Return value:		none
// Any other output:	Writes sdr.
void Object::setShader(const Shader& _sdr){
	if(sdr != NULL)
		delete sdr;
	sdr = _sdr.clone();
}