#ifndef __TILEMAP__
#define __TILEMAP__

#include <string>
#include <vector>
#include "game/Camera.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "TilemapLayer.hpp"
#include "opengl/texture.hpp"

class Tilemap {
	private:
	float m_fWidth = 0.0f;
	float m_fHeight = 0.0f;
	int m_iSize = 0;
	TilemapLayer m_layer = TilemapLayer();
	ObjectRenderer m_renderer = ObjectRenderer();
	std::vector<std::map<const char*, unsigned int>> m_vLayerTextures = {};

	public:
	void init();
	void render(std::shared_ptr<Camera> camera);
};

#endif
