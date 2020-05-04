#pragma once
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "../Serializer/json.hpp"

using namespace std;
using namespace nlohmann;

enum EventType { SESSION_START, SESSION_END, ATTACK, COMBO, GAME_START, GAME_END, PLAYER_KILLED,LEVEL ,EVENT_TYPE_SIZE};

class TrackerEvent
{
protected:
	string typeStrings[EVENT_TYPE_SIZE] = { "SESSION_START", "SESSION_END", "ATTACK", "COMBO", "GAME_START", "GAME_END"," PLAYER_KILLED","LEVEL" };
	EventType eventType;
	std::time_t time;
	json jo;

	string getTimeString();

public:
	TrackerEvent(time_t time, EventType eventType);

	virtual json ToJson();

	virtual string ToXML();
};

