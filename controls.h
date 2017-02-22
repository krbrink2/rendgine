#ifndef CONTROLS_H
#define CONTROLS_H
/*
	Compilation controls. This will handle render parameters for now.
*/

// Anti-aliasing
#define NUM_SAMPLES 		(1)
#define SQRT_NUM_SAMPLES	(1)
// Resolution
#define	HRES 				(5000)	// 1366,	1920
#define VRES 				(5000)	// 768,		1080
#define S 					(.025)
// Camera
#define	ORTHO				(false)
#define EYE					Point3D(0, 0, 10)
#define LOOKAT 				Point3D(-.025, .065, 0)
#define UP 					Vector3D(0, 1, 0)
#define	D 					(7)

/* Bunny:
S 		.002
EYE 	0 .15 .8
LOOKAT 	-.025, .065, 0
D 		3
*/

/* Defaults:
S 		
EYE
LOOKAT
D
*/



#endif