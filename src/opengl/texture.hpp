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
GLuint texture_init(std::string name, int width, int height);
bool texture_addData(std::string name, unsigned char* data, int destX, int destY, int width, int height);
GLuint texture_loadData(std::string name, int width, int height, GLfloat* data);
Texture* texture_get(const char* textureName);
GLuint texture_getID(const char* textureName);

#endif
