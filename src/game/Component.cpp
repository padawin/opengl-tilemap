#include "Component.hpp"
#include "GameObject.hpp"

Component::Component(GameObject &owner) :
	m_owner(owner) {
}

void Component::update() {
}
