#pragma once
// all states that can be assigned to the enemytank class
#include "State.h"
class EnemyTank;

class DazeAndRest : public State<EnemyTank> {
public:
	static DazeAndRest* getInstance();
	virtual void enter(EnemyTank* pETank);
	virtual void execute(EnemyTank* pETank);
	virtual void exit(EnemyTank* pETank);

	virtual bool onMessage(EnemyTank*, const Telegram&);
private:
	DazeAndRest() {}
	
	DazeAndRest(const DazeAndRest&);
	DazeAndRest& operator=(const DazeAndRest&);
};

class Patrol : public State<EnemyTank> {
public:
	static Patrol* getInstance();
	virtual void enter(EnemyTank* pETank);
	virtual void execute(EnemyTank* pETank);
	virtual void exit(EnemyTank* pETank);

	virtual bool onMessage(EnemyTank*, const Telegram&);
private:
	Patrol() {}
	
	Patrol(const Patrol&);
	Patrol& operator=(const Patrol&);
};


