#pragma once
#include "../Event/TrackerEvent.h"
class IPersistence
{
protected:
	ISerializer* serializer;

public:
	IPersistence(ISerializer* serializer) : serializer(serializer) {

	}

	virtual void Init() = 0;
	virtual void Send(TrackerEvent e) = 0;
	virtual void Flush() = 0;
};

