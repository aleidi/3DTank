#pragma once

#include <string>

enum message_type {
	Msg_INeedRest,
	Msg_ThereisBadGuy,
	Msg_HPRecovered,
	Msg_IsAttacked,
	Msg_DeathDelay
};

inline std::string MsgToStr(int msg) {
	switch (msg) {
	case 1:
		return"INeedRest";
	case 2:
		return"ThereisBadGuy";
	case 3:
		return"HP has recovered.";
	case 4:
		return"ImAttacked";
	case 5:
		return"IwillDeathSoon";
	default:
		return"Not recognized";
	}
}