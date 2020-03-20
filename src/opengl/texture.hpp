#ifndef __TEXTURE__
#define __TEXTURE__

#include <string>
#include "glad/glad.h"

typedef struct {
	int width = 0;
	int height = 0;
	int channelsCount = 0;
	unsigned int textureID = 0;
} Texture;

bool texture_loadAll();
GLuint texture_get(const char* textureName);

#endif
