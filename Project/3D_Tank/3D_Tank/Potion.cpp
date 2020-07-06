#include "Potion.h"
#include "GameCommon.h"

Potion::Potion()
	:mOffset(0.0f),mHeal(100.0f)
{
	mName = "PotionContainer";
	mPotion = SceneManager::sGetInstance()->createCube();
	mPotion->setName("Potion");
	mPotion->attach(*this);
	mPotion->getTransform()->setScale(0.1f, 0.1f, 0.1f);
	Material mat;
	mat.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mat.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
	mat.Color = XMFLOAT4(0.498f, 1.0f, 0.0f, 1.0f);
	mPotion->getRenderComponent()->setMaterial(mat);

	mTransform->rotateZ(30,true);
	mTransform->translate(0.0f, 0.0f, 5.0f);

	//save player transform
	mPlayer = GameInstance::sGetInstance()->getPlayer();
}

Potion::~Potion()
{
	mPotion->destroy();
}

void Potion::onUpdate(float deltaTime)
{
	mOffset += deltaTime;
	if (mOffset > 2 * Pi)
	{
		mOffset = 0.0f;
	}
	Vector3 pos = mTransform->getPosition();
	mTransform->setPosition(Vector3(pos.x, sinf(mOffset)*0.1f, pos.z));
	mTransform->rotateY(deltaTime*10.0f);

	float dis = Vector3::lengthSq(mPlayer->getTransform()->getPosition(), mTransform->getPosition());
	if (dis < 1.0f)
	{
		mPlayer->addHP(mHeal);
		destroy();
	}
}

void Potion::setHeal(float value)
{
	mHeal = value;
}
