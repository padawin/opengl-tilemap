#include "Tilemap.hpp"
#include "renderers.hpp"
#include <iostream>

void Tilemap::init() {
	m_fWidth = 10.0;
	m_fHeight = 10.0;
	m_iSize = (int) (m_fWidth * m_fHeight);
	// XXX Each layer should have a renderer
	//unsigned char data[] = {
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 1, 0, 0, 2, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 3, 0, 0, 4, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	//};
	m_vLayers.push_back(TilemapLayer());
	m_vLayers[0].setPosition(-1.0f, 0.0f, 0.0f);
	//m_vLayers[0].setRenderer("texture_atlas.png", m_fWidth, m_fHeight);
	renderer_initTilemapRenderer(&m_layerRenderer, m_fWidth, m_fHeight, "texture_atlas.png");
	//m_vLayers[0].setContent(data);
}

void Tilemap::render(std::shared_ptr<Camera> camera) {
	// set tile atlas
	for (auto layer : m_vLayers) {
		layer.render(camera, &m_layerRenderer);
	}
}
