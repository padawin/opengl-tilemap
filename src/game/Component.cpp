#include "Component.hpp"
#include "GameObject.hpp"

Component::Component(std::shared_ptr<GameObject> owner) :
	m_owner(owner) {
}

void Component::init() {
}

void Component::update() {
}

void Component::render(std::shared_ptr<Camera> camera __attribute__((unused))) {
}
