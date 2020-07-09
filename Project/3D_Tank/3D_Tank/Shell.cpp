#include "Shell.h"
#include "GameCommon.h"
#include "ShellFlyComponent.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "SoundComponent.h"
#include "PlayerTank.h"
#include "ShellContainer.h"

Shell::Shell() :shellType(0),tankType(1)
{
	shell = SceneManager::sGetInstance()->createSphere();
	Material mat = shell->getComponent<RenderComponent>()->getMaterial();
	mat.Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	shell->getComponent<RenderComponent>()->setMaterial(mat);

	shell->getTransform()->setPosition(Vector3(0.f, -3.f, 0.f));
	shell->getTransform()->setScale(0.02f, 0.02f, 0.02f);

	mCollisionSphere = new MBoundingSphere(shell);
	mCollisionSphere->createBoundingSphere(shell->getTransform()->getPosition(), 0.02f, 1);
	shell->addComponent(mCollisionSphere);
	mShellFly = new ShellFlyComponent(shell, Vector3(0.f,0.f,0.f));
	shell->addComponent(mShellFly);
	shell->sphere = mCollisionSphere;
	mSound = new SoundComponent(shell);
	shell->addComponent(mSound);
	this->onTrigger = false;
	ShellContainer::sGetInstance()->unTriggerShells.push_back(this);
}

Shell::Shell(const Vector3& ori, const Vector3& direction, const int& shellType)
	:shellType(shellType), origin(ori), tankType(0)
{
	//float dot = Vector3::dot(Vector3::forward, direction.normalize());
	//dot = Math::Clamp(1.0f, -1.0f, dot);
	//float rotate = acosf(dot) * 180 / Pi;
	//Vector3 cross = Vector3::cross(Vector3::forward, direction.normalize());
	//if (cross.y > 0)
	//	rotate = -rotate;
	//shell = SceneManager::sGetInstance()->createEmptyObject();
	//SceneManager::sGetInstance()->createModel(*shell,"Objects/Shell", L"Objects/Shell");
	shell = SceneManager::sGetInstance()->createSphere();
	Material mat = shell->getComponent<RenderComponent>()->getMaterial();
	if (shellType == 0) {
		mat.Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		mat.Color = XMFLOAT4(0.863f, 0.863f, 0.863f, 0.6f);
	}
	shell->getComponent<RenderComponent>()->setMaterial(mat);
	shell->getTransform()->setPosition(this->origin + direction * 0.6f + Vector3::up * 0.1f);
	shell->getTransform()->setScale(0.02f, 0.02f, 0.02f); 
	//shell->getTransform()->rotate(90.f, -rotate, 0.f);

	mCollisionSphere = new MBoundingSphere(shell);
	mCollisionSphere->createBoundingSphere(shell->getTransform()->getPosition(), 0.02f, 1);
	shell->addComponent(mCollisionSphere);
	mShellFly = new ShellFlyComponent(shell, direction);
	shell->addComponent(mShellFly);
	mShellFly->setTankType(0);
	shell->sphere = mCollisionSphere;
	mSound = new SoundComponent(shell);
	shell->addComponent(mSound);
	this->onTrigger = true;
	ShellContainer::sGetInstance()->onTriggerShells.push_back(this);
	mSound->setPosition();
	SoundManager::sGetInstance()->playOverlapSound(mSound->mChannel, 6);
	//SoundManager::sGetInstance()->setValume(0.3f, mSound->mChannel);
}

Shell::Shell(const Vector3 & ori, const Vector3 & direction, const int & shellType, const int& tankType)
	:shellType(shellType), origin(ori), tankType(tankType)
{


	shell->getTransform()->setPosition(ori);

	mCollisionSphere = new MBoundingSphere(shell);
	mCollisionSphere->createBoundingSphere(shell->getTransform()->getPosition(), 0.05f, 1);
	shell->addComponent(mCollisionSphere);
	mShellFly = new ShellFlyComponent(shell, direction);
	shell->addComponent(mShellFly);
	mShellFly->setTankType(tankType);
	shell->sphere = mCollisionSphere;
	mSound = new SoundComponent(shell);
	shell->addComponent(mSound);
	this->onTrigger = true;
	ShellContainer::sGetInstance()->onTriggerShells.push_back(this);

	ShellContainer::sGetInstance()->onTriggerBossShells.push_back(this);
	mSound->setPosition();
	SoundManager::sGetInstance()->playOverlapSound(mSound->mChannel, 6);
}

