CC = g++
CFLAGS = -g -Wall -Werror
TARGET = rendgine

default: $(TARGET)

$(TARGET): $(TARGET).o object.o lodepng.o
	$(CC) -o $(TARGET) $(TARGET).o object.o lodepng.o $(CFLAGS)

$(TARGET).o: $(TARGET).cpp object.h
	$(CC) -c $(TARGET).cpp $(CFLAGS)

lodepng.o: lodepng.cpp lodepng.h
	$(CC) -c lodepng.cpp $(CFLAGS)

object.o: object.cpp object.h
	$(CC) -c object.cpp $(CFLAGS)

clean:
	$(RM) $(TARGET) *.o *~