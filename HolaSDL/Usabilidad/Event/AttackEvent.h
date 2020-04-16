#pragma once
#include "TrackerEvent.h"

enum ATTACK_TYPE {	SWORD,GUN, CHARGED, HOOK };

class AttackEvent : public TrackerEvent
{
	ATTACK_TYPE type;

public:
	AttackEvent(time_t time, ATTACK_TYPE type) : TrackerEvent(time, ATTACK ) {
		this->type = type;
	}
	string ToJson() {

	}
};

