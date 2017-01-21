CC = g++
CFLAGS = -g -Wall -Werror
TARGET = rendgine
OBJS = object.o lodepng.o sphere.o Maths.o Matrix.o Normal.o Point3D.o Ray.o RGBColor.o Vector3D.o
HEADERS = object.h lodepng.h sphere.h Constants.h Maths.h Matrix.h Normal.h Point3D.h Ray.h RGBColor.h Vector3D.h

default: $(TARGET)

$(TARGET): $(TARGET).o $(OBJS)
	$(CC) -o $(TARGET) $(TARGET).o $(OBJS) $(CFLAGS)

$(TARGET).o: $(TARGET).cpp $(HEADERS)
	$(CC) -c $(TARGET).cpp $(CFLAGS)

lodepng.o: lodepng.cpp lodepng.h
	$(CC) -c lodepng.cpp $(CFLAGS)

object.o: object.cpp object.h
	$(CC) -c object.cpp $(CFLAGS)

sphere.o: sphere.cpp sphere.h object.h
	$(CC) -c sphere.cpp $(CFLAGS)


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