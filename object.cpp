#include "object.h"

Object::Object():
	sdr()
{}

Object::Object(const Object& obj):
	sdr(obj.sdr)
{}

Object& Object::operator=(const Object& rhs){
	sdr = rhs.sdr;
	return *this;
}

Object::~Object(){}
