#pragma once
#include "TrackerEvent.h"

enum COMBO_TYPE { GUN_SWORD, GUN_ULTI, HOOK_SWORD, HOOK_GUN, TRIPLE_SWORD};

class ComboEvent : public TrackerEvent
{
	COMBO_TYPE type;

public:
	ComboEvent(time_t time, COMBO_TYPE type) : TrackerEvent(time, COMBO) {
		this->type = type;
	}
	json ToJson() {
		json jo = TrackerEvent::ToJson();

		jo["COMBO_TYPE"] = type;

		return jo;
	}
};

