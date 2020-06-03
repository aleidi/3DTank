#pragma once
class BaseGameEntity {
public:
	BaseGameEntity(int id) { setID(id); }
	virtual ~BaseGameEntity() {}
	virtual void Update() = 0;
	int getID()const { return m_ID; }
private:
	int m_ID;
	static int m_iNextValidID;
	void setID(int val);
};

