#pragma once
#include "AITank.h"
#include "AIController.h"
#include "EnemyTank.h"
#include "EnemyBoss.h"

AITank::AITank(int ID) 
	: AITank(ID, -1)
{

}

AITank::AITank(int ID, int targetID) {
	m_ID = ID;

	if (ID == 0)
		m_Tank = new EnemyBoss(ID);
	else 
		m_Tank = new EnemyTank(ID);
	m_Tank->getTransform()->translate(m_Tank->getResetPoint());
	m_AICtrl = SceneManager::sGetInstance()->createAIController(ID);
	m_AICtrl->posses(m_Tank);
	m_Tank->setAICtrl(m_AICtrl);
	m_AICtrl->setPrefabs(this);

	if (targetID >= 0) {
		changeTarget(targetID);
	}

	if (ID == 2) {
		m_AICtrl->setPatrol(true, Vector3(-7.0, 0, 25.0), Vector3(-31, 0, 25.0));
	}
	/*
	if (ID == 3) {
		m_AICtrl->setPatrol(true, Vector3(2.3, 0, 12.0), Vector3(2.3, 0, -13.0));
	}
	*/
	if (ID == 4) {
		m_AICtrl->setPatrol(true, Vector3(-33.0, 0, -34.0), Vector3(-33.0, 0, -82.0));
	}

	if (ID == 6) {
		m_AICtrl->setPatrol(true, Vector3(-25.0, 0, -82.0), Vector3(0.0, 0, -82.0));
	}

	if (ID == 8) {
		m_AICtrl->setPatrol(true, Vector3(30.0, 0, -80.0), Vector3(30.0, 0, -15.0));
	}
}

AITank::~AITank() {
	m_Tank->destroy();
	m_AICtrl->destroy();
}

EnemyTank* AITank::getTank() {
	return m_Tank;
}

AIController* AITank::getCtrl() {
	return m_AICtrl;
}

void AITank::changeTarget(int targetID) {
	if (SceneManager::sGetInstance()->getAIController(targetID) != nullptr)
		m_AICtrl->setTarget(SceneManager::sGetInstance()->getAIController(targetID)->getPawn());
}

bool AITank::isAlive() {
	return m_Tank->isAlive();
}