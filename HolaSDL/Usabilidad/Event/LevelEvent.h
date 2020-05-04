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

	LevelEvent(time_t time, LEVEL_EVENT_TYPE type, int levelNum);

	virtual json ToJson();

	virtual string ToXML();

};

