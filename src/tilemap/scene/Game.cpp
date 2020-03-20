#include "Game.hpp"
#include "opengl/PerspectiveCamera.hpp"
#include "game/cameraView/Follow.hpp"
#include <iostream>

std::string GameScene::getStateID() const {
	return "GameScene";
}

GameScene::GameScene(UserActions &userActions) :
	SceneState(userActions),
	m_board(Tilemap())
{
}

bool GameScene::onEnter() {
	m_reference = std::shared_ptr<GameObject>(new GameObject);
	setCameraView(std::shared_ptr<CameraView>(new FollowView(m_reference, glm::vec3(0.0f, 0.0f, 20.0f))));

	setCamera(std::shared_ptr<Camera>(new PerspectiveCamera(m_cameraView, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f)));
	return true;
}

void GameScene::update(StateMachine<SceneState> &stateMachine) {
	_update();
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}
	m_cameraView->update();
}

void GameScene::render() {
	//m_board.render(m_camera);
}
