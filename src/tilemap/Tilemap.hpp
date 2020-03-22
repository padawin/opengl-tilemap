#ifndef __TILEMAP__
#define __TILEMAP__

#include <string>
#include <vector>
#include "game/Camera.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "TilemapLayer.hpp"
#include "opengl/texture.hpp"

typedef struct {
	TilemapLayer layer;
	ObjectRenderer renderer;
} Layer;

class Tilemap {
	private:
	float m_fWidth = 0.0f;
	float m_fHeight = 0.0f;
	int m_iSize = 0;
	std::vector<Layer> m_vLayers = {};
	ObjectRenderer m_layerRenderer = ObjectRenderer();

	public:
	void init();
	void render(std::shared_ptr<Camera> camera);
};

#endif
