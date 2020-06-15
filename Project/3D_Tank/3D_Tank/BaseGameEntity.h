#pragma once
#pragma warning(disable:4786)

#include <vector>
#include <string>
#include "Vector3.h"
//#include "geometry.h"
//#include "utils.h"
#include <cassert>
#include "Math.h"
#include "Pawn.h"
// desc: base class for a game object

struct Telegram;

class BaseGameEntity : public Pawn {
public:
	enum {default_entity_type = -1};

	virtual ~BaseGameEntity() {}
	virtual void update() {};
	// virtual void render() = 0;

	virtual bool handleMessage(const Telegram& msg) { return false; }

	static int getNextValidID() { return m_iNextValidID; }
	static void resetNextValidID() { m_iNextValidID = 0; }

	///////////////////////////////////////////////////////////////////////////
	Vector3 pos()const { return m_vPosition; }
	void setPos(Vector3 new_pos) { m_vPosition = new_pos; }

	double bRadius()const { return m_dBoundingRadius; }
	void setBRadius(double r) { m_dBoundingRadius = r; }

	Vector3 scale()const { return m_vScale; }
	void setScale(Vector3 val) { m_dBoundingRadius *= Math::MaxOf(val.x, val.y) / Math::MaxOf(m_vScale.x, m_vScale.y); m_vScale = val; } // 2D
	void setScale(float val) { m_dBoundingRadius *= (val / Math::MaxOf(m_vScale.x, m_vScale.y)); m_vScale = Vector3(val, val, val); }
	///////////////////////////////////////////////////////////////////////////
	int getID()const { return m_ID; }
	
	bool isTagged()const { return m_bTag; }
	void tag() { m_bTag = true; }
	void untag() { m_bTag = false; }

	int entityType()const { return m_iType; }
	void setEntityType(int new_type) { m_iType = new_type; }

protected:
	Vector3 m_vPosition;
	Vector3 m_vScale;
	double m_dBoundingRadius;

	BaseGameEntity(int id); // { setID(id); }

private:
	int m_ID; // every entity must have a unique identifying number

	int m_iType; // every entity has a type associated with it ( health, troll, ammo etc )

	bool m_bTag; // this is a generic flag

	static int m_iNextValidID; // this is the next valid ID. Each time a BaseGameEntity is instantiated. this value is updated.

	void setID(int val); // must ba called within the constructor to make sure the ID is set correctly.  
	                     // it verifies that the value passed tp the method is greater or equal to the next valid ID,
						 // before setting the ID and incrementing the next valid ID

};

