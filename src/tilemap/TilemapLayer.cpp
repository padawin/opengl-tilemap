#include "TilemapLayer.hpp"
#include "renderers.hpp"

//void TilemapLayer::setRenderer(std::string tileset, float width, float height) {
//	renderer_initTilemapRenderer(&m_renderer, width, height, tileset);
//}

void TilemapLayer::setContent(unsigned char* content) {
	texture_loadInGPU(m_texture, content);
	//m_renderer.addTexture(m_texture.textureID);
}

//ObjectRenderer* TilemapLayer::getRenderer() {
//	return &m_renderer;
//}
