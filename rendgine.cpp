#include <iostream>
#include <vector>
#include "lodepng.h"
#include "object.h"
#include "plane.h"
#include "shaderec.h"
#include "sphere.h"
#include "world.h"
#include "utils.h"
using namespace std;

// ---- Global variable declarations ----
World* worldPtr;		// Pointer to active World object.
int raysShot;			// Total number of rays shot.

// ---- Function declarations ----

// Function name:		encodeOneStep
// Function purpose:	Write image to disk.
// Parameters:
//	filename:		Name of file to write
//	image:			Vector of RGBA values
//	hres, vres:		Horizontal and vertical resolutions
// Return value:		None
// Any other output:	Writes png file
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned hres, unsigned vres);


// ---- Main funciton ----

// Function name:		main
// Function purpose:	Begin execution
// Parameters:			Command line parameters (unused)
// Return value:		0 on success
// Any other output:	Writes file "image.png" to disk
int main(int argc, char* argv[]){

	raysShot = 0;
	worldPtr = new World();
	worldPtr->build();
	if(ANIMATE)
		worldPtr->renderAnimation();
	else
		worldPtr->renderScene();
	delete worldPtr;
	cout << "> Rays shot: " << raysShot << endl;
	return 0;


}

// ---- Function defintions ----
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned hres, unsigned vres)
{
	unsigned error = lodepng::encode(filename, image, hres, vres);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}



// Function name:		
// Function purpose:	
// Parameters:			
// Return value:		
// Any other output:	