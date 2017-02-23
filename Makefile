CC = g++
CFLAGS = -g -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable
TARGET = rendgine
UTILS = Constants.h Maths.h Matrix.h Normal.h \
Point3D.h Ray.h RGBColor.h Vector3D.h
OBJS = ashikhmin.o dirlight.o light.o lodepng.o mesh.o object.o plane.o pointlight.o shader.o \
shaderec.o sphere.o world.o triangle.o \
Maths.o Matrix.o \
Normal.o Point3D.o Ray.o RGBColor.o Vector3D.o
HEADERS =  ashikhmin.h dirlight.h controls.h light.h lodepng.h mesh.h object.h plane.h pointlight.h \
shader.h shaderec.h sphere.h triangle.h world.h \
Constants.h Maths.h Matrix.h Normal.h \
Point3D.h Ray.h RGBColor.h Vector3D.h

default: $(TARGET)

# ---- Mine ----

$(TARGET): rendgine.o $(OBJS)
	$(CC) -o $(TARGET) rendgine.o $(OBJS) $(CFLAGS)

rendgine.o: rendgine.cpp $(HEADERS)
	$(CC) -c rendgine.cpp $(CFLAGS)

ashikhmin.o: ashikhmin.cpp ashikhmin.h shader.h world.h shaderec.h $(UTILS)
	$(CC) -c ashikhmin.cpp $(CFLAGS)

dirlight.o: dirlight.cpp dirlight.h light.h
	$(CC) -c dirlight.cpp $(CFLAGS)

light.o: light.cpp light.h shaderec.h utils.h
	$(CC) -c light.cpp $(CFLAGS)

lodepng.o: lodepng.cpp lodepng.h
	$(CC) -c lodepng.cpp $(CFLAGS)

mesh.o: mesh.cpp mesh.h object.h utils.h triangle.h
	$(CC) -c mesh.cpp $(CFLAGS)

object.o: object.cpp object.h utils.h shader.h shaderec.h utils.h
	$(CC) -c object.cpp $(CFLAGS)

plane.o: plane.cpp plane.h object.h shaderec.h utils.h
	$(CC) -c plane.cpp $(CFLAGS)

pointlight.o: pointlight.cpp pointlight.h light.h
	$(CC) -c pointlight.cpp $(CFLAGS)

shader.o: shader.cpp shader.h object.h shaderec.h world.h utils.h
	$(CC) -c shader.cpp $(CFLAGS)

shaderec.o: shaderec.cpp shaderec.h object.h utils.h
	$(CC) -c shaderec.cpp $(CFLAGS)

sphere.o: sphere.cpp sphere.h shaderec.h object.h utils.h
	$(CC) -c sphere.cpp $(CFLAGS)

triangle.o: triangle.cpp triangle.h object.h utils.h
	$(CC) -c triangle.cpp $(CFLAGS)

world.o: world.cpp world.h controls.h dirlight.h object.h plane.h pointlight.h shaderec.h sphere.h triangle.h utils.h
	$(CC) -c world.cpp $(CFLAGS)

# ---- rtftgu ----

Maths.o: Maths.cpp Maths.h Constants.h RGBColor.h
	$(CC) -c Maths.cpp $(CFLAGS)

Matrix.o: Matrix.cpp Matrix.h
	$(CC) -c Matrix.cpp $(CFLAGS)

Normal.o: Normal.cpp Normal.h Matrix.h Vector3D.h Point3D.h
	$(CC) -c Normal.cpp $(CFLAGS)

Point3D.o: Point3D.cpp Point3D.h Matrix.h Vector3D.h
	$(CC) -c Point3D.cpp $(CFLAGS)

Ray.o: Ray.cpp Ray.h Point3D.h Vector3D.h
	$(CC) -c Ray.cpp $(CFLAGS)

RGBColor.o: RGBColor.cpp RGBColor.h
	$(CC) -c RGBColor.cpp $(CFLAGS)

Vector3D.o: Vector3D.cpp Vector3D.h Normal.h Point3D.h
	$(CC) -c Vector3D.cpp $(CFLAGS)


clean:
	$(RM) $(TARGET) rendgine *.o *~