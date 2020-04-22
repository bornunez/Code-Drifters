#pragma once
#include <string>
#include "ISerializer.h"
class JSONSerializer : public ISerializer
{

public:
	string Serialize(TrackerEvent* e);
};

