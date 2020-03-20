#include "Follow.hpp"
#include <glm/gtc/matrix_transform.hpp>

FollowView::FollowView(std::shared_ptr<GameObject> target, glm::vec3 positionFromTarget) :
	m_target(target),
	m_positionFromTarget(positionFromTarget)
{
}

void FollowView::update() {
	m_position = m_target->getPosition() + m_positionFromTarget;

	glm::vec3 targetPosition = m_target->getPosition();
	glm::vec3 cameraDirection = glm::normalize(m_position - targetPosition);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, right);
	m_view = glm::lookAt(m_position, targetPosition, cameraUp);
}