Shell::~Shell()
{
}

void Shell::resetPosAndDir(const Vector3 & origin, const Vector3 & direction, const int & shellType, const int& enemyType)
{
	if (enemyType == 0) {
		this->onTrigger = true;
		this->shell->getTransform()->setPosition(origin + direction * 0.6f + Vector3::up * 0.1f);
		Material mat = shell->getComponent<RenderComponent>()->getMaterial();
		mat.Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		shell->getComponent<RenderComponent>()->setMaterial(mat);
		this->mCollisionSphere->sphere.Center.x = shell->getTransform()->getPosition().x;
		this->mCollisionSphere->sphere.Center.y = shell->getTransform()->getPosition().y;
		this->mCollisionSphere->sphere.Center.z = shell->getTransform()->getPosition().z;
		this->shellType = shellType;
		this->mShellFly->setVelocity(direction);
		mSound->setPosition();
		SoundManager::sGetInstance()->playOverlapSound(mSound->mChannel, 6);
		SoundManager::sGetInstance()->setValume(0.3f, mSound->mChannel);
		ShellContainer::sGetInstance()->onTriggerShells.push_back(this);
		for (std::vector<Shell*>::iterator it = ShellContainer::sGetInstance()->unTriggerShells.begin(); it != ShellContainer::sGetInstance()->unTriggerShells.end(); it++) {
			if (*it == this) {
				ShellContainer::sGetInstance()->unTriggerShells.erase(it);
				break;
			}
		}
	}
	else {
		this->onTrigger = true;
		this->shell->getTransform()->setPosition(origin);
		this->mCollisionSphere->sphere.Center.x = origin.x;
		this->mCollisionSphere->sphere.Center.y = origin.y;
		this->mCollisionSphere->sphere.Center.z = origin.z;
		this->shellType = shellType;
		this->mShellFly->setVelocity(direction);

		ShellContainer::sGetInstance()->onTriggerBossShells.push_back(this);
		for (std::vector<Shell*>::iterator it = ShellContainer::sGetInstance()->unTriggerBossShells.begin(); it != ShellContainer::sGetInstance()->unTriggerBossShells.end(); it++) {
			if (*it == this) {
				ShellContainer::sGetInstance()->unTriggerBossShells.erase(it);
				break;
			}
		}
	}
}

