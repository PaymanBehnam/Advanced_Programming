LIBS = -lGL -lGLU -lglut -lm -lpng -pthread
CC = g++
NAME = main
BUILD_NAME = pacman

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
all:
	$(CC) -std=c++11 -Wall *.cpp -o $(BUILD_NAME) $(LIBS)
else ifeq ($(UNAME_S), Darwin)
all:
	$(CC) -std=c++11 -Wall *.cpp -o $(BUILD_NAME) -framework OpenGL -framework GLUT -Wno-deprecated -lpng -pthread
endif

# clean build files
clean:
	rm -f *.o $(BUILD_NAME)
