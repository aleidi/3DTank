#include "Shell.h"
#include "GameCommon.h"
#include "ShellFlyComponent.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "SoundComponent.h"
#include "PlayerTank.h"
#include "ShellContainer.h"

Shell::Shell(const Vector3& ori, const Vector3& direction, const int& type)
	:shellType(type), origin(ori)
{
	//this->getTransform()->Forward = direction;
	//this->getTransform()->setPosition(ori);
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
	this->onTrigger = true;
	ShellContainer::sGetInstance()->onTriggerShells.push_back(this);
	mSound->setPosition();
	SoundManager::sGetInstance()->playOverlapSound(mSound->mChannel, 3);
}

Shell::Shell(const int & shellType)
{
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

void Shell::resetPosAndDir(const Vector3 & origin, const Vector3 & direction, const int & shellType)
{
	this->onTrigger = true;
	this->shell->getTransform()->setPosition(origin + direction * 0.6f + Vector3::up * 0.1f);
	this->mCollisionSphere->sphere.Center.x = shell->getTransform()->getPosition().x;
	this->mCollisionSphere->sphere.Center.y = shell->getTransform()->getPosition().y;
	this->mCollisionSphere->sphere.Center.z = shell->getTransform()->getPosition().z;
	this->shellType = shellType;
	this->mShellFly->setVelocity(direction);
	mSound->setPosition();
	SoundManager::sGetInstance()->stop(mSound->mChannel);
	SoundManager::sGetInstance()->playOverlapSound(mSound->mChannel, 3);
	ShellContainer::sGetInstance()->onTriggerShells.push_back(this);
	for (std::vector<Shell*>::iterator it = ShellContainer::sGetInstance()->unTriggerShells.begin(); it != ShellContainer::sGetInstance()->unTriggerShells.end(); it++) {
		if (*it == this) {
			ShellContainer::sGetInstance()->unTriggerShells.erase(it);
			break;
		}
	}
}

MBoundingSphere* Shell::getCollisionSphere()
{
	return this->mCollisionSphere;
}

ShellFlyComponent * Shell::getShellComponent()
{
	if(this->shellType == 1)
		return this->mShellFly;
	else return NULL;
}

SoundComponent * Shell::getSoundComponent()
{
	return mSound;
}

int Shell::getShelltype()
{
	return this->shellType;
}

void Shell::onUpdate(const float& deltaTime)
{
	if (this->onTrigger == true) {
		if (CollisionManager::sGetInstance()->collisionCheck_SphereToCube(this->shell->sphere, &attactTank) == true) {
			if (attactTank->cube->moveable == 1) {
				reinterpret_cast<Pawn*>(attactTank)->onCollisionEnter();
			}
			this->onTriggerEnter();
		}
		else {
			mCount += deltaTime;
			if (mCount >= 5.0f)
			{
				this->onTrigger = false;
				this->shell->getTransform()->setPosition(Vector3(0.f, -3.f, 0.f));
				this->mCollisionSphere->sphere.Center.x = 0.f;
				this->mCollisionSphere->sphere.Center.y = -3.f;
				this->mCollisionSphere->sphere.Center.z = 0.f;
				this->mShellFly->setVelocity(Vector3(0.f, 0.f, 0.f));
				ShellContainer::sGetInstance()->unTriggerShells.push_back(this);
				if (this->getShelltype() == 1) {
					this->getShellComponent()->setTarget(NULL);
					this->shellType = 0;
				}
				ShellContainer::sGetInstance()->onTriggerShells.erase(ShellContainer::sGetInstance()->onTriggerShells.begin());
				mCount = 0.f;
			}
		}
	}
}

void Shell::onTriggerEnter()
{
	this->onTrigger = false;
	mSound->setTriggerPosition(this->shell->getTransform()->getPosition());
	this->shell->getTransform()->setPosition(Vector3(0.f, -3.f, 0.f));
	this->mCollisionSphere->sphere.Center.x = 0.f;
	this->mCollisionSphere->sphere.Center.y = -3.f;
	this->mCollisionSphere->sphere.Center.z = 0.f;
	this->mShellFly->setVelocity(Vector3(0.f, 0.f, 0.f));
	mSound->setPosition();
	SoundManager::sGetInstance()->playOverlapSound(mSound->mChannel, 6);
	ShellContainer::sGetInstance()->unTriggerShells.push_back(this);
	if (this->getShelltype() == 1) {
		this->getShellComponent()->setTarget(NULL);
		this->shellType = 0;
	}
	ShellContainer::sGetInstance()->onTriggerShells.erase(ShellContainer::sGetInstance()->onTriggerShells.begin());
}
