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

void DazeAndRest::Enter(EnemyTank* pEnemyTank) {

}

void DazeAndRest::Execute(EnemyTank* pEnemyTank) {

}

void DazeAndRest::Exit(EnemyTank* pEnemyTank) {

}

bool DazeAndRest::OnMessage(EnemyTank*, const Telegram&) {
	return false;
}

//-------------------methods for Patrol
Patrol* Patrol::getInstance() {
	static Patrol* m_Patrol;
	return m_Patrol;
}

void Patrol::Enter(EnemyTank* pEnemyTank) {

}

void Patrol::Execute(EnemyTank* pEnemyTank) {

}

void Patrol::Exit(EnemyTank* pEnemyTank) {

}

bool Patrol::OnMessage(EnemyTank*, const Telegram&) {
	return false;
}