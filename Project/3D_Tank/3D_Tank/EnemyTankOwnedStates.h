#pragma once
// all states that can be assigned to the enemytank class
#include "State.h"
class EnemyTank;
struct Telegram;

class Rest : public State<EnemyTank> {
public:
	static Rest* getInstance();
	virtual void enter(EnemyTank* pETank);
	virtual void execute(EnemyTank* pETank);
	virtual void exit(EnemyTank* pETank);

	virtual bool onMessage(EnemyTank* agent, const Telegram& msg);
private:
	Rest() {}
	
	Rest(const Rest&);
	Rest& operator=(const Rest&);
};

class Patrol : public State<EnemyTank> {
public:
	static Patrol* getInstance();
	virtual void enter(EnemyTank* pETank);
	virtual void execute(EnemyTank* pETank);
	virtual void exit(EnemyTank* pETank);

	virtual bool onMessage(EnemyTank* agent, const Telegram& msg);
private:
	Patrol() {}
	
	Patrol(const Patrol&);
	Patrol& operator=(const Patrol&);
};

class Attack : public State<EnemyTank> {
public:
	static Attack* getInstance();
	virtual void enter(EnemyTank* pETank);
	virtual void execute(EnemyTank* pETank);
	virtual void exit(EnemyTank* pETank);

	virtual bool onMessage(EnemyTank* agent, const Telegram& msg);
private:
	Attack() {}

	Attack(const Attack&);
	Attack& operator=(const Attack&);
};

class Evade : public State<EnemyTank> {
public:
	static Evade* getInstance();
	virtual void enter(EnemyTank* pETank);
	virtual void execute(EnemyTank* pETank);
	virtual void exit(EnemyTank* pETank);

	virtual bool onMessage(EnemyTank* agent, const Telegram& msg);
private:
	Evade() {}

	Evade(const Evade&);
	Evade& operator=(const Evade&);
};

class Avoidance : public State<EnemyTank> {
public:
	static Avoidance* getInstance();
	virtual void enter(EnemyTank* pETank);
	virtual void execute(EnemyTank* pETank);
	virtual void exit(EnemyTank* pETank);

	virtual bool onMessage(EnemyTank* agent, const Telegram& msg);
private:
	Avoidance() {}

	Avoidance(const Avoidance&);
	Avoidance& operator=(const Avoidance&);
};



 
