#pragma once

#include <string>

enum message_type {
	Msg_INeedRest,
	Msg_ThereisBadGuy,
	Msg_HPRecovered
};

inline std::string MsgToStr(int msg) {
	switch (msg) {
	case 1:
		return"INeedRest";
	case 2:
		return"ThereisBadGuy";
	case 3:
		return"HP has recovered.";
	default:
		return"Not recognized";
	}
}