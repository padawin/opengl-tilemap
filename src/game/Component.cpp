#include "Component.hpp"
#include "GameObject.hpp"

Component::Component(std::shared_ptr<GameObject> owner) :
	m_owner(owner) {
}

void Component::update() {
}

void Component::render() {
}
