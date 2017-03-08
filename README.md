Kyle Brinker
Rendgine ray tracer

To build, run the Makefile. The project uses no external libraries other than std.

Scene parameters are found as macros in controls.h. The binary rendres the scene into image.png. 

To render an animation, change ANIMATE to "true" in controls.h. The binary will produce a series of frames: a000.png, a001.png. animates.sh produces an mp4 file from these.

