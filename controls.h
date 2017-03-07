#ifndef CONTROLS_H
#define CONTROLS_H

// Compilation controls. This will handle render parameters for now.

// Anti-aliasing
#define NUM_SAMPLES 		(9)
#define SQRT_NUM_SAMPLES	(3)
// Resolution
#define	HRES 				(1920)	// 1366,	1920
#define VRES 				(1080)	// 768,		1080
// Camera
#define	ORTHO				(false)
#define UP 					Vector3D(0, 1, 0)
// Acceleration structures
#define USE_BVH 			(true)

// Bunny:
#define S 		(.002)
#define	EYE 	Point3D(0, .15, .8)
#define	LOOKAT 	Point3D(-.025, .065, 0)
#define	D 		(3)


// Defaults:
// #define S 		(.02)
// #define	EYE		Point3D(0, 1, 15)
// #define LOOKAT	Point3D(0, 0, 0)
// #define D 		(7)




#endif