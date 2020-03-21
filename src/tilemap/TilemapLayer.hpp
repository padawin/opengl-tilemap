#ifndef __TILEMAP_LAYER__
#define __TILEMAP_LAYER__

#include <string>
#include "opengl/texture.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "game/GameObject.hpp"

class TilemapLayer : public GameObject {
	private:
	Texture m_texture = Texture();
	//ObjectRenderer m_renderer = ObjectRenderer();

	public:
	//void setRenderer(std::string tileset, float width, float height);
	void setContent(unsigned char* content);
	//ObjectRenderer* getRenderer();
};

#endif
