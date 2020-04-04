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
	friend class TilemapReader;
	private:
	int m_iWidth = 0;
	int m_iHeight = 0;
	std::vector<TilemapLayerData> m_vLayers = {};
	std::vector<char> m_collisionMap = {};
	std::map<std::string, char> m_mTileProperties = {};
	TilemapLayer m_layer = TilemapLayer();
	ObjectRenderer m_renderer = ObjectRenderer();

	public:
	~Tilemap() {}
	bool init(std::string filePath);
	void render(std::shared_ptr<Camera> camera);
	bool collides(float x, float y) const;
};

#endif
