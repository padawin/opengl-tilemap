#include "OrthoCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

OrthoCamera::OrthoCamera(std::shared_ptr<CameraView> view, float left, float right, float bottom, float top, float near, float far) :
	Camera(view),
	m_projectionMatrix(glm::ortho(left, right, bottom, top, near, far)),
	m_position(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

glm::mat4 OrthoCamera::getProjection() const {
	return m_projectionMatrix;
}
