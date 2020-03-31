#include "Movements.hpp"
#include "game/GameObject.hpp"

MovementsComponent::MovementsComponent(std::shared_ptr<GameObject> owner, UserActions &userActions) :
	Component(owner),
	m_userActions(userActions) {

}
void MovementsComponent::init() {
	m_animationComponent = std::dynamic_pointer_cast<AnimationComponent>(m_owner->getComponent("animation"));
}

void MovementsComponent::update() {
	if (m_animationComponent == nullptr) {
		return;
	}
	int upPressed = m_userActions.getActionState("UP"),
		downPressed = m_userActions.getActionState("DOWN"),
		leftPressed = m_userActions.getActionState("LEFT"),
		rightPressed = m_userActions.getActionState("RIGHT");

	if (upPressed) {
		if (!m_bMovesUp) {
			m_animationComponent->start("walkUp");
		}
	}
	else if (downPressed) {
		if (!m_bMovesDown) {
			m_animationComponent->start("walkDown");
		}
	}
	else if (leftPressed) {
		if (!m_bMovesLeft) {
			m_animationComponent->start("walkLeft");
		}
	}
	else if (rightPressed) {
		if (!m_bMovesRight) {
			m_animationComponent->start("walkRight");
		}
	}
	else {
		m_animationComponent->stop();
	}
	m_bMovesUp = upPressed;
	m_bMovesDown = downPressed;
	m_bMovesLeft = leftPressed;
	m_bMovesRight = rightPressed;
}
