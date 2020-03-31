#include "Movements.hpp"
#include "game/GameObject.hpp"

const unsigned char NO_DIRECTION    = 0;
const unsigned char DIRECTION_UP    = 1;
const unsigned char DIRECTION_DOWN  = 1 << 1;
const unsigned char DIRECTION_RIGHT = 1 << 2;
const unsigned char DIRECTION_LEFT  = 1 << 3;
const unsigned char MAX_DIRECTION   = 1 << 4;

MovementsComponent::MovementsComponent(std::shared_ptr<GameObject> owner, UserActions &userActions) :
	Component(owner),
	m_userActions(userActions) {

}
void MovementsComponent::init() {
	m_animationComponent = std::dynamic_pointer_cast<AnimationComponent>(m_owner->getComponent("animation"));
}

void MovementsComponent::update() {
	unsigned char pressedKeys = 0;
	pressedKeys = pressedKeys | (m_userActions.getActionState("UP") ? DIRECTION_UP : NO_DIRECTION);
	pressedKeys = pressedKeys | (m_userActions.getActionState("DOWN") ? DIRECTION_DOWN : NO_DIRECTION);
	pressedKeys = pressedKeys | (m_userActions.getActionState("RIGHT") ? DIRECTION_RIGHT : NO_DIRECTION);
	pressedKeys = pressedKeys | (m_userActions.getActionState("LEFT") ? DIRECTION_LEFT : NO_DIRECTION);
	_updateAnimation(pressedKeys);
}

void MovementsComponent::_updateAnimation(unsigned char pressedKeys) {
	if (m_animationComponent == nullptr) {
		return;
	}

	if (!pressedKeys) {
		m_directionSpriteToRender = 0;
		m_animationComponent->stop();
	}
	else if (!(m_directionSpriteToRender & pressedKeys)) {
		int i, direction;
		// find first pressed direction and use it for the animation
		for (
			i = 0, direction = 1;
			direction < MAX_DIRECTION && !(direction & pressedKeys);
			i++, direction = 1 << i
		) {}
		m_directionSpriteToRender = (unsigned char) direction;
		std::string animations[] = {"walkUp", "walkDown", "walkRight", "walkLeft"};
		m_animationComponent->start(animations[i]);
	}
}
