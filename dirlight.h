#ifndef DIRLIGHT_H
#def DIRLIGHT_H
#include "light.h"

class DirLight: public Light{
	DirLight();

	Vector3D direction;

}


#endif