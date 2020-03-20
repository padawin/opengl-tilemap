#include "config.hpp"

std::string binPath = "";

void config_setBinPath(const char* path) {
	binPath = path;
}

std::string config_getBinPath() {
	return binPath;
}
