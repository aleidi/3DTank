#include "Shell.h"
#include "GameCommon.h"
#include "ShellFlyComponent.h"

Shell::Shell(const Vector3& ori, const Vector3& direction, const int& type)
	:shellType(type), origin(ori)
{
	this->getTransform()->Forward = direction;
	this->getTransform()->setPosition(ori);
	shell = SceneManager::sGetInstance()->createSphere();
	shell->getTransform()->setPosition(this->origin);
	shell->getTransform()->setScale(0.08f, 0.08f, 0.08f);

	mCollisionSphere = new MBoundingSphere(shell);
	mCollisionSphere->createBoundingSphere(shell->getTransform()->getPosition(), 0.1f, 1);
	shell->addComponent(mCollisionSphere);
	mShellFly = new ShellFlyComponent(shell, direction);
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
