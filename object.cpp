#include "object.h"

Object::Object(){}

Object::Object(const Object& obj){}

Object& Object::operator=(const Object& rhs){
	color = rhs.color;
	return *this;
}

Object::~Object(){}

