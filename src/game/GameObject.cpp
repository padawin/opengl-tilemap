#include "GameObject.hpp"
#include <iostream>

void GameObject::update() {
	for (auto component : m_mComponents) {
		component.second->update();
	}
}

void GameObject::render(std::shared_ptr<Camera> camera, GameObjectRenderer *renderer) {
	render(camera, renderer, m_position, m_angle, m_scale);
}

void GameObject::render(std::shared_ptr<Camera> camera, GameObjectRenderer *renderer, glm::vec3 position, glm::vec3 angle, glm::vec3 scale) {
	for (auto component : m_mComponents) {
		component.second->render();
	}
	renderer->setPosition(position.x, position.y, position.z);
	renderer->setRotation(angle.x, angle.y, angle.z);
	renderer->setScale(scale.x, scale.y, scale.z);
	renderer->render(camera);
}

void GameObject::setPosition(float x, float y, float z) {
	m_position = glm::vec3(x, y, z);
}

glm::vec3 GameObject::getPosition() const {
	return m_position;
}

void GameObject::addComponent(std::string name, std::shared_ptr<Component> component) {
	m_mComponents[name] = component;
}

void GameObject::initComponents() {
	for (auto component : m_mComponents) {
		component.second->init();
	}
}

std::shared_ptr<Component> GameObject::getComponent(std::string name) {
	if (m_mComponents.find(name) == m_mComponents.end()) {
		return nullptr;
	}

	return m_mComponents[name];
}
