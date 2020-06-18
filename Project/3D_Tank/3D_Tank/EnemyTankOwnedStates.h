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
	Wander() {
		float theta = Math::RandFloat() * 2 * Pi ;
		m_WanderTarget = Vector3(m_WanderRadius * cos(theta), 0, m_WanderRadius * sin(theta));
	}
	float maxspeed = 0.5;
	float mass = 50;
	Vector3 velocity;

	float m_WanderRadius = 10.0;
	float m_WanderDistance = 20;
	float m_WanderJitter = 800;
	Vector3 m_WanderTarget;

	float timer = 0;
	float speed = 1.0*0.0001;
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


 
