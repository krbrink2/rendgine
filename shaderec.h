#ifndef SHADEREC_R
#define SHADEREC_R

#include "Constants.h"
#include "Point3D.h"
#include "Normal.h"


class ShadeRec{
	public:
		bool hitObject;
		double t;
		Point3D hitPoint;
		Normal hitNormal;
		RGBColor hitColor;

		ShadeRec();									// Constructor
		ShadeRec(const ShadeRec& sr);				// Copy constructor
		ShadeRec& operator=(const ShadeRec& rhs);	// Assignment operator
		~ShadeRec(void);							// Destructor
};


#endif