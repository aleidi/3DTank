#pragma once
#include <assert.h>

#include "State.h"

template <class entity_type>
class StateMachine {
public:
	StateMachine(entity_type* owner): m_pOwner(owner),
									  m_pCurrentState(NULL),
									  m_pPreviousState(NULL),
		                              m_pGlobalState(NULL)
	{}

	void setCurrentState(State<entity_type>* s) { m_pCurrentState = s; }
	void setPreviousState(State<entity_type>* s) { m_pPreviousState = s; }
	void setGlobalState(State<entity_type>* s) { m_pGlobalState = s; }

	void update() const {
		if (m_pGlobalState) m_pGlobalState->Execute(m_pOwner);
		if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}

	void changeState(State<entity_type>* pNewState) {
		assert(pNewState && "<StateMachine::ChangeState>: trying to change to a null state");

		m_pPreviousState = m_pCurrentState;
		m_pCurrentState->Exit(m_pOwner);
		m_pCurrentState = pNewState;
		m_pCurrentState->Enter(m_pOwner);
	}

	void revertToPerviousState() {
		changeState(m_pPreviousState);
	}

	State<entity_type>* getCurrentState() const { return m_pCurrentState; }
	State<entity_type>* getGlobalState() const { return m_pGlobalState; }
	State<entity_type>* getPreviousState() const { return m_pPreviousState; }

	bool isInState(const State<entity_type>& st) const;
private:
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;
	State<entity_type>* m_pPreviousState;
	State<entity_type>* m_pGlobalState;
};

