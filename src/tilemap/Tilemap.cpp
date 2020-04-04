#include "Tilemap.hpp"
#include "renderers.hpp"
#include "stb_image.h"

bool Tilemap::init(std::string filePath) {
	TilemapReader reader;
	if (reader.process(filePath, this)) {
		renderer_initTilemapRenderer(&m_renderer, (float) m_iWidth, (float) m_iHeight);
		return true;
	}
	return false;
}

void Tilemap::render(std::shared_ptr<Camera> camera) {
	for (auto layer : m_vLayers) {
		m_renderer.setTextures(layer.textures);
		m_renderer.setUniform("tileAtlasWidth", layer.atlasWidth);
		m_renderer.setUniform("tileAtlasHeight", layer.atlasHeight);
		m_layer.setPosition(0.0f, 0.0f, layer.zPos);
		m_layer.render(camera, &m_renderer);
	}
}

bool Tilemap::collides(float x, float y) const {
	if (m_collisionMap.size() == 0) {
		return false;
	}
	// test if any tile within `rect` is a colliding tile
	int xCoord = (int) floor(x);
	int yCoord = m_iHeight - (int) floor(y) - 1;
	if (xCoord < 0 || xCoord >= m_iWidth || yCoord < 0 || yCoord > m_iHeight) {
		return true;
	}
	long unsigned cellIndex = (long unsigned) (yCoord * m_iWidth + xCoord);
	return m_collisionMap[cellIndex] == 1;
}
