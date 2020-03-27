#ifndef __COMPONENT__
#define __COMPONENT__

class GameObject;

class Component {
	private:
	GameObject &m_owner;

	public:
	Component(GameObject &owner);
	virtual ~Component() {}
	virtual void update();
};

#endif
