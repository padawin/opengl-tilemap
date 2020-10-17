#ifndef __COMPONENT_TEXT__
#define __COMPONENT_TEXT__

#include "opengl/components/Renderer.hpp"

class TextComponent : public RendererComponent {
	private:
	GLuint m_iAtlasTextureID = 0;
	bool m_bIsUI = false;

	public:
	TextComponent(std::shared_ptr<GameObject> owner, std::string text, std::string font, unsigned int size);
	void render(std::shared_ptr<Camera> camera);
	void setUI();
};

#endif
