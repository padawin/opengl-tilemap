#ifndef __TILEMAP__
#define __TILEMAP__

#include <string>
#include <vector>
#include "game/Camera.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "TilemapLayer.hpp"
#include "TilemapReader.hpp"
#include "opengl/texture.hpp"

class Tilemap {
	private:
	TilemapLayer m_layer = TilemapLayer();
	ObjectRenderer m_renderer = ObjectRenderer();
	TilemapFileFormat m_layers = TilemapFileFormat();

	public:
	void init(std::string filePath);
	void render(std::shared_ptr<Camera> camera);
};

#endif
