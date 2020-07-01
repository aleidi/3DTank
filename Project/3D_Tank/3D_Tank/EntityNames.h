#pragma once

#include <string>

enum {
	ent_Tank_Player = -1,

	ent_Tank_SuperEnemy,

	ent_Tank_Enemy01,

	ent_Tank_Enemy02,

	ent_Tank_Enemy03,

	ent_Tank_Enemy04,

	ent_Tank_Enemy05,

	ent_Tank_Enemy06,

	ent_Tank_Enemy07,

	ent_Tank_Enemy08,

	ent_Tank_Enemy09,

	ent_Tank_Enemy10,

	ent_Tank_FakePlayer = 88,

	ent_Debug = 99

};

inline std::string getNameOfEntity(int n) {
	switch (n)
	{
	case ent_Tank_Enemy01:
		return"Enemy Tank 01";
	case ent_Tank_SuperEnemy:
		return"Super Enemy Tank";
	case ent_Debug:
		return"Debug";
	default:
		return"Wtf is that";
	}
}

