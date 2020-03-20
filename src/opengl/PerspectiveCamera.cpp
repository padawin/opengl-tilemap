#include "PerspectiveCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(std::shared_ptr<CameraView> view, float angleDegrees, float screenRatio, float near, float far) :
	Camera(view),
	m_projectionMatrix(glm::perspective(glm::radians(angleDegrees), screenRatio, near, far)),
	m_position(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

glm::mat4 PerspectiveCamera::getProjection() const {
	return m_projectionMatrix;
}
