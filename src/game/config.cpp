#include "config.hpp"

std::string binPath = "";
int screenWidth = 1;
int screenHeight = 1;

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
