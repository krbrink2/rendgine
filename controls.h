#ifndef CONTROLS_H
#define CONTROLS_H
/*
	Compilation controls. This will handle render parameters for now.
*/

// Anti-aliasing
#define NUM_SAMPLES 		(1)
#define SQRT_NUM_SAMPLES	(1)
// Resolution
#define	HRES 				(200)	// 1366,	1920
#define VRES 				(200)	// 768,		1080
#define S 					(.02)
// Camera
#define	ORTHO				(false)
#define EYE					Point3D(0, 0, 3)
#define LOOKAT 				Point3D(0, 0, 0)
#define UP 					Vector3D(0, 10, 0)
#define	D 					(10)

// Good for perspec comparison for ortho: E 5, LOOKAT 0 0 -10, D 15



#endif