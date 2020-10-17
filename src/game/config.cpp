#include "config.hpp"

std::string binPath = "";
int screenWidth = 1;
int screenHeight = 1;
float cameraWidth = 1.0f;
float cameraHeight = 1.0f;

void config_setBinPath(const char* path) {
	binPath = path;
}

std::string config_getBinPath() {
	return binPath;
}

void config_setScreenSize(const int width, const int height) {
	screenWidth = width;
	screenHeight = height;
}

int config_getScreenWidth() {
	return screenWidth;
}
int config_getScreenHeight() {
	return screenHeight;
}

void config_setCameraSize(const float width, const float height) {
	cameraWidth = width;
	cameraHeight = height;
}

float config_getCameraWidth() {
	return cameraWidth;
}
float config_getCameraHeight() {
	return cameraHeight;
}
