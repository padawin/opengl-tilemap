#include "Renderer.hpp"


RendererComponent::RendererComponent(std::shared_ptr<GameObject> owner, std::shared_ptr<ObjectRenderer> renderer) :
	Component(owner),
	m_renderer(renderer)
{
}

void RendererComponent::render(std::shared_ptr<Camera> camera) {
	glm::vec3 position;
	glm::vec3 angle;
	glm::vec3 scale;
	position = m_owner->getPosition();
	angle = m_owner->getRotation();
	scale = m_owner->getScale();
	m_renderer->setPosition(position.x, position.y, position.z);
	m_renderer->setRotation(angle.x, angle.y, angle.z);
	m_renderer->setScale(scale.x, scale.y, scale.z);
	m_renderer->render(camera);
}
