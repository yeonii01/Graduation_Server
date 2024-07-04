#pragma once
#include "stdafx.h"

enum EVENT_TYPE { EV_TARGET_MOVE, EV_HEAL, EV_ATTACK };
class EVENT {
public:
	int obj_id;
	std::chrono::system_clock::time_point wakeup_time;
	EVENT_TYPE e_type;
	int target_id;

	bool operator<(const EVENT& cmp) const {
		return this->wakeup_time > cmp.wakeup_time;
	}
};
