#ifndef __CONFIG__
#define __CONFIG__

#include <string>

void config_setBinPath(const char* path);
std::string config_getBinPath();
void config_setScreenSize(const int width, const int height);
int config_getScreenWidth();
int config_getScreenHeight();
void config_setCameraSize(const float width, const float height);
float config_getCameraWidth();
float config_getCameraHeight();

#endif
