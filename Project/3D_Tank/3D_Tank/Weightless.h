#pragma once
#include "GameObject.h"
#include "SceneManager.h"

class Weightless : public GameObject
{
public:
	GameObject* empty = SceneManager::sGetInstance()->createEmptyObject();
	
	Weightless();
	void onUpdate(const float& deltaTime) override;
};