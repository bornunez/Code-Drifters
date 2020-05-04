#include "TrackerEvent.h"

string TrackerEvent::getTimeString()
{
	auto t = time;
	struct tm buf;
	localtime_s(&buf, &t);

	std::ostringstream oss;
	oss << std::put_time(&buf, "%H:%M:%S");
	return oss.str();

}

TrackerEvent::TrackerEvent(time_t time, EventType eventType)
{
	this->eventType = eventType;
	this->time = time;
}

json TrackerEvent::ToJson()
{

	jo["TIME"] = getTimeString();
	jo["TYPE"] = typeStrings[eventType];

	return jo;
}

string TrackerEvent::ToXML()
{
	return "";
}
