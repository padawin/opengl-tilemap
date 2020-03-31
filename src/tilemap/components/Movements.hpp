#ifndef __MOVEMENTS_COMPONENT__
#define __MOVEMENTS_COMPONENT__

#include "game/UserActions.hpp"
#include "game/Component.hpp"
#include "Animation.hpp"

class MovementsComponent : public Component {
	private:
	std::shared_ptr<AnimationComponent> m_animationComponent = 0;
	unsigned char m_movements = 0;
	unsigned char m_directionSpriteToRender = 0;
	UserActions &m_userActions;

	void _updateAnimation(unsigned char pressedKeys);

	public:
	MovementsComponent(std::shared_ptr<GameObject> owner, UserActions &userActions);
	void init();
	void moveUp(bool moves);
	void moveDown(bool moves);
	void moveLeft(bool moves);
	void moveRight(bool moves);
	void update();
};

#endif
