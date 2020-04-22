#pragma once
#include "../Event/TrackerEvent.h"
#include "../Serializer/ISerializer.h"
class IPersistence
{
protected:
	ISerializer* serializer;

public:
	IPersistence(ISerializer* serializer) : serializer(serializer) {

	}

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Send(TrackerEvent* e) = 0;
	virtual void Flush() = 0;
};

