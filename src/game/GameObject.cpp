#include "GameObject.hpp"
#include <iostream>

void GameObject::update() {
	for (auto component : m_mComponents) {
		component.second->update();
	}
}

void GameObject::render(std::shared_ptr<Camera> camera) {
	for (auto component : m_mComponents) {
		component.second->render(camera);
	}
}

void GameObject::setPosition(float x, float y, float z) {
	m_position = glm::vec3(x, y, z);
}

glm::vec3 GameObject::getPosition() const {
	return m_position;
}

glm::vec3 GameObject::getRotation() const {
	return m_angle;
}

glm::vec3 GameObject::getScale() const {
	return m_scale;
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
