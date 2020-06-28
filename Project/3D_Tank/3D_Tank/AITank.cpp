#pragma once
#include "AITank.h"
#include "AIController.h"
#include "EnemyTank.h"

AITank::AITank(int ID) {
	m_Tank = new EnemyTank(ID);
	m_Tank->setResetPoint(Vector3(0, 0, 10));
	m_Tank->getTransform()->setPosition(m_Tank->getResetPoint());
	m_Tank->setMaxSpeed(1.5f);
	m_AICtrl = SceneManager::sGetInstance()->createAIController(ID);
	m_AICtrl->posses(m_Tank);
}

AITank::~AITank() {

}

EnemyTank* AITank::getTank() {
	return m_Tank;
}

AIController* AITank::getCtrl() {
	return m_AICtrl;
}