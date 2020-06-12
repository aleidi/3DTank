#pragma once
#include <cassert>
#include <string>

#include "State.h"
#include "Telegram.h"

template <class entity_type>
class StateMachine {
public:
	StateMachine(entity_type* owner): m_pOwner(owner),
									  m_pCurrentState(NULL),
									  m_pPreviousState(NULL),
		                              m_pGlobalState(NULL)
	{}

	virtual ~StateMachine(){}

	void setCurrentState(State<entity_type>* s) { m_pCurrentState = s; }
	void setPreviousState(State<entity_type>* s) { m_pPreviousState = s; }
	void setGlobalState(State<entity_type>* s) { m_pGlobalState = s; }

	void update() const {
		if (m_pGlobalState)
			m_pGlobalState->execute(m_pOwner);
		if (m_pCurrentState)
			m_pCurrentState->execute(m_pOwner);
	}

	void changeState(State<entity_type>* pNewState) {
		assert(pNewState && "<StateMachine::ChangeState>: trying to change to a null state");

		m_pPreviousState = m_pCurrentState;
		m_pCurrentState->exit(m_pOwner);
		m_pCurrentState = pNewState;
		m_pCurrentState->enter(m_pOwner);
	}

	void revertToPerviousState() {
		changeState(m_pPreviousState);
	}

	State<entity_type>* getCurrentState() const { return m_pCurrentState; }
	State<entity_type>* getGlobalState() const { return m_pGlobalState; }
	State<entity_type>* getPreviousState() const { return m_pPreviousState; }

	bool isInState(const State<entity_type>& st) const {
		if (typeid(*m_pCurrentState) == typeid(st)) return true;
		return false;
	}

	bool handleMessage(const Telegram& msg)const {
		if (m_pCurrentState && m_pCurrentState->onMessage(m_pOwner, msg)) {
			return true;
		}

		if (m_pGlobalState && m_pGlobalState->onMessage(m_pOwner, msg)) {
			return true;
		}

		return false;
	}

	std::string getNameOfCurrentState()const {
		std::string s(typeid(*m_pCurrentState).name());
		return s;
	}
private:
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;
	State<entity_type>* m_pPreviousState;
	State<entity_type>* m_pGlobalState;
};

