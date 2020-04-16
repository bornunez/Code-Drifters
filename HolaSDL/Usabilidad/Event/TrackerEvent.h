#pragma once
#include <ctime>
#include <string>

using namespace std;

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

	virtual string ToJson() {
		return "";
	}

	virtual string ToXML() {
		return "";
	}
};

