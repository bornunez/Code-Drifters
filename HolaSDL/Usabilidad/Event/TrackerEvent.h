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

	string getTimeString() {
		auto t = time;
		struct tm buf;
		localtime_s(&buf, &t);

		std::ostringstream oss;
		oss << std::put_time(&buf, "%H:%M:%S");
		return oss.str();

	}

public:
	TrackerEvent(time_t time, EventType eventType) {
		this->eventType = eventType;
		this->time = time;
	}

	virtual json ToJson() {

		jo["TIME"] = getTimeString();
		jo["TYPE"] =typeStrings[eventType];

		return jo;
	}

	virtual string ToXML() {
		return "";
	}
};

