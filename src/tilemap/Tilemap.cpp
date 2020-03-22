#include "Tilemap.hpp"
#include "renderers.hpp"
#include <iostream>

void Tilemap::init() {
	m_fWidth = 10.0;
	m_fHeight = 10.0;
	m_iSize = (int) (m_fWidth * m_fHeight);
	const char* layerName = "test.layer";
	unsigned char data[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 2, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 3, 0, 0, 4, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	m_vLayers.push_back({
		TilemapLayer(),
		ObjectRenderer()
	});
	m_vLayers[0].layer.setPosition(-1.0f, 0.0f, 0.0f);
	renderer_initTilemapRenderer(&m_vLayers[0].renderer, m_fWidth, m_fHeight);
	texture_loadData(layerName, (int) m_fWidth, (int) m_fHeight, data);
	m_vLayers[0].renderer.addTexture("tileAtlas", texture_get("texture_atlas.png"));
	m_vLayers[0].renderer.addTexture("tilemap", texture_get(layerName));
}

void Tilemap::render(std::shared_ptr<Camera> camera) {
	// set tile atlas
	for (auto layer : m_vLayers) {
		layer.layer.render(camera, &layer.renderer);
	}
}
