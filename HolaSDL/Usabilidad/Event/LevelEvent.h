#pragma once
#include "TrackerEvent.h"

enum LEVEL_EVENT_TYPE { LEVEL_START, LEVEL_END ,LEVEL_EVENT_SIZE};

class LevelEvent : public TrackerEvent
{

private:
	LEVEL_EVENT_TYPE type;
	int levelNum;
	string levelEventString[LEVEL_EVENT_SIZE] = { "LEVEL_START","LEVEL_END" };

public:

	LevelEvent(time_t time, LEVEL_EVENT_TYPE type, int levelNum) : TrackerEvent(time, LEVEL);

	virtual json ToJson() {

		jo["NUM_LEVEL"] = levelNum;
		jo["LEVEL_EVENT_TYPE"] = levelEventString[type];

		TrackerEvent::ToJson();
		return jo;
	}

	virtual string ToXML() {
		return "";
	}

};

