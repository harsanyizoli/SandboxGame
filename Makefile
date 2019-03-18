CXX := -c++
TARGET := SandboxGame
LDFLAGS := -lglfw -lGL -ldl
INCLUDE := -I$(shell pwd)/include/
CXXFLAGS :=
SRC	:=	src/main.cpp include/glad.c include/lodepng.cpp src/util.cpp

all:
	$(CXX) $(SRC) $(LDFLAGS) $(INCLUDE) -o $(TARGET)