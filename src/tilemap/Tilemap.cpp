#include "Tilemap.hpp"
#include "renderers.hpp"
#include "stb_image.h"

void Tilemap::init(std::string filePath) {
	TilemapReader reader;
	if (reader.process(filePath, m_layers)) {
		renderer_initTilemapRenderer(&m_renderer, (float) m_layers.width, (float) m_layers.height);
	}
}

void Tilemap::render(std::shared_ptr<Camera> camera) {
	float z = 0.0f;
	for (auto layer : m_layers.layers) {
		m_renderer.setTextures(layer.textures);
		m_renderer.setUniform("tileAtlasWidth", layer.atlasWidth);
		m_renderer.setUniform("tileAtlasHeight", layer.atlasHeight);
		m_layer.setPosition(0.0f, 0.0f, z);
		m_layer.render(camera, &m_renderer);
		z += 0.1f;
	}
}
