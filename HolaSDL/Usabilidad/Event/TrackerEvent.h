#pragma once
#include <ctime>
#include <string>
#include "../Serializer/json.hpp"

using namespace std;
using namespace nlohmann;

enum EventType { START, END, ATTACK };

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

