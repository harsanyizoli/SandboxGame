CXX := -c++
TARGET := SandboxGame
LDFLAGS := -lglfw -lGL -ldl
INCLUDE := -I$(shell pwd)/include/
CXXFLAGS :=
SRC	:= include/glad.c include/lodepng.cpp src/engine/*.cpp src/graphics/*.cpp src/*.cpp

all:
	$(CXX) $(SRC) $(LDFLAGS) $(INCLUDE) -o $(TARGET)