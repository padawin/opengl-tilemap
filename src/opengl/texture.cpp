#include "texture.hpp"
#include "game/config.hpp"
#include "game/utils.hpp"
#include <map>
#include <dirent.h> // for DIR
#include <iostream>
#include "glad/glad.h"
#include "stb_image.h"

const char* resourcesDir = "/../resources/";

std::map<std::string, Texture> textures = {};

bool _loadTexture(std::string name, std::string path);

bool texture_loadAll() {
	std::string baseDir = config_getBinPath() + resourcesDir;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(baseDir.c_str())) == NULL) {
		std::cerr << "Could not open resources directory: " << baseDir << std::endl;
		return false;
	}

	bool res = true;
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
		res &= loaded;
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
	texture_loadInGPU(t, data);
	textures[name] = t;
	stbi_image_free(data);
	return true;
}

void texture_loadInGPU(Texture &t, unsigned char* data) {
	glGenTextures(1, &t.textureID);
	glBindTexture(GL_TEXTURE_2D, t.textureID);
	// set the texture wrapping/filtering options (on the currently bound
	// texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t.width, t.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint texture_get(const char* textureName) {
	if (textures.find(textureName) == textures.end()) {
		return 0;
	}
	return textures[textureName].textureID;
}
