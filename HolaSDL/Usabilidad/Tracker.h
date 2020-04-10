#pragma once

#include "Event/TrackerEvent.h"
#include "Persistence/IPersistence.h"
#include "Serializer/ISerializer.h"
#include "Serializer/JSONSerializer.h"
#include "Persistence/FilePersistence.h"
#include "Event/AttackEvent.h"
#include <ctime>

using namespace std;

class Tracker
{
private:
	static Tracker* instance;

	IPersistence* persistenceObject;
	ISerializer* serializerObject;

	static std::time_t getTime() {
		return std::time(nullptr);
	}

public:

	void Init() {
		serializerObject = new JSONSerializer();
		persistenceObject = new FilePersistence(serializerObject, "trackFile");
	}
	void End() {
		delete persistenceObject;
		delete serializerObject;
	}
	void TrackEvent(TrackerEvent e) {
		persistenceObject->Send(e);
	}
	static AttackEvent Attack(ATTACK_TYPE type) {
		AttackEvent e(getTime(), type);
		return e;
	}

	static Tracker* getInstance() {
		if (instance == nullptr)
			instance = new Tracker();
		return instance;
	}
};

