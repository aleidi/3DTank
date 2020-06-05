#include "EntityManager.h"
#include "BaseGameEntity.h"

EntityManager* EntityManager::getInstance() {
	static EntityManager m_EntityManager;
	return &m_EntityManager;
}

BaseGameEntity* EntityManager::getEntityFromID(int ID) const {
	EntityMap::const_iterator ent = m_EntityMap.find(ID);

	assert((ent != m_EntityMap.end()) && "<EntityManager::getEntityFromID>: invalid ID");

	return ent->second;
}

void EntityManager::RemoveEntity(BaseGameEntity* pEntity) {
	m_EntityMap.erase(m_EntityMap.find(pEntity->getID()));
}

void EntityManager::RegisterEntity(BaseGameEntity* NewEntity) {
	m_EntityMap.insert(std::make_pair(NewEntity->getID(), NewEntity));
}