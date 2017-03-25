#include "shaderec.h"

// ---- Constructor ----
ShadeRec::ShadeRec(void){
	hitObject = false;
	t = kHugeValue;
	numBounces = 0;
	hitShader = NULL;
}


