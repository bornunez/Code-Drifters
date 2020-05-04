#pragma once

#include "Event/TrackerEvent.h"
#include "Persistence/IPersistence.h"
#include "Serializer/ISerializer.h"
#include "Serializer/JSONSerializer.h"
#include "Persistence/FilePersistence.h"
#include "Persistence/ServerPersistence.h"
#include "Event/AttackEvent.h"
#include "Event/ComboEvent.h"
#include "Event/LevelEvent.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class Tracker
{
private:
	static Tracker* instance;

	IPersistence* persistenceObject;
	ISerializer* serializerObject;
 	string GAME_ID = "";


	static std::time_t getTime() {
		return std::time(nullptr);
	}
	string getDateString();
	string getTimeString();

public:

	Tracker() {

	}

	void Init();
	void End();
	void TrackEvent(TrackerEvent* e);
	static TrackerEvent* GenerateTrackerEvent(EventType type);
	static AttackEvent* GenerateAtackEvent(ATTACK_TYPE type);
	static ComboEvent* GenerateComboEvent(COMBO_TYPE type);
	static LevelEvent* GenerateLevelEvent(LEVEL_EVENT_TYPE type, int levelNum);

	static Tracker* getInstance() {
		if (instance == nullptr)
			instance = new Tracker();
		return instance;
	}
};

