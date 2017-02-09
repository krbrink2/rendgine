#ifndef CONTROLS_H
#define CONTROLS_H
/*
	Compilation controls. This will handle render parameters for now.
*/

// Anti-aliasing
#define NUM_SAMPLES 		(16)
#define SQRT_NUM_SAMPLES	(4)
// Resolution
#define	HRES 				(512)	// 1366
#define VRES 				(512)	// 768
#define S 					(.075)
// Camera
#define	ORTHO				(false)
#define EYE					Point3D(0, 0, 2)
#define LOOKAT 				Point3D(0, 0, -10)
#define UP 					Vector3D(0, 10, 0)
#define	D 					(10)

// Good for perspec comparison for ortho: E 5, LOOKAT 0 0 -10, D 15



#endif