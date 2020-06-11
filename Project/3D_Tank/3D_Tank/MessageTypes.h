#pragma once

#include <string>

enum message_type {
	Msg_INeedRest,
	Msg_ThereisBadGuy
};

inline std::string MsgToStr(int msg) {
	switch (msg) {
	case 1:
		return"INeedRest";
	case 2:
		return"ThereisBadGuy";
	default:
		return"Not recognized";
	}
}