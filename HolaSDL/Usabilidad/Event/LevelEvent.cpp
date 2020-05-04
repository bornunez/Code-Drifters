#include "LevelEvent.h"

LevelEvent::LevelEvent(time_t time, LEVEL_EVENT_TYPE type, int levelNum) : TrackerEvent(time, LEVEL) {
	this->type = type;
	this->levelNum = levelNum;
}

json LevelEvent::ToJson()
{

	jo["NUM_LEVEL"] = levelNum;
	jo["LEVEL_EVENT_TYPE"] = levelEventString[type];

	TrackerEvent::ToJson();
	return jo;
}

string LevelEvent::ToXML()
{
	return "";
}
