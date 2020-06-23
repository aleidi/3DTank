#include "BaseGameEntity.h"
#include "MovementComponent.h"

int BaseGameEntity::m_iNextValidID = 0;

void BaseGameEntity::setID(int val) {
	assert((val >= m_iNextValidID) && "<BaseGameEntity::setID>: invalid ID");

	m_ID = val;

	m_iNextValidID = m_ID + 1;
}
