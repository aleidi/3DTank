#include "Shell.h"
#include "GameCommon.h"
#include "ShellFlyComponent.h"

Shell::Shell(const Vector3& ori, const Vector3& direction, const int& type)
	:shellType(type), origin(ori)
{
	this->getTransform()->Forward = direction;
	//this->getTransform()->setPosition(ori);
	shell = SceneManager::sGetInstance()->createSphere();
	shell->getTransform()->setPosition(this->origin);
	shell->getTransform()->setScale(0.02f, 0.02f, 0.02f);

	mCollisionSphere = new MBoundingSphere(shell);
	mCollisionSphere->createBoundingSphere(shell->getTransform()->getPosition(), 0.1f, 1);
	shell->addComponent(mCollisionSphere);
	mShellFly = new ShellFlyComponent(shell, direction);
	shell->addComponent(mShellFly);
}

Shell::Shell(GameObject* obj, const int& type)
	:shellType(type), origin(obj->getTransform()->Forward), fireTank(obj)
{
	this->getTransform()->Forward = obj->getTransform()->Forward;
	//this->getTransform()->setPosition(obj->getTransform()->getPosition() + obj->getTransform()->Forward*0.6f + obj->getTransform()->Up*0.18f + obj->getTransform()->Right*0.04f);
	shell = SceneManager::sGetInstance()->createSphere();
	shell->getTransform()->setPosition(obj->getTransform()->getPosition() + obj->getTransform()->Forward*0.6f + obj->getTransform()->Up*0.18f + obj->getTransform()->Right*0.04f);
	shell->getTransform()->setScale(0.02f, 0.02f, 0.02f);

	mCollisionSphere = new MBoundingSphere(shell);
	mCollisionSphere->createBoundingSphere(shell->getTransform()->getPosition(), 0.1f, 1);
	shell->addComponent(mCollisionSphere);
	mShellFly = new ShellFlyComponent(shell, obj->getTransform()->Forward);
	shell->addComponent(mShellFly);
}

Shell::~Shell()
{
}

MBoundingSphere * Shell::getCollisionSphere()
{
	return this->mCollisionSphere;
}

int Shell::getShelltype()
{
	return this->shellType;
}
