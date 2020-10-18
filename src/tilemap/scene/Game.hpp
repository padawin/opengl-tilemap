#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "game/SceneState.hpp"
#include "game/UserActions.hpp"
#include "game/GameObject.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "tilemap/AnimationCollection.hpp"
#include "tilemap/Tilemap.hpp"

class GameScene : public SceneState {
	private:
	Tilemap m_board;
	ObjectRenderer m_spriteRenderer = ObjectRenderer();
	AnimationCollection m_animationCollection = AnimationCollection();
	std::shared_ptr<GameObject> m_reference = 0;
	std::shared_ptr<GameObject> m_name = 0;
	std::shared_ptr<GameObject> m_UIText = 0;

	public:
	GameScene(UserActions &userActions);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
