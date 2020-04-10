#include "JSONSerializer.h"

string JSONSerializer::Serialize(TrackerEvent e)
{
	return e.ToJson();
}
