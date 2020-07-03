#pragma once
#include "AITank.h"
#include "AIController.h"
#include "EnemyTank.h"

AITank::AITank(int ID) 
	: AITank(ID, -1)
{

}

AITank::AITank(int ID, int targetID) {
	if (ID == 0)
		m_Tank = new EnemyTank(ID,0.02);
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

	if (ID == 9) {
		m_AICtrl->setPatrol(true, Vector3(30, 0, -80), Vector3(30, 0, -30));
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