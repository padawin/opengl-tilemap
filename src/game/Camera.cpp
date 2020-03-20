#include "Camera.hpp"

Camera::Camera(std::shared_ptr<CameraView> view) : m_view(view) {
}

glm::mat4 Camera::getView() const {
	return m_view->get();
}
