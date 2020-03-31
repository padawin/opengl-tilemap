#ifndef __COMPONENT_ANIMATION__
#define __COMPONENT_ANIMATION__

#include <string>
#include <memory>
#include <map>
#include "game/Component.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "tilemap/Animation.hpp"

class AnimationComponent : public Component {
	private:
	std::shared_ptr<ObjectRenderer> m_renderer;
	std::map<std::string, std::shared_ptr<Animation>> m_mAnimations = {};
	std::string m_sCurrentAnimation = "";

	public:
	AnimationComponent(std::shared_ptr<GameObject> owner, std::shared_ptr<ObjectRenderer> renderer);
	void addAnimation(std::string name, std::shared_ptr<Animation> animation);
	void start(std::string name);
	void stop();
	void update();
	void render();
};

#endif
