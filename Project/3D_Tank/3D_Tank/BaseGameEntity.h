#pragma once
#pragma warning(disable:4786)

#include <string>
#include <cassert>
#include "Pawn.h"
// desc: base class for a game object

struct Telegram;

class BaseGameEntity : public Pawn {
public:
	enum {default_entity_type = -1};

	BaseGameEntity(int id): Pawn() { setID(id); }
	virtual ~BaseGameEntity() {}

	/////////////////////////////////////

	// virtual bool handleMessage(const Telegram& msg) { return false; }

	static int getNextValidID() { return m_iNextValidID; }
	static void resetNextValidID() { m_iNextValidID = 0; }

	int getID()const { return m_ID; }

private:
	int m_ID; // every entity must have a unique identifying number

	static int m_iNextValidID; // this is the next valid ID. Each time a BaseGameEntity is instantiated. this value is updated.

	void setID(int val); // must ba called within the constructor to make sure the ID is set correctly.  
	                     // it verifies that the value passed tp the method is greater or equal to the next valid ID,
						 // before setting the ID and incrementing the next valid ID

};

