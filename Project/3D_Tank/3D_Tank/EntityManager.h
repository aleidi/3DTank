#pragma once
#pragma warning (disable:4786)

#include <map>
#include <cassert>


class BaseGameEntity;

#define EntityMgr EntityManager::getInstance()
// singleton class to handle the management of entities
class EntityManager {
public:
	static EntityManager* getInstance();
	void registerEntity(BaseGameEntity* NewEntity);		// this mehod stores a pointer to the entity in the std::vector
													    // e_Entities at the index position indicated by the entity's ID
	                                                    // (makes for faster access)

	BaseGameEntity* getEntityFromID(int ID)const;		// returns a pointer to the entity with the ID given as a parameter
	void removeEntity(BaseGameEntity* pEntity);			// removes the entity from the list

	void reset() { m_EntityMap.clear(); }
private:
	typedef std::map<int, BaseGameEntity*> EntityMap;

	EntityMap m_EntityMap;
	EntityManager(){}

	EntityManager(const EntityManager&);
	EntityManager operator=(const EntityManager&);
};

