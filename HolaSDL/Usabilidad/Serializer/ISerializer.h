#pragma once
#include "../Event/TrackerEvent.h"

class ISerializer
{

public:

	virtual string Serialize(TrackerEvent e) = 0;

};

