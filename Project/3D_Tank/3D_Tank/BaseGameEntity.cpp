#include "BaseGameEntity.h"
#include "MovementComponent.h"

int BaseGameEntity::m_iNextValidID = 0;

void BaseGameEntity::setID(int val) {
	m_ID = val;

	m_iNextValidID = m_ID + 1;
}
