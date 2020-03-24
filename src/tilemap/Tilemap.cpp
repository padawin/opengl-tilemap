#include "Tilemap.hpp"
#include "renderers.hpp"
#include "stb_image.h"

void Tilemap::init() {
	m_fWidth = 10.0;
	m_fHeight = 10.0;
	unsigned int tileAtlasWidth = 38;
	unsigned int tileAtlasHeight = 25;
	int width = (int) m_fWidth;
	int height = (int) m_fHeight;
	m_iSize = width * height;
	std::string groundLayerName = "ground.layer";
	std::string buildingsLayerName = "buildings.layer";
	GLfloat data1[] = {
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		38.0f, 38.0f, 38.0f, 40.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 76.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};
	GLfloat data2[] = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 16.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	};
	GLuint textureID;
	renderer_initTilemapRenderer(&m_renderer, m_fWidth, m_fHeight);
	m_renderer.setUniform("tileAtlasWidth", tileAtlasWidth);
	m_renderer.setUniform("tileAtlasHeight", tileAtlasHeight);

	textureID = texture_loadData(groundLayerName, width, height, data1);
	std::map<const char*, unsigned int> groundTextures = {};
	groundTextures["tileAtlas"] = texture_get("world.png");
	groundTextures["tilemap"] = textureID;

	textureID = texture_loadData(buildingsLayerName, width, height, data2);
	std::map<const char*, unsigned int> buildingsTextures = {};
	buildingsTextures["tileAtlas"] = texture_get("world.png");
	buildingsTextures["tilemap"] = textureID;

	m_vLayerTextures.push_back(groundTextures);
	m_vLayerTextures.push_back(buildingsTextures);
}

void Tilemap::render(std::shared_ptr<Camera> camera) {
	float z = 0.0f;
	for (auto textures : m_vLayerTextures) {
		m_renderer.setTextures(textures);
		m_layer.setPosition(0.0f, 0.0f, z);
		m_layer.render(camera, &m_renderer);
		z += 0.1f;
	}
}
