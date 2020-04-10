#pragma once
#include "../Event/TrackerEvent.h"
class IPersistence
{

public:
	virtual void Init() = 0;
	virtual void Send(TrackerEvent e) = 0;
	virtual void Flush() = 0;
};