void Shell::resetPosAndDir(const Vector3 & origin, const Vector3 & direction, const int & shellType, GameObject * obj, const int& enemyType)
{
	if (enemyType == 0) {
		this->onTrigger = true;
		this->shell->getTransform()->setPosition(origin + direction * 0.6f + Vector3::up * 0.1f);
		Material mat = shell->getComponent<RenderComponent>()->getMaterial();
		mat.Color = XMFLOAT4(0.863f, 0.863f, 0.863f, 0.6f);
		shell->getComponent<RenderComponent>()->setMaterial(mat);
		this->mCollisionSphere->sphere.Center.x = shell->getTransform()->getPosition().x;
		this->mCollisionSphere->sphere.Center.y = shell->getTransform()->getPosition().y;
		this->mCollisionSphere->sphere.Center.z = shell->getTransform()->getPosition().z;
		this->shellType = shellType;
		this->mShellFly->setVelocity(direction);
		mSound->setPosition();
		SoundManager::sGetInstance()->playOverlapSound(mSound->mChannel, 6);
		SoundManager::sGetInstance()->setValume(0.3f, mSound->mChannel);
		ShellContainer::sGetInstance()->onTriggerShells.push_back(this);
		this->mShellFly->setTarget(obj);
		for (std::vector<Shell*>::iterator it = ShellContainer::sGetInstance()->unTriggerShells.begin(); it != ShellContainer::sGetInstance()->unTriggerShells.end(); it++) {
			if (*it == this) {
				ShellContainer::sGetInstance()->unTriggerShells.erase(it);
				break;
			}
		}
	}
	else {
		this->onTrigger = true;
		this->shell->getTransform()->setPosition(origin);
		this->mCollisionSphere->sphere.Center.x = origin.x;
		this->mCollisionSphere->sphere.Center.y = origin.y;
		this->mCollisionSphere->sphere.Center.z = origin.z;
		this->shellType = shellType;
		this->mShellFly->setVelocity(direction);
		this->mShellFly->setTarget(obj);

		ShellContainer::sGetInstance()->onTriggerBossShells.push_back(this);
		for (std::vector<Shell*>::iterator it = ShellContainer::sGetInstance()->unTriggerBossShells.begin(); it != ShellContainer::sGetInstance()->unTriggerBossShells.end(); it++) {
			if (*it == this) {
				ShellContainer::sGetInstance()->unTriggerBossShells.erase(it);
				break;
			}
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
			if (shellType == 0) {
				if (mCount >= 5.0f)
				{
					this->onTrigger = false;
					this->shell->getTransform()->setPosition(Vector3(0.f, -3.f, 0.f));
					this->mCollisionSphere->sphere.Center.x = 0.f;
					this->mCollisionSphere->sphere.Center.y = -3.f;
					this->mCollisionSphere->sphere.Center.z = 0.f;
					this->mShellFly->setVelocity(Vector3(0.f, 0.f, 0.f));
					//shell->getTransform()->setRotation(Vector3(0.f, 0.f, 0.f));
					if (tankType == 0) {
						ShellContainer::sGetInstance()->unTriggerShells.push_back(this);
						ShellContainer::sGetInstance()->onTriggerShells.erase(ShellContainer::sGetInstance()->onTriggerShells.begin());
					}
					else {
						ShellContainer::sGetInstance()->unTriggerBossShells.push_back(this);
						ShellContainer::sGetInstance()->onTriggerBossShells.erase(ShellContainer::sGetInstance()->onTriggerBossShells.begin());
					}
					mCount = 0.f;
				}
			}
			else {
				if (mCount >= 10.f) {
					this->onTrigger = false;
					this->shell->getTransform()->setPosition(Vector3(0.f, -3.f, 0.f));
					this->mCollisionSphere->sphere.Center.x = 0.f;
					this->mCollisionSphere->sphere.Center.y = -3.f;
					this->mCollisionSphere->sphere.Center.z = 0.f;
					this->mShellFly->setVelocity(Vector3(0.f, 0.f, 0.f));
					//->getTransform()->setRotation(Vector3(0.f, 0.f, 0.f));
					if (tankType == 0) {
						ShellContainer::sGetInstance()->unTriggerShells.push_back(this);
						if (this->getShelltype() == 1) {
							this->getShellComponent()->setTarget(NULL);
							this->shellType = 0;
						}
						ShellContainer::sGetInstance()->onTriggerShells.erase(ShellContainer::sGetInstance()->onTriggerShells.begin());
					}
					else {
						ShellContainer::sGetInstance()->unTriggerBossShells.push_back(this);
						if (this->getShelltype() == 1) {
							this->getShellComponent()->setTarget(NULL);
							this->shellType = 0;
						}
						ShellContainer::sGetInstance()->onTriggerBossShells.erase(ShellContainer::sGetInstance()->onTriggerBossShells.begin());
					}
					mCount = 0.f;
				}
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
	SoundManager::sGetInstance()->playOverlapSound(mSound->mChannel, 9);
	//SoundManager::sGetInstance()->setFrequency(0.5f, mSound->mChannel);
	SoundManager::sGetInstance()->setValume(0.3f, mSound->mChannel);
	//shell->getTransform()->setRotation(Vector3(0.f, 0.f, 0.f));
	if (tankType == 0) {
		ShellContainer::sGetInstance()->unTriggerShells.push_back(this);
		if (this->getShelltype() == 1) {
			this->getShellComponent()->setTarget(NULL);
			this->shellType = 0;
		}
		ShellContainer::sGetInstance()->onTriggerShells.erase(ShellContainer::sGetInstance()->onTriggerShells.begin());
	}
	else {
		ShellContainer::sGetInstance()->unTriggerBossShells.push_back(this);
		if (this->getShelltype() == 1) {
			this->getShellComponent()->setTarget(NULL);
			this->shellType = 0;
		}
		ShellContainer::sGetInstance()->onTriggerBossShells.erase(ShellContainer::sGetInstance()->onTriggerBossShells.begin());
	}
}
