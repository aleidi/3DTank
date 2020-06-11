#pragma once

#include <string>

enum {
	ent_Tank_Enemy,

	ent_Tank_SuperEnemy,

	ent_Debug
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

