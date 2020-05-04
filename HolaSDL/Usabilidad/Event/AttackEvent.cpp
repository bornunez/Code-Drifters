#include "AttackEvent.h"

json AttackEvent::ToJson()
{

	jo["ATTACK_TYPE"] = attackTypeStrings[type];

	TrackerEvent::ToJson();
	return jo;
}
