#ifndef SHADEREC_R
#define SHADEREC_R

#include "world.h"
#include "Constants.h"
#include "Point3D.h"
#include "Normal.h"


class ShadeRec{
	public:
		World& w;
		bool hitObject;
		double t;
		Point3D hitPoint;
		Normal hitNormal;
		RGBColor hitColor;

		ShadeRec(World& _w);						// Constructor
		ShadeRec(const ShadeRec& sr);				// Copy constructor
		ShadeRec& operator=(const ShadeRec& rhs);	// Assignment operator
		~ShadeRec(void);							// Destructor
};


#endif