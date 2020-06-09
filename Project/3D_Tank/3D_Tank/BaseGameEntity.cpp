#include "BaseGameEntity.h"

int BaseGameEntity::m_iNextValidID = 0;

BaseGameEntity::BaseGameEntity(int ID) :m_iType(default_entity_type),
										m_bTag(false)
{
	setID(ID);
}

void BaseGameEntity::setID(int val) {
	assert((val >= m_iNextValidID) && "<BaseGameEntity::setID>: invalid ID");

	m_ID = val;

	m_iNextValidID = m_ID + 1;
}