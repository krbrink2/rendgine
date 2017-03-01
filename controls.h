#ifndef CONTROLS_H
#define CONTROLS_H
/*
	Compilation controls. This will handle render parameters for now.
*/

// Anti-aliasing
#define NUM_SAMPLES 		(1)
#define SQRT_NUM_SAMPLES	(1)
// Resolution
#define	HRES 				(500)	// 1366,	1920
#define VRES 				(500)	// 768,		1080
#define S 					(.0025)
// Camera
#define	ORTHO				(false)
#define EYE					Point3D(0, .15, .8)
#define LOOKAT 				Point3D(-.025, .065, 0)
//#define LOOKAT 				Point3D(-.025, .065, 0)
#define UP 					Vector3D(0, 1, 0)
#define	D 					(3)

/* Bunny:
S 		.002
EYE 	0 .15 .8
LOOKAT 	-.025, .065, 0
D 		3
*/

/* Defaults:
S 		.02
EYE		0, 1, 15
LOOKAT	0, 0, 0
D 		7
*/



#endif