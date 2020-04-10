#pragma once
#include <ctime>

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

	string ToJson() {
		return "";
	}

	string ToXML() {
		return "";
	}
};

