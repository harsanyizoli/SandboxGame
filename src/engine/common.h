#ifndef COMMON_H
#define COMMON_H

#include "glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unistd.h>

//#define ERROR(msg) fprintf(stderr, "ERROR: %s:%d: ", __FILE__, __LINE__); fprintf(stderr, "%s\n", msg);
#define ERROR(msg) std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << " " << msg << std::endl;

#endif