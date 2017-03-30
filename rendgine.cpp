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

// Pulled from 
//	https://people.sc.fsu.edu/~jburkardt/cpp_src/halton/halton.cpp
double *halton ( int i, int m );

// ---- Main funciton ----

// Function name:		main
// Function purpose:	Begin execution
// Parameters:			Command line parameters (unused)
// Return value:		0 on success
// Any other output:	Writes file "image.png" to disk
int main(int argc, char* argv[]){

	worldPtr = new World();
	worldPtr->build();
	if(ANIMATE)
		worldPtr->renderAnimation();
	else
		worldPtr->renderScene();
	delete worldPtr;
	return 0;


}

// ---- Function defintions ----
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned hres, unsigned vres)
{
	unsigned error = lodepng::encode(filename, image, hres, vres);
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

// Pulled from 
//	https://people.sc.fsu.edu/~jburkardt/cpp_src/halton/halton.cpp
double *halton ( int i, int m )
{
  int d;
  int i1;
  int j;
  double *prime_inv;
  double *r;
  int *t;

  prime_inv = new double[m];
  r = new double[m];
  t = new int[m];

  for ( j = 0; j < m; j++ )
  {
    t[j] = i;
  }
//
//  Carry out the computation.
//
  for ( j = 0; j < m; j++ )
  {
    prime_inv[j] = 1.0 / ( double ) ( prime ( j + 1 ) );
  }

  for ( j = 0; j < m; j++ )
  {
    r[j] = 0.0;
  }

  while ( 0 < i4vec_sum ( m, t ) )
  {
    for ( j = 0; j < m; j++ )
    {
      d = ( t[j] % prime ( j + 1 ) );
      r[j] = r[j] + ( double ) ( d ) * prime_inv[j];
      prime_inv[j] = prime_inv[j] / ( double ) ( prime ( j + 1 ) );
      t[j] = ( t[j] / prime ( j + 1 ) );
    }
  }

  delete [] prime_inv;
  delete [] t;

  return r;
}


// Function name:		
// Function purpose:	
// Parameters:			
// Return value:		
// Any other output:	