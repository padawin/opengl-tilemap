#include "Game.hpp"
#include "tilemap/components/Animation.hpp"
#include "tilemap/components/Movements.hpp"
#include "tilemap/Animation.hpp"
#include "tilemap/AnimationReader.hpp"
#include "tilemap/renderers.hpp"
#include "opengl/texture.hpp"
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
	std::string levelFilePath = config_getBinPath() + "/../resources/levels/level1.lvl";
	std::string animationsFilePath = config_getBinPath() + "/../resources/animations.dat";
	if (!m_board.init(levelFilePath)) {
		return false;
	}
	renderer_initSpriteRenderer(&m_spriteRenderer);
	m_reference = std::shared_ptr<GameObject>(new GameObject);
	AnimationReader reader;
	if (!reader.process(animationsFilePath, &m_animationCollection)) {
		return false;
	}
	auto animationComponent = std::shared_ptr<AnimationComponent>(new AnimationComponent(
		m_reference, std::shared_ptr<ObjectRenderer>(&m_spriteRenderer)
	));
	animationComponent->addAnimation("walkUp", m_animationCollection.getAnimation("walkUp"));
	animationComponent->addAnimation("walkDown", m_animationCollection.getAnimation("walkDown"));
	animationComponent->addAnimation("walkLeft", m_animationCollection.getAnimation("walkLeft"));
	animationComponent->addAnimation("walkRight", m_animationCollection.getAnimation("walkRight"));
	float playerSpeed = 0.05f;
	auto movementsComponent = std::shared_ptr<MovementsComponent>(new MovementsComponent(
		m_reference, m_userActions, playerSpeed
	));
	m_reference->addComponent("animation", animationComponent);
	m_reference->addComponent("movements", movementsComponent);
	m_reference->initComponents();
	m_reference->setPosition(3.0f, 4.0f, 1.0f);
	setCameraView(std::shared_ptr<CameraView>(new FollowView(m_reference, glm::vec3(0.0f, 0.0f, 15.0f))));

	setCamera(std::shared_ptr<Camera>(new OrthoCamera(m_cameraView, -6.0f, 6.0f, -4.0f, 4.0f, 0.1f, 100.0f)));
	return true;
}

void GameScene::update(StateMachine<SceneState> &stateMachine) {
	_update();
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}
	m_cameraView->update();
	m_reference->update();
}

void GameScene::render() {
	m_board.render(m_camera);
	m_reference->render(m_camera, &m_spriteRenderer);
}
