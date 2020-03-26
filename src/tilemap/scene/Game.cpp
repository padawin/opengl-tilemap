#include "Game.hpp"
#include "game/config.hpp"
#include "opengl/OrthoCamera.hpp"
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
	std::string filePath = config_getBinPath() + "/../resources/levels/level1.lvl";
	m_board.init(filePath);
	m_reference = std::shared_ptr<GameObject>(new GameObject);
	m_reference->setPosition(-1.0f, 1.0f, 1.0f);
	setCameraView(std::shared_ptr<CameraView>(new FollowView(m_reference, glm::vec3(0.0f, 0.0f, 15.0f))));

	setCamera(std::shared_ptr<Camera>(new OrthoCamera(m_cameraView, 0.0f, 12.0f, 0.0f, 8.0f, 0.1f, 100.0f)));
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
	m_board.render(m_camera);
}
