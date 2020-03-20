#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#include <vector>

/**
 * Finished state machine. Contains a stack of states.
 * A new state can be pushed on top of the stack, the top state can be changed
 * for another one and the top state can also be popped.
 */
template <class stateType> class StateMachine {
	private:
	std::vector<stateType*> m_vStates = {};

	public:
	void pushState(stateType* pState);
	void changeState(stateType* pState);
	bool popState();
	void clean();
	stateType* getCurrentState() const;

	/**
	 * Methods to update and render the current state
	 */
	void update();
	void render() const;
};

#include "StateMachine.tpp"

#endif
