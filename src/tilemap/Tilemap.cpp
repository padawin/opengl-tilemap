#include "Tilemap.hpp"
#include "renderers.hpp"
#include "stb_image.h"

void Tilemap::init() {
	m_fWidth = 10.0;
	m_fHeight = 10.0;
	int width = (int) m_fWidth;
	int height = (int) m_fHeight;
	unsigned int tileAtlasWidth = 38;
	unsigned int tileAtlasHeight = 25;
	m_iSize = width * height;
	const char* layerName1 = "ground.layer";
	const char* layerName2 = "buildings.layer";
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
	ObjectRenderer groundRenderer, buildingsRenderer;

	renderer_initTilemapRenderer(&groundRenderer, m_fWidth, m_fHeight);
	texture_loadData(layerName1, width, height, data1);
	groundRenderer.setUniform("tileAtlasWidth", tileAtlasWidth);
	groundRenderer.setUniform("tileAtlasHeight", tileAtlasHeight);

	renderer_initTilemapRenderer(&buildingsRenderer, m_fWidth, m_fHeight);
	texture_loadData(layerName2, width, height, data2);
	buildingsRenderer.setUniform("tileAtlasWidth", tileAtlasWidth);
	buildingsRenderer.setUniform("tileAtlasHeight", tileAtlasHeight);

	m_vRenderer.push_back(groundRenderer);
	m_vRenderer.push_back(buildingsRenderer);
}

void Tilemap::render(std::shared_ptr<Camera> camera) {
	const char* layerName1 = "ground.layer";
	const char* layerName2 = "buildings.layer";
	unsigned int worldTexture = texture_get("world.png");
	std::map<const char*, unsigned int> textures1 = {};
	textures1["tileAtlas"] = worldTexture;
	textures1["tilemap"] = texture_get(layerName1);
	std::map<const char*, unsigned int> textures2 = {};
	textures2["tileAtlas"] = worldTexture;
	textures2["tilemap"] = texture_get(layerName2);

	m_vRenderer[0].setTextures(textures1);
	m_layer.setPosition(0.0f, 0.0f, 0.0f);
	m_layer.render(camera, &m_vRenderer[0]);
	m_vRenderer[1].setTextures(textures2);
	m_layer.setPosition(0.0f, 0.0f, 1.0f);
	m_layer.render(camera, &m_vRenderer[1]);
}
