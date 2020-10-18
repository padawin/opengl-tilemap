#include "Game.hpp"
#include "opengl/components/Text.hpp"
#include "tilemap/components/Animation.hpp"
#include "tilemap/components/Movements.hpp"
#include "tilemap/components/Collision.hpp"
#include "tilemap/Animation.hpp"
#include "tilemap/AnimationReader.hpp"
#include "tilemap/renderers.hpp"
#include "opengl/texture.hpp"
#include "game/config.hpp"
#include "opengl/OrthoCamera.hpp"
#include "game/config.hpp"
#include "game/cameraView/Follow.hpp"
#include "game/cameraView/Fixed.hpp"

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
	animationComponent->addAnimation("walkLeft", m_animationCollection.getAnimation("walkLeft"));
	animationComponent->addAnimation("walkRight", m_animationCollection.getAnimation("walkRight"));
	animationComponent->addAnimation("walkDown", m_animationCollection.getAnimation("walkDown"));
	float playerSpeed = 0.05f;
	auto movementsComponent = std::shared_ptr<MovementsComponent>(new MovementsComponent(
		m_reference, m_userActions, playerSpeed
	));
	auto collisionComponent = std::shared_ptr<CollisionComponent>(new CollisionComponent(m_reference, m_board));
	collisionComponent->addHitboxPoint(0.20f, 0.01f);
	collisionComponent->addHitboxPoint(0.75f, 0.01f);
	collisionComponent->addHitboxPoint(0.75f, 0.33f);
	collisionComponent->addHitboxPoint(0.20f, 0.33f);
	m_reference->addComponent("animation", animationComponent);
	m_reference->addComponent("movements", movementsComponent);
	m_reference->addComponent("collision", collisionComponent);
	m_reference->initComponents();
	m_reference->setPosition(0.0f, 0.0f, 1.0f);

	m_UIText = std::shared_ptr<GameObject>(new GameObject);
	m_UIText->setPosition(1.0f, 1.0f, 0.0f);
	auto uiTextComponent = std::shared_ptr<TextComponent>(new TextComponent(
		m_UIText, "UI Text", "LiberationMono-Regular.ttf", 48
	));
	uiTextComponent->setUI();
	m_UIText->addComponent("text", uiTextComponent);

	m_name = std::shared_ptr<GameObject>(new GameObject);
	m_name->setPosition(1.0f, 1.0f, 0.0f);
	auto textComponent = std::shared_ptr<TextComponent>(new TextComponent(
		m_name, "Player", "LiberationMono-Regular.ttf", 48
	));
	m_name->addComponent("text", textComponent);

	setCameraView(std::shared_ptr<CameraView>(new FollowView(m_reference, glm::vec3(0.0f, 0.0f, 15.0f))));

	float cameraLeft = -4.0f;
	float cameraRight = 4.0f;
	float cameraBottom = -3.0f;
	float cameraTop = 3.0f;
	config_setCameraSize(cameraRight - cameraLeft, cameraTop - cameraBottom);
	setCamera(std::shared_ptr<Camera>(new OrthoCamera(m_cameraView, cameraLeft, cameraRight, cameraBottom, cameraTop, 0.1f, 100.0f)));

	setUICameraView(std::shared_ptr<CameraView>(new FixedView(glm::vec3(0.0f, 0.0f, 1.0f))));
	setUICamera(std::shared_ptr<Camera>(new OrthoCamera(m_UICameraView, 0.0f, 1280.0f, 0.0f, 960.0f)));
	return true;
}

void GameScene::update(StateMachine<SceneState> &stateMachine) {
	_preUpdate();
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}
	_update();
	m_reference->update();
}

void GameScene::render() {
	m_board.render(m_camera);
	m_reference->render(m_camera);
	m_UIText->render(m_UICamera);
	m_name->render(m_camera);
}
