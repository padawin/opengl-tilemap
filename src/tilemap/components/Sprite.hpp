#ifndef __COMPONENT_SPRITE__
#define __COMPONENT_SPRITE__

#include "game/Component.hpp"
#include "opengl/ObjectRenderer.hpp"
#include <string>

class SpriteComponent : public Component {
	private:
	std::shared_ptr<ObjectRenderer> m_renderer;
	unsigned int m_iTexture;
	float m_fWidth;
	float m_fHeight;
	unsigned int m_iX;
	unsigned int m_iY;
	unsigned int m_iSheetWidth;
	unsigned int m_iSheetHeight;

	public:
	SpriteComponent(
		std::shared_ptr<GameObject> owner,
		std::shared_ptr<ObjectRenderer> renderer,
		unsigned int textureID,
		float width, float height,
		unsigned int x, unsigned int y,
		unsigned int sheetWidth, unsigned int sheetHeight
		);
	void render();
};

#endif
