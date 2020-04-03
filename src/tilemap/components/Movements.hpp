#ifndef __MOVEMENTS_COMPONENT__
#define __MOVEMENTS_COMPONENT__

#include "game/UserActions.hpp"
#include "game/Component.hpp"
#include "Animation.hpp"
#include "Collision.hpp"

class MovementsComponent : public Component {
	private:
	std::shared_ptr<AnimationComponent> m_animationComponent = 0;
	std::shared_ptr<CollisionComponent> m_collisionComponent = 0;
	unsigned char m_movements = 0;
	unsigned char m_directionSpriteToRender = 0;
	int m_directionIndex = 0;
	UserActions &m_userActions;
	float m_fSpeed;

	void _updateAnimation(unsigned char pressedKeys);
	void _updatePosition(unsigned char pressedKeys);

	public:
	MovementsComponent(std::shared_ptr<GameObject> owner, UserActions &userActions, float speed);
	void init();
	void moveUp(bool moves);
	void moveDown(bool moves);
	void moveLeft(bool moves);
	void moveRight(bool moves);
	void update();
};

#endif
