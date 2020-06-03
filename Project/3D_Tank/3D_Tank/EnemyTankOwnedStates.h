#pragma once
// all states that can be assigned to the enemytank class
#include "State.h"
class EnemyTank;

class DazeAndRest : public State<EnemyTank> {
public:
	static DazeAndRest& getInstance();
	virtual void Enter(EnemyTank* pETank);
	virtual void Execute(EnemyTank* pETank);
	virtual void Exit(EnemyTank* pETank);
private:
	DazeAndRest() {}
	
	DazeAndRest(const DazeAndRest&);
	DazeAndRest& operator=(const DazeAndRest&);
};

class Patrol : public State<EnemyTank> {
public:
	static Patrol& getInstance();
	virtual void Enter(EnemyTank* pETank);
	virtual void Execute(EnemyTank* pETank);
	virtual void Exit(EnemyTank* pETank);
private:
	Patrol() {}
	
	Patrol(const Patrol&);
	Patrol& operator=(const Patrol&);
};


