#pragma once
#include "../Event/TrackerEvent.h"
#include <string>

using namespace std;

class ISerializer
{

public:

	virtual string Serialize(TrackerEvent e) = 0;

};

