#pragma once
#pragma warning(disable:4786)

#include <vector>
#include <string>
#include "Vector3.h"
//#include "geometry.h"
//#include "utils.h"
#include <cassert>
// desc: base class for a game object

struct Telegram;

class BaseGameEntity {
public:
	enum {default_entity_type = -1};

	BaseGameEntity(int id) { setID(id); }
	virtual ~BaseGameEntity() {}
	virtual void update() {};
	virtual void render() = 0;

	virtual bool handleMessage(const Telegram& msg) { return false; }

	static int getNextValidID() { return m_iNextValidID; }
	static void resetNextValidID() { m_iNextValidID = 0; }

	int getID()const { return m_ID; }
	
	bool isTagged()const { return m_bTag; }
	void tag() { m_bTag = true; }
	void untag() { m_bTag = false; }

	int entityType()const { return m_iType; }
	void setEntityType(int new_type) { m_iType = new_type; }

private:
	int m_ID; // every entity must have a unique identifying number

	int m_iType; // every entity has a type associated with it ( health, troll, ammo etc )

	bool m_bTag; // this is a generic flag

	static int m_iNextValidID; // this is the next valid ID. Each time a BaseGameEntity is instantiated. this value is updated.

	void setID(int val); // must ba called within the constructor to make sure the ID is set correctly.  
	                     // it verifies that the value passed tp the method is greater or equal to the next valid ID,
						 // before setting the ID and incrementing the next valid ID

};

