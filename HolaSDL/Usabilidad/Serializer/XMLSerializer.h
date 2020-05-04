#pragma once
#include "ISerializer.h"
#include "../../tinyxml2.h"

class XMLSerializer :
	public ISerializer
{
public:
	string Serialize(TrackerEvent* e);
};

