#ifndef __MOVEMENTS_COMPONENT__
#define __MOVEMENTS_COMPONENT__

#include "game/UserActions.hpp"
#include "game/Component.hpp"
#include "Animation.hpp"

class MovementsComponent : public Component {
	private:
	std::shared_ptr<AnimationComponent> m_animationComponent = 0;
	unsigned char m_movements = 0;
	bool m_bMovesUp = false;
	bool m_bMovesDown = false;
	bool m_bMovesLeft = false;
	bool m_bMovesRight = false;
	UserActions &m_userActions;

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
