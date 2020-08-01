#ifndef __RENDERER_COMPONENT__
#define __RENDERER_COMPONENT__

#include "game/GameObject.hpp"
#include "game/Component.hpp"
#include "opengl/ObjectRenderer.hpp"

class RendererComponent : public Component {
	protected:
	std::shared_ptr<ObjectRenderer> m_renderer;

	public:
	RendererComponent(std::shared_ptr<GameObject> owner, std::shared_ptr<ObjectRenderer> renderer);
	~RendererComponent() {}
	void render(std::shared_ptr<Camera> camera);
};

#endif
