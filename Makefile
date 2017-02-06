CC = g++
CFLAGS = -g -Wall -Werror -Wextra -Wno-unused-parameter
TARGET = rendgine
OBJS = light.o lodepng.o object.o plane.o shader.o \
shaderec.o sphere.o world.o triangle.o \
Maths.o Matrix.o \
Normal.o Point3D.o Ray.o RGBColor.o Vector3D.o
HEADERS =  light.h lodepng.h object.h plane.h \
shader.h shaderec.h sphere.h triangle.h world.h \
Constants.h Maths.h Matrix.h Normal.h \
Point3D.h Ray.h RGBColor.h Vector3D.h

default: $(TARGET)

# ---- Mine ----

$(TARGET): $(TARGET).o $(OBJS)
	$(CC) -o $(TARGET) $(TARGET).o $(OBJS) $(CFLAGS)

$(TARGET).o: $(TARGET).cpp $(HEADERS)
	$(CC) -c $(TARGET).cpp $(CFLAGS)

light.o: light.cpp light.h Point3D.h RGBColor.h Vector3D.h
	$(CC) -c light.cpp $(CFLAGS)

lodepng.o: lodepng.cpp lodepng.h
	$(CC) -c lodepng.cpp $(CFLAGS)

object.o: object.cpp object.h shader.h shaderec.h Ray.h RGBColor.h
	$(CC) -c object.cpp $(CFLAGS)

plane.o: plane.cpp plane.h object.h shaderec.h Normal.h Point3D.h Ray.h Vector3D.h
	$(CC) -c plane.cpp $(CFLAGS)

shader.o: shader.cpp shader.h object.h shaderec.h world.h Ray.h RGBColor.h
	$(CC) -c shader.cpp $(CFLAGS)

shaderec.o: shaderec.cpp shaderec.h object.h Constants.h Maths.h Point3D.h Normal.h
	$(CC) -c shaderec.cpp $(CFLAGS)

sphere.o: sphere.cpp sphere.h shaderec.h object.h Normal.h Point3D.h Ray.h \
	Vector3D.h
	$(CC) -c sphere.cpp $(CFLAGS)

triangle.o: triangle.cpp triangle.h object.h Normal.h Point3D.h
	$(CC) -c triangle.cpp $(CFLAGS)

world.o: world.cpp world.h object.h plane.h shaderec.h sphere.h Point3D.h Ray.h RGBColor.h
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
	$(RM) $(TARGET) *.o *~