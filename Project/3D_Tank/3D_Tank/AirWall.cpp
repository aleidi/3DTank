#include "AirWall.h"
#include "GameCommon.h"

AirWall::AirWall(const Vector3& position, const Vector3& scale)
{
	//cube = SceneManager::sGetInstance()->createCube();
	//cube->getTransform()->setPosition(position);
	//cube->getTransform()->setScale(scale);
	//cube->attach(*this);
	//cube->setName("airwallcube");
	
	mTransform->setPosition(position);
	mTransform->setScale(scale);
	mName = "airwall";

	mCollisionBox = new BoundingCube(this);
	mCollisionBox->createBoundingCube(position, Vector3(0.5 * scale.x, 0.5 * scale.y, 0.5 * scale.z), 0);
	addComponent(mCollisionBox);
	cube = mCollisionBox;
	//cube->addComponent(mCollisionBox);
	//cube->cube = mCollisionBox;
}

AirWall::~AirWall()
{
	//cube->destroy();
}
