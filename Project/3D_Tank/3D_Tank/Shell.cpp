#include "Shell.h"
#include "GameCommon.h"
#include "ShellFlyComponent.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "SoundComponent.h"
#include "Pawn.h"
#include "PlayerTank.h"

Shell::Shell(const Vector3& ori, const Vector3& direction, const int& type)
	:shellType(type), origin(ori)
{
	//this->getTransform()->Forward = direction;
/*	SceneManager::sGetInstance()->createModel(*this, "Objects\\Shell", L"Objects\\Shell");
	this->getTransform()->setPosition(this->origin + direction * 0.6f + Vector3::up * 0.1f);
	this->getTransform()->setScale(0.02f, 0.02f, 0.02f);
	this->getTransform()->rotate(this->getTransform()->getRotation().x + 90.f, this->getTransform()->getRotation().y, this->getTransform()->getRotation().z);

	mCollisionSphere = new MBoundingSphere(this);
	mCollisionSphere->createBoundingSphere(this->getTransform()->getPosition(), 0.001f, 1);
	this->addComponent(mCollisionSphere);
	mShellFly = new ShellFlyComponent(this, direction);
	this->addComponent(mShellFly);
	this->sphere = mCollisionSphere;
	mSound = new SoundComponent(this);
	this->addComponent(mSound)*/;

	this->getTransform()->setPosition(ori);
	shell = SceneManager::sGetInstance()->createSphere();
	shell->getTransform()->setPosition(this->origin + direction * 0.6f + Vector3::up * 0.1f);
	shell->getTransform()->setScale(0.02f, 0.02f, 0.02f);

	mCollisionSphere = new MBoundingSphere(shell);
	mCollisionSphere->createBoundingSphere(shell->getTransform()->getPosition(), 0.001f, 1);
	shell->addComponent(mCollisionSphere);
	mShellFly = new ShellFlyComponent(shell, direction);
	shell->addComponent(mShellFly);
	shell->sphere = mCollisionSphere;
	mSound = new SoundComponent(shell);
	shell->addComponent(mSound);
}

Shell::Shell(GameObject* obj, const int& type)
	:shellType(type), origin(obj->getTransform()->Forward)
{
	//this->getTransform()->Forward = obj->getTransform()->Forward;
	//this->getTransform()->setPosition(obj->getTransform()->getPosition() + obj->getTransform()->Forward*0.6f + obj->getTransform()->Up*0.18f + obj->getTransform()->Right*0.04f);
	shell = SceneManager::sGetInstance()->createSphere();
	shell->getTransform()->setPosition(obj->getTransform()->getPosition() + obj->getTransform()->Forward*0.6f + obj->getTransform()->Up*0.18f + obj->getTransform()->Right*0.04f);
	shell->getTransform()->setScale(0.02f, 0.02f, 0.02f);

	mCollisionSphere = new MBoundingSphere(shell);
	mCollisionSphere->createBoundingSphere(shell->getTransform()->getPosition(), 0.01f, 1);
	shell->addComponent(mCollisionSphere);
	mShellFly = new ShellFlyComponent(shell, obj->getTransform()->Forward);
	shell->addComponent(mShellFly);
	shell->sphere = mCollisionSphere;
	mSound = new SoundComponent(shell);
	shell->addComponent(mSound);
}

Shell::~Shell()
{
}

MBoundingSphere * Shell::getCollisionSphere()
{
	return this->mCollisionSphere;
}

ShellFlyComponent * Shell::getShellComponent()
{
	if(this->shellType == 1)
		return this->mShellFly;
	else return NULL;
}

int Shell::getShelltype()
{
	return this->shellType;
}

void Shell::onUpdate(float deltaTime)
{
	if (CollisionManager::sGetInstance()->collisionCheck_SphereToCube(this->shell->sphere, &attactTank) == true) {		
		if (attactTank->cube->moveable == 1) {
			reinterpret_cast<Pawn*>(attactTank)->onCollisionEnter();
		}
		this->onTriggerEnter();
	}
	
	mCount += deltaTime;
	if (mCount > 5.0f)
	{
		shell->destroy();
		destroy();
	}
	//if (CollisionManager::sGetInstance()->collisionCheck_SphereToCube(this->sphere, &attactTank) == true) {
	//	if (attactTank->cube->moveable == 1) {
	//		reinterpret_cast<Pawn*>(attactTank)->onCollisionEnter();
	//	}
	//	this->onTriggerEnter();
	//}

	//mCount += deltaTime;
	//if (mCount > 5.0f)
	//{
	//	//shell->destroy();
	//	destroy();
	//}
}

void Shell::onTriggerEnter()
{
	mSound->setPosition();
	SoundManager::sGetInstance()->playSound(mSound->mChannel, 6);
	//shell->destroy();
	this->destroy();
}
