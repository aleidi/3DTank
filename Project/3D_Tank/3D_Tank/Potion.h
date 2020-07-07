#pragma once
#include "GameObject.h"

class Pawn;

class Potion : public GameObject
{
public:
	Potion();
	~Potion();

	void onUpdate(const float& deltaTime) override;
	
	void setHeal(float value);

private:
	GameObject* mPotion;
	Pawn* mPlayer;

	float mOffset;
	int mHeal;

};

