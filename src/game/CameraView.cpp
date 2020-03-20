#include "CameraView.hpp"

void CameraView::setPosition(glm::vec3 position) {
	m_position = position;
}

glm::vec3 CameraView::getPosition() const {
	return m_position;
}

glm::mat4 CameraView::get() const {
	return m_view;
}
