#include "Game.hpp"
#include "tilemap/components/Animation.hpp"
#include "tilemap/components/Movements.hpp"
#include "tilemap/Animation.hpp"
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
	std::string filePath = config_getBinPath() + "/../resources/levels/level1.lvl";
	m_board.init(filePath);
	renderer_initSpriteRenderer(&m_spriteRenderer);
	m_reference = std::shared_ptr<GameObject>(new GameObject);
	//m_animationCollection.loadAnimations(config_getBinPath() + "/../resources/animations.dat");
	auto walkUp = m_animationCollection.createAnimation("walkUp", true, 0.3f);
	auto walkDown = m_animationCollection.createAnimation("walkDown", true, 0.3f);
	auto walkLeft = m_animationCollection.createAnimation("walkLeft", true, 0.3f);
	auto walkRight = m_animationCollection.createAnimation("walkRight", true, 0.3f);
	walkUp->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 1, 3, 12, 8);
	walkUp->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 2, 3, 12, 8);
	walkUp->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 1, 3, 12, 8);
	walkUp->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 0, 3, 12, 8);
	walkDown->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 1, 0, 12, 8);
	walkDown->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 2, 0, 12, 8);
	walkDown->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 1, 0, 12, 8);
	walkDown->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 0, 0, 12, 8);
	walkLeft->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 1, 1, 12, 8);
	walkLeft->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 2, 1, 12, 8);
	walkLeft->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 1, 1, 12, 8);
	walkLeft->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 0, 1, 12, 8);
	walkRight->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 1, 2, 12, 8);
	walkRight->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 2, 2, 12, 8);
	walkRight->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 1, 2, 12, 8);
	walkRight->addFrame(texture_get("chara6.png"), 1.0f, 72.0f / 52.0f, 0, 2, 12, 8);
	auto animationComponent = std::shared_ptr<AnimationComponent>(new AnimationComponent(
		m_reference, std::shared_ptr<ObjectRenderer>(&m_spriteRenderer)
	));
	animationComponent->addAnimation("walkUp", walkUp);
	animationComponent->addAnimation("walkDown", walkDown);
	animationComponent->addAnimation("walkLeft", walkLeft);
	animationComponent->addAnimation("walkRight", walkRight);
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
