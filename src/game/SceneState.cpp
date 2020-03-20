#include "SceneState.hpp"
#include <GLFW/glfw3.h>

SceneState::SceneState(UserActions &userActions) :
	m_userActions(userActions)
{
}

void SceneState::_update() {
	double currentFrame = glfwGetTime();
	m_fDeltaTime = (float) (currentFrame - m_fLastFrame);
	m_fLastFrame = currentFrame;
}

void SceneState::setCamera(std::shared_ptr<Camera> camera) {
	m_camera = camera;
}

void SceneState::setCameraView(std::shared_ptr<CameraView> cameraView) {
	m_cameraView = cameraView;
}
