#ifndef __MOUSE__
#define __MOUSE__

#include <GLFW/glfw3.h>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
float mouse_getX();
float mouse_getY();

#endif
