CXX := -c++
TARGET := SandboxGame
LDFLAGS := -lglfw -lGL -ldl
INCLUDE := -I/home/d/Documents/SandboxGL/include
CXXFLAGS :=
SRC	:=	src/main.cpp include/glad.c include/lodepng.cpp src/util.cpp

all: 
		$(CXX) $(SRC) $(LDFLAGS) -o $(TARGET) $(INCLUDE)