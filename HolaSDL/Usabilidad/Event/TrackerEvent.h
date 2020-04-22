#pragma once
#include <ctime>
#include <string>
#include "../Serializer/json.hpp"

using namespace std;
using namespace nlohmann;

enum EventType {SESSION_START, SESSION_END, ATTACK,COMBO,GAME_START,GAME_END,PLAYER_KILLED };

class TrackerEvent
{
	EventType eventType;
	std::time_t time;

public:
	TrackerEvent(time_t time, EventType eventType) {
		this->eventType = eventType;
		this->time = time;
	}

	virtual json ToJson() {
		json jo;

		jo["TIME"] = time;
		jo["TYPE"] = eventType;

		return jo;
	}

	virtual string ToXML() {
		return "";
	}
};

