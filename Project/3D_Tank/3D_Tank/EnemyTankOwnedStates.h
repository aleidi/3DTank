#pragma once
// all states that can be assigned to the enemytank class
#include "State.h"
#include "Math.h"

class AIController;
struct Telegram;

class Rest : public State<AIController> {
public:
	static Rest* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Rest() {}

	Rest(const Rest&);
	Rest& operator=(const Rest&);
};

class Wander : public State<AIController> {
public:
	static Wander* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Wander() {}

	float mass = 50;
	
	float rotate = 0.0f;
	Wander(const Wander&);
	Wander& operator=(const Wander&);
};

class Avoidance : public State<AIController> {
public:
	static Avoidance* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Avoidance() {}

	Avoidance(const Avoidance&);
	Avoidance& operator=(const Avoidance&);
};

class Attack : public State<AIController> {
public:
	static Attack* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Attack() {}

	Attack(const Attack&);
	Attack& operator=(const Attack&);
};

class Evade : public State<AIController> {
public:
	static Evade* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Evade() {}

	Evade(const Evade&);
	Evade& operator=(const Evade&);
};

class Pursuit : public State<AIController> {
public:
	static Pursuit* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Pursuit() {}

	Pursuit(const Pursuit&);
	Pursuit& operator=(const Pursuit&);
};

class Death : public State<AIController> {
public:
	static Death* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Death() {}

	Death(const Death&);
	Death& operator=(const Death&);
};



//////////////////////////////////////
class Patrol : public State<AIController> {
public:
	static Patrol* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Patrol() {}

	Patrol(const Patrol&);
	Patrol& operator=(const Patrol&);
};


 
