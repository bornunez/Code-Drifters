#pragma once
#include "TrackerEvent.h"

enum LEVEL_EVENT_TYPE { LEVEL_START, LEVEL_END };

class LevelEvent : public TrackerEvent
{

private:
	LEVEL_EVENT_TYPE type;
	int levelNum;

public:

	LevelEvent(time_t time, LEVEL_EVENT_TYPE type, int levelNum) : TrackerEvent(time, LEVEL) {
		this->type = type;
		this->levelNum = levelNum;
	}

	virtual json ToJson() {
		json jo = TrackerEvent::ToJson();
		return jo;
	}

	virtual string ToXML() {
		return "";
	}

};

