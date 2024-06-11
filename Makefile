#C++ compiler to use:
CXX = g++

#Compiler Flags:
# -g      - this flag adds debugging information to the executable file
# -Wall  - this flag is used to turn on most compiler warnings
# -fsanitize=leak - THis is to detect memory leaks
CXXFLAGS = -g -Wall -Wextra #-fsanitize=leak -fno-omit-frame-pointer

#Libraries to link:
# -lSDL2		-SDL2 Library (for making our  window)
# -lGL  		-OpenGL library (Fot ralking to the GPU)
# -lGLEW		-GLEW library (finds out version of OpenGL and which extensions are supported and loads their function pointers so you can easily use them.)
# -lSDL2main  	-(Not sure what this one does. keeping it here incase i need it later)
LDLIBS = -lSDL2 -lGL -lGLEW

#For storing public header files
INCLUDE = include/

DEPENDENCIES = src/shaderClass.cpp src/vboClass.cpp src/eboClass.cpp src/vaoClass.cpp

all:build run

build: 
	$(CXX) src/main.cpp $(DEPENDENCIES) $(CXXFLAGS) $(LDLIBS) -I $(INCLUDE) -o bin/main.o

run:
	./bin/main.o

clean:
	rm bin/main.o
	clear


# Install GLEW: sudo apt-get install libglew-dev
# installs- libglew2.2 libglu1-mesa-dev libopengl-dev libglew-dev 

# For dinamic linking to opengl: -lGL

#Undefined references to gl functions probably mean you did not link libGL (-lGL). 
#Undefined references to glut functions probably mean you did not link GLUT (-lglut). 
#Undefined references to GLEW functions probably mean you did not link GLEW (-lGLEW). 

# -lglfw

#https://stackoverflow.com/a/2481326