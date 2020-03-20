#include <iostream>

template <class stateType>
void StateMachine<stateType>::pushState(stateType *pState) {
	// if the current state is the same as the pushed one, do nothing
	if (!m_vStates.empty() && m_vStates.back()->getStateID() == pState->getStateID()) {
		return;
	}

	m_vStates.push_back(pState);
	if (!m_vStates.back()->onEnter()) {
		popState();
	}
}

template <class stateType>
void StateMachine<stateType>::changeState(stateType *pState) {
	std::clog << "Change state";
	// If there is at least one state
	if (!m_vStates.empty()) {
		std::clog << " from " << m_vStates.back()->getStateID();
		// and if it is the state we want to add
		if (m_vStates.back()->getStateID() == pState->getStateID()) {
			return;
		}

		// remove the state
		popState();
	}
	std::clog << " to " << pState->getStateID() << std::endl;

	// add the new one
	pushState(pState);
}

template <class stateType>
bool StateMachine<stateType>::popState() {
	if (!m_vStates.empty() && m_vStates.back()->onExit()) {
		delete m_vStates.back();
		m_vStates.pop_back();
		return true;
	}

	return false;
}

template <class stateType>
void StateMachine<stateType>::clean() {
	while (popState()) {}
}

template <class stateType>
stateType* StateMachine<stateType>::getCurrentState() const {
	if (!m_vStates.empty()) {
		return m_vStates.back();
	}
	return NULL;
}

template <class stateType>
void StateMachine<stateType>::update() {
	if (!m_vStates.empty()) {
		m_vStates.back()->update(*this);
	}
}

template <class stateType>
void StateMachine<stateType>::render() const {
	if (!m_vStates.empty()) {
		m_vStates.back()->render();
	}
}
