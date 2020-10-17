#ifndef __COMPONENT__
#define __COMPONENT__

#include <memory>
#include "Camera.hpp"

class GameObject;

class Component {
	protected:
	std::shared_ptr<GameObject> m_owner;

	public:
	Component(std::shared_ptr<GameObject> owner);
	virtual ~Component() {}
	virtual void init();
	virtual void update();
	virtual void render(std::shared_ptr<Camera> camera);
};

#endif
