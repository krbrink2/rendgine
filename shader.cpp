#include "shader.h"
#include "world.h"

// ---- Default constructor ----
Shader::Shader(){}

// ---- Copy constructor ----
Shader::Shader(const Shader& sdr){}

// ---- Assignment operator ----
Shader& Shader::operator=(const Shader& rhs){
	return *this;
}

// ---- Destructor ----
Shader::~Shader(){}

RGBColor Shader::shade(const World& w){
	return w.backgroundColor;
}


