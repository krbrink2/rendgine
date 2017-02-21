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
#define S 					(.002)
// Camera
#define	ORTHO				(false)
#define EYE					Point3D(0, .15, .8)
#define LOOKAT 				Point3D(-.025, .065, 0)
#define UP 					Vector3D(0, 1, 0)
#define	D 					(3)

// Good for perspec comparison for ortho: E 5, LOOKAT 0 0 -10, D 15



#endif