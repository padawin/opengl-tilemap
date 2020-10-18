#include "SceneState.hpp"
#include <GLFW/glfw3.h>

SceneState::SceneState(UserActions &userActions) :
	m_userActions(userActions)
{
}

void SceneState::_preUpdate() {
	double currentFrame = glfwGetTime();
	m_fDeltaTime = (float) (currentFrame - m_fLastFrame);
	m_fLastFrame = currentFrame;
}

void SceneState::_update() {
	if (m_cameraView != nullptr) {
		m_cameraView->update();
	}
	if (m_UICameraView != nullptr) {
		m_UICameraView->update();
	}
}

void SceneState::setUICamera(std::shared_ptr<Camera> camera) {
	m_UICamera = camera;
}

void SceneState::setCamera(std::shared_ptr<Camera> camera) {
	m_camera = camera;
}

void SceneState::setUICameraView(std::shared_ptr<CameraView> cameraView) {
	m_UICameraView = cameraView;
}

void SceneState::setCameraView(std::shared_ptr<CameraView> cameraView) {
	m_cameraView = cameraView;
}
