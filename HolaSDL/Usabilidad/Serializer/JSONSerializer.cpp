#include "JSONSerializer.h"

string JSONSerializer::Serialize(TrackerEvent e)
{
	json jo = e.ToJson();

	std::string s = jo.dump();

	return s;
}
