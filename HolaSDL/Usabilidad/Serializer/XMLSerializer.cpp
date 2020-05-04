#include "XMLSerializer.h"

string XMLSerializer::Serialize(TrackerEvent* e)
{
	return e->ToXML();
}
