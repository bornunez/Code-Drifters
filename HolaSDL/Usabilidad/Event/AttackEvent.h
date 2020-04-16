#pragma once
#include "TrackerEvent.h"

enum ATTACK_TYPE {	SWORD,GUN, CHARGED, HOOK,ULTI };

class AttackEvent : public TrackerEvent
{
	ATTACK_TYPE type;

public:
	AttackEvent(time_t time, ATTACK_TYPE type) : TrackerEvent(time, ATTACK ) {
		this->type = type;
	}
	json ToJson() {
		json jo = TrackerEvent::ToJson();

		jo["ATTACK_TYPE"] = type;

		return jo;
	}
};

