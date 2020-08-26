#include "texture.hpp"
#include "game/config.hpp"
#include "game/utils.hpp"
#include <map>
#include <dirent.h> // for DIR
#include <iostream>
#include "glad/glad.h"
#include "stb_image.h"

const char* resourcesDir = "/../resources/textures/";

std::map<std::string, Texture> textures = {};

bool _loadTexture(std::string name, std::string path);
void _loadInGPU(Texture &t, unsigned char* data);

bool texture_loadAll() {
	std::string baseDir = config_getBinPath() + resourcesDir;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(baseDir.c_str())) == NULL) {
		std::cerr << "Could not open resources directory: " << baseDir << std::endl;
		return false;
	}

	while ((ent = readdir(dir)) != NULL) {
		std::string fname = ent->d_name,
		            fullPath = baseDir + fname;
		if (!utils_isRegularFile(fullPath.c_str())) {
			continue;
		}
		bool loaded = _loadTexture(fname, fullPath);
		if (loaded) {
			std::cout << "Texture loaded: " << fullPath << std::endl;
		}
		else {
			std::cerr << "Failed to load texture: " << fullPath << std::endl;
		}
	}
	closedir(dir);
	return true;
}

bool _loadTexture(std::string name, std::string path) {
	Texture t;
	// load and generate the texture
	unsigned char* data = stbi_load(path.c_str(), &t.width, &t.height, &t.channelsCount, 0);
	if (!data) {
		return false;
	}
	glGenTextures(1, &t.textureID);
	glBindTexture(GL_TEXTURE_2D, t.textureID);
	// set the texture wrapping/filtering options (on the currently bound
	// texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t.width, t.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	textures[name] = t;
	stbi_image_free(data);
	return true;
}

GLuint texture_init(std::string name, int width, int height) {
	Texture t;
	t.width = width;
	t.height = height;
	glGenTextures(1, &t.textureID);
	glBindTexture(GL_TEXTURE_2D, t.textureID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8, t.width, t.height);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	textures[name] = t;
	return t.textureID;
}

bool texture_addData(std::string name, unsigned char* data, int destX, int destY, int width, int height) {
	auto iter = textures.find(name);
	if (iter == textures.end()) {
		return false;
	}
	Texture t = iter->second;
	glBindTexture(GL_TEXTURE_2D, t.textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, destX, destY, width, height, GL_RED, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

GLuint texture_loadData(std::string name, int width, int height, GLfloat* data) {
	Texture t;
	t.width = width;
	t.height = height;
	glGenTextures(1, &t.textureID);
	glBindTexture(GL_TEXTURE_2D, t.textureID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED, GL_FLOAT, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	textures[name] = t;
	return t.textureID;
}

Texture* texture_get(const char* textureName) {
	if (textures.find(textureName) == textures.end()) {
		return 0;
	}
	return &textures[textureName];
}

GLuint texture_getID(const char* textureName) {
	if (textures.find(textureName) == textures.end()) {
		return 0;
	}
	return textures[textureName].textureID;
}
