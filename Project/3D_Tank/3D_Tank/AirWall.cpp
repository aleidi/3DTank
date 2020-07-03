#include "AirWall.h"
#include "GameCommon.h"

AirWall::AirWall(const Vector3& position, const Vector3& scale)
{
	//airCube = SceneManager::sGetInstance()->createCube();
	//airCube->getTransform()->setPosition(position);
	//airCube->getTransform()->setScale(scale);
	//airCube->attach(*this);
	//airCube->setName("airwallcube");

	
	mTransform->setPosition(position);
	mTransform->setScale(scale);
	mName = "airwall";

	mCollisionBox = new BoundingCube(this);
	mCollisionBox->createBoundingCube(position, Vector3(0.5 * scale.x, 0.5 * scale.y, 0.5 * scale.z), 0);
	this->addComponent(mCollisionBox);
	this->cube = mCollisionBox;

	mTag = ObjectTag::Environment;

	//cube->addComponent(mCollisionBox);
	//cube->cube = mCollisionBox;
}

AirWall::~AirWall()
{
	//cube->destroy();
}
