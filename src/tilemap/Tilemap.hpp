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
	std::map<std::string, std::vector<char>> m_mTileProperties = {};
	std::shared_ptr<TilemapLayer> m_layer = 0;
	ObjectRenderer m_renderer = ObjectRenderer();

	long _getTileIndexFromCoord(float x, float y) const;

	public:
	~Tilemap() {}
	bool init(std::string filePath);
	void render(std::shared_ptr<Camera> camera);
	bool tilePropertyEquals(std::string propertyName, float x, float y, char value);
};

#endif
