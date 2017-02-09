#include "shaderec.h"

// ---- Constructor ----
ShadeRec::ShadeRec(void){
	hitObject = false;
	t = kHugeValue;
	hitColor = RGBColor(0, 0, 0);
	hitShader = NULL;
}

// ---- Constructor ----
ShadeRec::ShadeRec(const RGBColor& c):
	hitObject(false),
	t(kHugeValue),
	hitColor(c),
	hitShader(NULL)
	{}

