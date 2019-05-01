CXX := -c++
TARGET := SandboxGame
LDFLAGS := -lglfw -lGL -ldl -lstdc++fs
INCLUDE := -I$(shell pwd)/include/
CXXFLAGS := -std=c++17
SRC	:= include/glad.c include/lodepng.cpp src/engine/*.cpp src/engine/*/*.cpp src/*.cpp

all:
	$(CXX) $(SRC) $(LDFLAGS) $(INCLUDE) -o $(TARGET) $(CXXFLAGS)