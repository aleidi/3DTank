#pragma once

#include <string>

enum {
	ent_Tank_Enemy,

	ent_Tank_SuperEnemy,

	ent_Debug,

	ent_Tank_Enemy1,
	ent_Tank_Enemy2,
	ent_Tank_Enemy3,
	ent_Tank_Enemy4, 
	ent_Tank_Enemy5
};

inline std::string getNameOfEntity(int n) {
	switch (n)
	{
	case ent_Tank_Enemy:
		return"Enemy Tank";
	case ent_Tank_SuperEnemy:
		return"Super Enemy Tank";
	case ent_Debug:
		return"Im Debug";
	default:
		return"Wtf is that";
	}
}

