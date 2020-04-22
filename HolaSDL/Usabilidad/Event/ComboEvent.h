#pragma once
#include "TrackerEvent.h"

enum COMBO_TYPE { GUN_SWORD, HOOK_SWORD, HOOK_GUN, TRIPLE_SWORD,COMBO_TYPE_SIZE};

class ComboEvent : public TrackerEvent
{
	COMBO_TYPE type;
	string comboString[COMBO_TYPE_SIZE] = { "GUN_SWORD", "HOOK_SWORD", "HOOK_GUN", "TRIPLE_SWORD" };
public:
	ComboEvent(time_t time, COMBO_TYPE type) : TrackerEvent(time, COMBO) {
		this->type = type;
	}
	json ToJson() {

		jo["COMBO_TYPE"] = comboString[type];

		TrackerEvent::ToJson();
		return jo;
	}
};

