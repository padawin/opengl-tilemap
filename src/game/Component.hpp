#ifndef __COMPONENT__
#define __COMPONENT__

#include <memory>

class GameObject;

class Component {
	private:
	std::shared_ptr<GameObject> m_owner;

	public:
	Component(std::shared_ptr<GameObject> owner);
	virtual ~Component() {}
	virtual void update();
};

#endif
