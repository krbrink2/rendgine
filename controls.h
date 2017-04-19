#ifndef CONTROLS_H
#define CONTROLS_H

// Compilation controls. This will handle render parameters for now.

// Anti-aliasing
#define NUM_SAMPLES 		(1)
#define SQRT_NUM_SAMPLES	(1)
// Resolution
#define	HRES 				(500)	// 1366,	1920
#define VRES 				(700)	// 768,		1080
// Camera
#define	ORTHO				(false)
#define UP 					Vector3D(0, 1, 0)
// Acceleration structures
#define USE_BVH 			(true)
#define BENCHMARK_NUM_SPHERES	(1000)
// Animation
#define ANIMATE				(false)
#define NUM_FRAMES			(10)
#define ANIMATION_VECTOR	Vector3D(.004, -.0005, 0)
// Rendering
#define MAX_BOUNCES 				(2)
#define AREALIGHT_NUM_SAMPLES 		(8)
#define GLOSSY_NUM_SAMPLES 			(8)

// Bunny:
// #define S 		(.002)
// #define	EYE 	Point3D(0, .3, .8)
// #define	LOOKAT 	Point3D(-.025, .065, 0)
// #define	D 		(3)

// Defaults:
#define S 		(.02)
#define	EYE		Point3D(2, 3, 10)
// #define	EYE		Point3D(15, 4, 0)
#define LOOKAT	Point3D(0, 0, 0)
#define D 		(7)

// Many spheres:
// #define S 		(.02)
// #define	EYE		Point3D(-1, 1, 1)
// #define LOOKAT	Point3D(.5, .5, .5)
// #define D 		(14)




#endif
