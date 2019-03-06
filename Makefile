CXX := -c++
TARGET := SandboxGame
LDFLAGS := -lglfw -lGL -ldl
INCLUDE :=
CXXFLAGS :=
SRC	:=	main.cpp include/glad.c

all: 
		$(CXX) $(SRC) $(LDFLAGS) -o $(TARGET)