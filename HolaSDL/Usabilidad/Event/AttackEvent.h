#pragma once
#include "TrackerEvent.h"

enum ATTACK_TYPE {	SWORD,GUN, CHARGED, HOOK,ULTI,ATTACK_TYPE_SIZE };

class AttackEvent : public TrackerEvent
{
	ATTACK_TYPE type;
	string attackTypeStrings[ATTACK_TYPE_SIZE] = { "SWORD","GUN", "CHARGED", "HOOK","ULTI" };

public:
	AttackEvent(time_t time, ATTACK_TYPE type) : TrackerEvent(time, ATTACK ) {
		this->type = type;
	}
	virtual json ToJson();
};

