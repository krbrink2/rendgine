#include "object.h"

// ---- Default constructor ----
Object::Object():
	sdr()
{}

// ---- Copy constructor ----
Object::Object(const Object& obj):
	sdr(obj.sdr)
{}

// ---- Destructor ----
Object::~Object(){}
