CC=g++
CFLAGS=-g --std=c++14
LDFLAGS=-framework GLUT -framework OpenGL -lpng
IFLAGS=-Isrc/
SOURCES=src/main.cpp src/world/*.cpp src/controls/*cpp src/geometry/*.cpp src/graphics/*.cpp src/utils/*.cpp
EXECUTABLE=test_build

all: $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
