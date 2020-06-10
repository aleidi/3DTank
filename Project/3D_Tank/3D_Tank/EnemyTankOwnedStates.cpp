#include "EnemyTankOwnedStates.h"
#include "State.h"
#include "EnemyTank.h"
#include "EntityNames.h"

#include "Engine.h" // text test

//-------------------methods for DazeAndRest

DazeAndRest* DazeAndRest::getInstance() {
	static DazeAndRest* m_DazeAndRest;
	return m_DazeAndRest;
}

void DazeAndRest::enter(EnemyTank* pEnemyTank) {

}

void DazeAndRest::execute(EnemyTank* pEnemyTank) {

}

void DazeAndRest::exit(EnemyTank* pEnemyTank) {

}

bool DazeAndRest::onMessage(EnemyTank*, const Telegram&) {
	return false;
}

//-------------------methods for Patrol
Patrol* Patrol::getInstance() {
	static Patrol* m_Patrol;
	return m_Patrol;
}

void Patrol::enter(EnemyTank* pEnemyTank) {

}

void Patrol::execute(EnemyTank* pEnemyTank) {

}

void Patrol::exit(EnemyTank* pEnemyTank) {

}

bool Patrol::onMessage(EnemyTank*, const Telegram&) {
	return false;
}