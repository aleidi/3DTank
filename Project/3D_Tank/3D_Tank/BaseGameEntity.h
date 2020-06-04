#pragma once

// desc: base class for a game object
class BaseGameEntity {
public:
	BaseGameEntity(int id) { setID(id); }
	virtual ~BaseGameEntity() {}
	virtual void Update() = 0;
	int getID()const { return m_ID; }

private:
	int m_ID; // every entity must have a unique identifying number

	static int m_iNextValidID; // this is the next valid ID. Each time a BaseGameEntity is instantiated. this value is updated.

	void setID(int val); // must ba called within the constructor to make sure the ID is set correctly.  
	                     // it verifies that the value passed tp the method is greater or equal to the next valid ID,
						 // before setting the ID and incrementing the next valid ID
};

