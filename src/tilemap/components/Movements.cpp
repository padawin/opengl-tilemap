#include "Movements.hpp"
#include "game/GameObject.hpp"

const unsigned char NO_DIRECTION    = 0;
const unsigned char DIRECTION_UP    = 1;
const unsigned char DIRECTION_DOWN  = 1 << 1;
const unsigned char DIRECTION_RIGHT = 1 << 2;
const unsigned char DIRECTION_LEFT  = 1 << 3;
const unsigned char MAX_DIRECTION   = 1 << 4;
const unsigned char HORIZONTAL_DIRECTION = DIRECTION_RIGHT | DIRECTION_LEFT;
const unsigned char VERTICAL_DIRECTION = DIRECTION_UP | DIRECTION_DOWN;

MovementsComponent::MovementsComponent(std::shared_ptr<GameObject> owner, UserActions &userActions, float speed) :
	Component(owner),
	m_userActions(userActions),
	m_fSpeed(speed)
{

}
void MovementsComponent::init() {
	m_animationComponent = std::dynamic_pointer_cast<AnimationComponent>(m_owner->getComponent("animation"));
	m_collisionComponent = std::dynamic_pointer_cast<CollisionComponent>(m_owner->getComponent("collision"));
}

void MovementsComponent::update() {
	unsigned char pressedKeys = 0;
	pressedKeys = pressedKeys | (m_userActions.getActionState("UP") ? DIRECTION_UP : NO_DIRECTION);
	pressedKeys = pressedKeys | (m_userActions.getActionState("DOWN") ? DIRECTION_DOWN : NO_DIRECTION);
	pressedKeys = pressedKeys | (m_userActions.getActionState("RIGHT") ? DIRECTION_RIGHT : NO_DIRECTION);
	pressedKeys = pressedKeys | (m_userActions.getActionState("LEFT") ? DIRECTION_LEFT : NO_DIRECTION);
	_updateAnimation(pressedKeys);
	_updatePosition(pressedKeys);
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
		m_directionIndex = i;
		std::string animations[] = {"walkUp", "walkDown", "walkRight", "walkLeft"};
		m_animationComponent->start(animations[i]);
	}
}

void MovementsComponent::_updatePosition(unsigned char pressedKeys) {
	if (!pressedKeys) {
		return;
	}

	float xSpeeds[] = {0.0f, 0.0f, m_fSpeed, -m_fSpeed};
	float ySpeeds[] = {m_fSpeed, -m_fSpeed, 0.0f, 0.0f};
	glm::vec3 pos = m_owner->getPosition();
	float oldX = pos.x;
	float oldY = pos.y;

	if (m_directionSpriteToRender & HORIZONTAL_DIRECTION) {
		pos.x += xSpeeds[m_directionIndex];
		if (pressedKeys & DIRECTION_UP) {
			pos.y += m_fSpeed;
		}
		else if (pressedKeys & DIRECTION_DOWN) {
			pos.y -= m_fSpeed;
		}
	}
	else if (m_directionSpriteToRender & VERTICAL_DIRECTION) {
		pos.y += ySpeeds[m_directionIndex];
		if (pressedKeys & DIRECTION_RIGHT) {
			pos.x += m_fSpeed;
		}
		else if (pressedKeys & DIRECTION_LEFT) {
			pos.x -= m_fSpeed;
		}
	}
	m_owner->setPosition(pos.x, pos.y, pos.z);
	if (m_collisionComponent && m_collisionComponent->collides()) {
		m_owner->setPosition(oldX, oldY, pos.z);
	}
}
