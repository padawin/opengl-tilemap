#include "mouse.hpp"

float lastX = 0.0f;
float lastY = 0.0f;
float offsetX = 0.0f;
float offsetY = 0.0f;
bool firstMouse = true;

void mouse_callback(GLFWwindow* window __attribute__((unused)), double xpos, double ypos) {
    if (firstMouse) {
        lastX = (float) xpos;
        lastY = (float) ypos;
        firstMouse = false;
    }

    offsetX = (float) (xpos - lastX);
    offsetY = (float) (lastY - ypos); // reversed since y-coordinates go from bottom to top
    lastX = (float) xpos;
    lastY = (float) ypos;

    float sensitivity = 0.1f; // change this value to your liking
    offsetX *= sensitivity;
    offsetY *= sensitivity;
}

float mouse_getX() {
	return lastX;
}

float mouse_getY() {
	return lastY;
}
